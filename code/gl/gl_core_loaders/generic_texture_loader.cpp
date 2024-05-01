#include "generic_texture_loader.h"

#include <string>
#include <fstream>

#include "spdlog/spdlog.h"

#include "gl_texture/texture_info.h"
#include "gl_texture/texture_asset.h"

#include "utility/unique_id_generator.h"

#undef _UNICODE
#define ILUT_USE_OPENGL	// This MUST be defined before calling the DevIL headers or we don't get OpenGL functionality
#include <IL/il.h>
#include <IL/ilu.h>

#include <string>

namespace gl {
	const std::string gLoaderExtension = "*";
	const std::string gLoaderName("GenericTextureLoader");

    infra::AssetLoaderName GenericTextureLoader::Name() {
        return gLoaderName;
    }
    std::shared_ptr<infra::Asset> GenericTextureLoader::Load(std::string_view path, std::string_view label) {
        auto newAsset = std::make_shared<TextureAsset>();
        TextureInfo textureInfo;
        newAsset->InfoRef().mStatus = infra::AssetStatus::LoadInProgress;

        ILuint imageID;

        ilGenImages(1, &imageID);
        ilBindImage(imageID);

        //Load image
        ILboolean success = ilLoadImage(static_cast<std::string>(path).c_str());

        //Check for error
        ILenum ilError = ilGetError();

        //Image loaded successfully
        if (success != IL_TRUE) {
            ilBindImage(0);
            ilDeleteImages(1, &imageID);
            newAsset->InfoRef().mStatus = infra::AssetStatus::LoadFailed;
        }
        else {
            //Convert image to RGBA
            success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

            if (success == IL_TRUE)
            {
                // If the image is flipped (i.e. upside-down and mirrored, flip it the right way up!)
                ILinfo ImageInfo;
                iluGetImageInfo(&ImageInfo);
                if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT) {
                    iluFlipImage();
                }

                int32_t imageBPP = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
                int32_t imageWidth = ilGetInteger(IL_IMAGE_WIDTH);
                int32_t imageHeight = ilGetInteger(IL_IMAGE_HEIGHT);
                int32_t imageFormat = ilGetInteger(IL_IMAGE_FORMAT);
                int32_t imageType = ilGetInteger(IL_IMAGE_TYPE);

                textureInfo.Height = imageHeight;
                textureInfo.Width = imageWidth;
                textureInfo.BPP = static_cast<TextureBPP>(imageBPP);
                textureInfo.PixelFormat = static_cast<PixelFormat>(imageFormat);
                textureInfo.PixelType = static_cast<PixelType>(imageType);

                int32_t size = imageWidth * imageWidth * imageBPP;
                auto& rawData = newAsset->GetTextureRawData();

                size = imageWidth * imageWidth * 3;
                rawData.resize(size);

                void* data = ilGetData();

                memcpy(&rawData[0], data, size);

                newAsset->SetAsDirty();
                newAsset->InfoRef().mStatus = infra::AssetStatus::LoadSuccessful;
            }
        }

        newAsset->InfoRef().mHandle = UniqueIDGenerator::GetNextID();
        newAsset->InfoRef().mPath = static_cast<std::string>(path);
        newAsset->InfoRef().mLabel = static_cast<std::string>(label);
        newAsset->InfoRef().mLoaderHandle = mAssetLoaderHandle;
        newAsset->SetTextureInfo(textureInfo);

        return newAsset;
    }
    void GenericTextureLoader::Dispose(std::shared_ptr<infra::Asset>) {
    }
}