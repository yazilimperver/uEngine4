#include "texture_asset.h"

#include "texture_info.h"

#include "graphics/color.h"

#include "spdlog/spdlog.h"

//! TODO: Check for android
#ifdef WIN32
    #include <Windows.h>
    #include <GL/glew.h>
#endif

#ifndef ANDROID
    #include <GL/GL.h>
#else
    #include <GLES2/gl2.h>
    #include <GLES/glext.h>
    #include "texture_asset.h"
#endif

namespace gl {
    TextureAsset::TextureAsset()  {
    }

    bool gl::TextureAsset::IsValid() const {
        return !( (mTextureInfo.Width == 0)
            ||
            (mTextureInfo.Height == 0));
    }

    TextureAsset::TextureAsset(const TextureAsset& arg)    {
        mIsDirty = arg.mIsDirty;
        mTextureInfo = arg.mTextureInfo;
        mRawData = arg.mRawData;
    }

    TextureAsset& TextureAsset::operator=(TextureAsset& arg) {
        mIsDirty = arg.mIsDirty;
        mTextureInfo = arg.mTextureInfo;
        mRawData = arg.mRawData;;

        return *this;
    }

    std::optional<Color> TextureAsset::GetPixel(uint32_t x, uint32_t y)    {
        if ((x < mTextureInfo.Width)
            &&
            (y < mTextureInfo.Height)) {
            Color colorToReturn;
            uint32_t rowSize = mTextureInfo.Width * static_cast<uint32_t>(mTextureInfo.BPP);
            uint32_t xIncrement = x * static_cast<uint32_t>(mTextureInfo.BPP);

            switch (static_cast<TextureBPP>(mTextureInfo.BPP)) {
                case TextureBPP::BPP_4:
                    colorToReturn.A = mRawData[y * rowSize + xIncrement + 3U];
                case TextureBPP::BPP_3:
                    colorToReturn.B = mRawData[y * rowSize + xIncrement + 2U];
                case TextureBPP::BPP_2:
                    colorToReturn.G = mRawData[y * rowSize + xIncrement + 1U];
                case TextureBPP::BPP_1:
                    colorToReturn.R = mRawData[y * rowSize + xIncrement];
                    break;
                default:
                    break;
            }

            return colorToReturn;
        }
        else {
            return std::nullopt;
        }
    }

    void TextureAsset::SetPixel(uint32_t x, uint32_t y, const Color& color)  {
        if ((x < mTextureInfo.Width)
            &&
            (y < mTextureInfo.Height)) {
            uint32_t rowSize = mTextureInfo.Width * static_cast<uint32_t>(mTextureInfo.BPP);
            uint32_t xIncrement = x * static_cast<uint32_t>(mTextureInfo.BPP);

            switch (static_cast<TextureBPP>(mTextureInfo.BPP)) {
                case TextureBPP::BPP_4:
                    mRawData[y * rowSize + xIncrement + 3U] = color.A;
                case TextureBPP::BPP_3:
                    mRawData[y * rowSize + xIncrement + 2U] = color.B;
                case TextureBPP::BPP_2:
                    mRawData[y * rowSize + xIncrement + 1U] = color.G;
                case TextureBPP::BPP_1:
                    mRawData[y * rowSize + xIncrement] = color.R;
                    break;
                default:
                    break;
            }

            mIsDirty = true;
        }
    }

    void TextureAsset::BlitPixels(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint8_t* data)     {
        if ((nullptr != data)
            &&
            (x < mTextureInfo.Width)
            &&
            (y < mTextureInfo.Height))
        {
            // Copy pixels rows
            uint32_t bpp = static_cast<uint32_t>(mTextureInfo.BPP);
            
            for (uint32_t i = 0U; i < height; ++i) {
                memcpy(&mRawData[((i + y) * mTextureInfo.Width + x) * bpp], 
                    &data[i * width * bpp],
                    width * bpp);
            }

            mIsDirty = true;
        }
    }

