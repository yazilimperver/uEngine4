#include "stb_image_loader.h"

#include <string>
#include <fstream>

#include "spdlog/spdlog.h"

#include "gl_texture/texture_info.h"
#include "gl_texture/texture_asset.h"

#include "utility/unique_id_generator.h"

#define STB_IMAGE_IMPLEMENTATION   

#include <stb_image.h>

#include <string>

namespace gl {
	const std::string gLoaderExtension = "*";
	const std::string gLoaderName("STBImageLoader");

    infra::AssetLoaderName STBImageLoader::Name() {
        return gLoaderName;
    }
    std::shared_ptr<infra::Asset> STBImageLoader::Load(std::string_view path, std::string_view label) {
        auto newAsset = std::make_shared<TextureAsset>();
        TextureInfo textureInfo;
        newAsset->InfoRef().mStatus = infra::AssetStatus::LoadInProgress;

        int32_t imageWidth = 0;
        int32_t imageHeight;
        int32_t imageBPP;
        unsigned char* image = nullptr;

        auto assetPath = static_cast<std::string>(path);
        stbi_info(assetPath.c_str(), &imageWidth, &imageHeight, &imageBPP);

        if (TextureBPP::BPP_1 == static_cast<TextureBPP>(imageBPP)) {
            image = stbi_load(assetPath.c_str(), &imageWidth, &imageHeight, &imageBPP, STBI_grey);
            textureInfo.PixelFormat = PixelFormat::ALPHA;
            imageBPP = 1U;
        }
        else if (TextureBPP::BPP_3 == static_cast<TextureBPP>(imageBPP)) {
            image = stbi_load(assetPath.c_str(), &imageWidth, &imageHeight, &imageBPP, STBI_rgb);
            textureInfo.PixelFormat = PixelFormat::RGB;
        }
        else
        {
            image = stbi_load(assetPath.c_str(), &imageWidth, &imageHeight, &imageBPP, STBI_rgb_alpha);
            textureInfo.PixelFormat = PixelFormat::RGBA;
        }

        if (nullptr != image) {
            textureInfo.Height = imageHeight;
            textureInfo.Width = imageWidth;
            textureInfo.BPP = static_cast<TextureBPP>(imageBPP);
            textureInfo.PixelType = PixelType::UNSIGNED_BYTE;
            textureInfo.IsCompressed = false;            

            int32_t size = imageWidth * imageHeight * imageBPP;
            auto& rawData = newAsset->GetTextureRawData();
            rawData.resize(size);
            memcpy((char*)&rawData[0], image, size);

            newAsset->SetAsDirty();
            stbi_image_free(image);
            newAsset->InfoRef().mStatus = infra::AssetStatus::LoadSuccessful;
        }
        else {
            newAsset->InfoRef().mStatus = infra::AssetStatus::LoadFailed;
        }

        newAsset->InfoRef().mHandle = UniqueIDGenerator::GetNextID();
        newAsset->InfoRef().mPath = static_cast<std::string>(path);
        newAsset->InfoRef().mLabel = static_cast<std::string>(label);
        newAsset->InfoRef().mLoaderHandle = mAssetLoaderHandle;
        newAsset->SetTextureInfo(textureInfo);

        return newAsset;
    }
    void STBImageLoader::Dispose(std::shared_ptr<infra::Asset>) {

    }
}