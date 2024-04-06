#include "dds_texture_loader.h"

#include <string>
#include <fstream>

#include "spdlog/spdlog.h"

#include "gl_texture/texture_info.h"
#include "gl_texture/texture_asset.h"

#include "utility/unique_id_generator.h"

const uint16_t PIXEL_FORMAT_GL_COMPRESSED_RGB_S3TC_DXT1_EXT = 0x83F0;
const uint16_t PIXEL_FORMAT_GL_COMPRESSED_RGBA_S3TC_DXT1_EXT = 0x83F1;
const uint16_t PIXEL_FORMAT_GL_COMPRESSED_RGBA_S3TC_DXT3_EXT = 0x83F2;
const uint16_t PIXEL_FORMAT_GL_COMPRESSED_RGBA_S3TC_DXT5_EXT = 0x83F3;

//! DDS Constants
const uint32_t FOURCC_DXT1 = 0x31545844; //(MAKEFOURCC('D','X','T','1'))
const uint32_t FOURCC_DXT3 = 0x33545844; //(MAKEFOURCC('D','X','T','3'))
const uint32_t FOURCC_DXT5 = 0x35545844; //(MAKEFOURCC('D','X','T','5'))

const uint32_t DDS_FILE_TYPE_STRING_LENGTH = 4U;
const uint32_t DDS_HEADER_STRING_LENGTH = 124U;
const uint32_t BLOCK_SIZE_DXT1 = 8U;
const uint32_t BLOCK_SIZE_DXT3_5 = 16U;
const uint32_t DDS_HEIGHT_OFFSET = 8U;
const uint32_t DDS_WIDTH_OFFSET = 12U;
const uint32_t DDS_LINEARSIZE_OFFSET = 16U;
const uint32_t DDS_MIPMAP_COUNT_OFFSET = 24U;
const uint32_t DDS_FOURE_CC_OFFSET = 80U;

namespace gl {
	const static std::string gLoaderExtension = ".dds";
	const static std::string gLoaderName("DDSTextureLoader");

    
    infra::AssetLoaderName DDSTextureLoader::Name() {
        return gLoaderName;
    }

    std::shared_ptr<infra::Asset> DDSTextureLoader::Load(std::string_view path, std::string_view label) {
        auto newAsset = std::make_shared<TextureAsset>();
        TextureInfo textureInfo;        
        newAsset->InfoRef().mStatus = infra::AssetStatus::LoadInProgress;

        std::ifstream fileToRead;
        fileToRead.open(static_cast<std::string>(path), std::ios::binary);
        
        if (false == fileToRead.is_open()) {
            spdlog::error("[uDDSLoader] File not found! File: {}", static_cast<std::string>(path));
        }
        else {
            std::array<char, DDS_FILE_TYPE_STRING_LENGTH> fileHeader;
            fileToRead.read(fileHeader.data(), DDS_FILE_TYPE_STRING_LENGTH);

            if (true == fileToRead.eof()) {
                spdlog::error("[uDDSLoader] Error, not enough bytes!");
            }
            else {
                if (('D' != fileHeader[0])
                    ||
                    ('D' != fileHeader[1])
                    ||
                    ('S' != fileHeader[2])
                    ||
                    (' ' != fileHeader[3])) {
                    newAsset->InfoRef().mStatus = infra::AssetStatus::LoadFailed;
                    spdlog::error("[uDDSLoader] Image is not a DDS type!");
                }
                else {
                    std::array<char, DDS_HEADER_STRING_LENGTH> header;
                    fileToRead.read(header.data(), DDS_HEADER_STRING_LENGTH);

                    if (true == fileToRead.eof()) {
                        spdlog::error("[uDDSLoader] Error, not enough bytes!");
                    }
                    else {
                        uint32_t height = *reinterpret_cast<uint32_t*>(&(header[DDS_HEIGHT_OFFSET]));
                        uint32_t width = *reinterpret_cast<uint32_t*>(&(header[DDS_WIDTH_OFFSET]));
                        uint32_t linearSize = *reinterpret_cast<uint32_t*>(&(header[DDS_LINEARSIZE_OFFSET]));
                        uint32_t mipMapCount = *reinterpret_cast<uint32_t*>(&(header[DDS_MIPMAP_COUNT_OFFSET]));
                        uint32_t fourCC = *reinterpret_cast<uint32_t*>(&(header[DDS_FOURE_CC_OFFSET]));
                        uint32_t bpp = 0U;

                        if (fourCC == FOURCC_DXT1) {
                            bpp = 3U;
                        }
                        else {
                            bpp = 4U;
                        }

                        spdlog::info("[uDDSLoader] Image Info> Width: {}, Height {}, Bytes per Pixel {}", width, height, bpp);

                        // Mipmapping will not be used
                        if (mipMapCount > 1) {
                            spdlog::error("[uDDSLoader] Mipmapping not supported!");
                            newAsset->InfoRef().mStatus = infra::AssetStatus::LoadFailed;
                        }
                        else {
                            uint32_t bufSize = linearSize;
                            auto& rawData = newAsset->GetTextureRawData();
                            rawData.resize(bufSize);

                            fileToRead.read((char*)&rawData[0], bufSize);

                            // load completed
                            newAsset->InfoRef().mStatus = infra::AssetStatus::LoadSuccessful;

                            // fill metadata
                            textureInfo.Width = width;
                            textureInfo.Height = height;
                            textureInfo.BPP = static_cast<TextureBPP>(bpp);
                            textureInfo.IsCompressed = true;
                            textureInfo.PixelType = PixelType::UNSIGNED_BYTE;

                            switch (fourCC) {
                                // Block size is 8
                            case FOURCC_DXT1:
                                textureInfo.PixelFormat = PixelFormat::PIXEL_FORMAT_GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
                                textureInfo.mDDSTextureSize = ((width + 3) / 4) * ((height + 3) / 4) * BLOCK_SIZE_DXT1;
                                break;
                                // Block size is 16
                            case FOURCC_DXT3:
                                textureInfo.PixelFormat = PixelFormat::PIXEL_FORMAT_GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
                                textureInfo.mDDSTextureSize = ((width + 3) / 4) * ((height + 3) / 4) * BLOCK_SIZE_DXT3_5;
                                break;
                                // Block size is 16
                            case FOURCC_DXT5:
                                textureInfo.PixelFormat = PixelFormat::PIXEL_FORMAT_GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
                                textureInfo.mDDSTextureSize = ((width + 3) / 4) * ((height + 3) / 4) * BLOCK_SIZE_DXT3_5;
                                break;
                            default:
                                newAsset->InfoRef().mStatus = infra::AssetStatus::LoadFailed;
                                break;
                            }
                        }
                    }
                }
            }
        }

        newAsset->SetAsDirty();
        newAsset->InfoRef().mHandle = UniqueIDGenerator::GetNextID();
        newAsset->InfoRef().mPath = static_cast<std::string>(path);
        newAsset->InfoRef().mLabel = static_cast<std::string>(label);
        newAsset->InfoRef().mLoaderHandle = mAssetLoaderHandle;
        newAsset->SetTextureInfo(textureInfo);

        return newAsset;
    }
    
    void DDSTextureLoader::Dispose(std::shared_ptr<infra::Asset> asset) {
        // ozel bir sey yapmaya gerek yok
    }
}