    std::vector<uint8_t>& TextureAsset::GetTextureRawData() {
        return mRawData;
    }

    bool TextureAsset::IsSmoothEnabled() {
        return mTextureInfo.IsSmooth;
    }

    void TextureAsset::SetSmooth(bool smooth) {
        if (smooth != mTextureInfo.IsSmooth) {
            mTextureInfo.IsSmooth = smooth;

            glBindTexture(GL_TEXTURE_2D, mTextureInfo.OpenGLTextureId);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mTextureInfo.IsSmooth ? GL_LINEAR : GL_NEAREST);

            if (mTextureInfo.HasMipmap) {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mTextureInfo.IsSmooth ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_LINEAR);
            }
            else {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mTextureInfo.IsSmooth ? GL_LINEAR : GL_NEAREST);
            }
        }
    }

    bool TextureAsset::IsRepeatedEnabled() {
        return mTextureInfo.IsRepeated;
    }

    void TextureAsset::SetRepeated(bool isRepeated) {
        if (isRepeated != mTextureInfo.IsRepeated) {
            mTextureInfo.IsRepeated = isRepeated;
#ifdef ANDROID
            static bool textureEdgeClamp = true;
#else
            static bool textureEdgeClamp = GLEW_EXT_texture_edge_clamp != 0;
#endif
            if (!mTextureInfo.IsRepeated && !textureEdgeClamp) {
                static bool warned = false;

                if (!warned) {
                    spdlog::error("OpenGL extension SGIS_texture_edge_clamp unavailable");
                    spdlog::error("Artifacts may occur along texture edges");
                    spdlog::error("Ensure that hardware acceleration is enabled if available");
                    warned = true;
                }
            }

            glBindTexture(GL_TEXTURE_2D, mTextureInfo.OpenGLTextureId);
#ifdef ANDROID
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mTextureInfo.mIsRepeated ? GL_REPEAT : (textureEdgeClamp ? GL_CLAMP_TO_EDGE : GL_CLAMP_TO_EDGE));
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mTextureInfo.mIsRepeated ? GL_REPEAT : (textureEdgeClamp ? GL_CLAMP_TO_EDGE : GL_CLAMP_TO_EDGE));
#else
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mTextureInfo.IsRepeated ? GL_REPEAT : (textureEdgeClamp ? GL_CLAMP_TO_EDGE : GL_CLAMP));
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mTextureInfo.IsRepeated ? GL_REPEAT : (textureEdgeClamp ? GL_CLAMP_TO_EDGE : GL_CLAMP));
#endif // ANDROID
        }
    }

    bool TextureAsset::GenerateMipmap()  {
#ifdef ANDROID
        if (!GL_OES_framebuffer_object)
            return false;
#else
        if (!GLEW_EXT_framebuffer_object)
            return false;
#endif
        glBindTexture(GL_TEXTURE_2D, mTextureInfo.OpenGLTextureId);

        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mTextureInfo.IsSmooth ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_LINEAR);

        mTextureInfo.HasMipmap = true;

        return true;
    }

    void TextureAsset::InvalidateMipmap() {
        if (!mTextureInfo.HasMipmap)
            return;

        glBindTexture(GL_TEXTURE_2D, mTextureInfo.OpenGLTextureId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mTextureInfo.IsSmooth ? GL_LINEAR : GL_NEAREST);
        mTextureInfo.HasMipmap = false;
    }

    const infra::AssetInfo& gl::TextureAsset::Info() const {
        return mInfo;
    }
    
    infra::AssetInfo& gl::TextureAsset::InfoRef() {
        return mInfo;
    }
    TextureInfo TextureAsset::GetTextureInfo() const {
        return mTextureInfo;
    }

    void TextureAsset::SetTextureInfo(const TextureInfo& val) {
        mTextureInfo = val;
    }

    bool TextureAsset::IsTextureBinded() {   
        return mTextureInfo.IsEverBinded;
    }

    void TextureAsset::BindTexture() { 
        if (true == this->IsValid()) {
            // a new texture is going to be binded for the first time
            if (false == mTextureInfo.IsEverBinded) {
                if (false == mTextureInfo.IsCompressed) {
                    // Generate a texture name
                    glGenTextures(1, &mTextureInfo.OpenGLTextureId);
                    glBindTexture(GL_TEXTURE_2D, mTextureInfo.OpenGLTextureId);

                    // Set texture clamping method
#ifdef ANDROID
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mTextureInfo.mIsRepeated ? GL_REPEAT : (mTextureInfo.IsTextureClamp ? GL_CLAMP_TO_EDGE : GL_CLAMP_TO_EDGE));
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mTextureInfo.mIsRepeated ? GL_REPEAT : (mTextureInfo.IsTextureClamp ? GL_CLAMP_TO_EDGE : GL_CLAMP_TO_EDGE));
#else
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mTextureInfo.IsRepeated ? GL_REPEAT : (mTextureInfo.IsTextureClamp ? GL_CLAMP_TO_EDGE : GL_CLAMP));
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mTextureInfo.IsRepeated ? GL_REPEAT : (mTextureInfo.IsTextureClamp ? GL_CLAMP_TO_EDGE : GL_CLAMP));
#endif
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mTextureInfo.IsSmooth ? GL_LINEAR : GL_NEAREST);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mTextureInfo.IsSmooth ? GL_LINEAR : GL_NEAREST);

                    /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);*/

                    // Specify the texture specification
                    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                    glTexImage2D(GL_TEXTURE_2D, // Type of texture
                        0,
                        static_cast<uint32_t>(mTextureInfo.PixelFormat),
                        mTextureInfo.Width,
                        mTextureInfo.Height,
                        0,
                        static_cast<uint32_t>(mTextureInfo.PixelFormat),
                        static_cast<uint32_t>(mTextureInfo.PixelType),
                        &mRawData[0]);
                    glBindTexture(GL_TEXTURE_2D, 0);
                }
                else {
                    // Generate a texture name
                    glGenTextures(1, &mTextureInfo.OpenGLTextureId);
                    glBindTexture(GL_TEXTURE_2D, mTextureInfo.OpenGLTextureId);
                    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

                    glCompressedTexImage2D(GL_TEXTURE_2D,
                        0,
                        static_cast<uint32_t>(mTextureInfo.PixelFormat),
                        mTextureInfo.Width,
                        mTextureInfo.Height,
                        0,
                        mTextureInfo.mDDSTextureSize,
                        &mRawData[0]);
                    glBindTexture(GL_TEXTURE_2D, 0);
                }

                mTextureInfo.IsEverBinded = true;
            }
            // image is updated
            else {
                if (false == mTextureInfo.IsCompressed) {
                    glBindTexture(GL_TEXTURE_2D, mTextureInfo.OpenGLTextureId);
                    glTexSubImage2D(GL_TEXTURE_2D,
                        0,
                        0,
                        0,
                        mTextureInfo.Width,
                        mTextureInfo.Height,
                        static_cast<uint32_t>(mTextureInfo.PixelFormat),
                        static_cast<uint32_t>(mTextureInfo.PixelType),
                        &mRawData[0]);
                }
                else {
                    glBindTexture(GL_TEXTURE_2D, mTextureInfo.OpenGLTextureId);
                    glCompressedTexSubImage2D(GL_TEXTURE_2D,
                        0,
                        0,
                        0,
                        mTextureInfo.Width,
                        mTextureInfo.Height,
                        static_cast<uint32_t>(mTextureInfo.PixelFormat),
                        mTextureInfo.mDDSTextureSize,
                        &mRawData[0]);
                }
            }
        }
    }

    uint32_t TextureAsset::GetOpenGLTextureId() const {
        return mTextureInfo.OpenGLTextureId;
    }

}