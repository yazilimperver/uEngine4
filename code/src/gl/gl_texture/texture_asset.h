/**
 * @file   texture_asset.h
 * @date   5/22/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_TEXTURE_ASSET_H
#define INC_TEXTURE_ASSET_H

#include <optional>
#include <cstddef>
#include <vector>

#include "texture_info.h"
#include "texture_common.h"

#include "asset/asset.h"

class  Color;

namespace gl {

    //! TODO: Mutex control is required for simultaneous texture updates
    class TextureAsset
        : public infra::Asset {
    public:
        TextureAsset();
        TextureAsset(const TextureAsset& arg);
        TextureAsset& operator=(TextureAsset& data);

        std::optional<Color> GetPixel(uint32_t x, uint32_t y);

        //! Set pixels according to pixel format
        void SetPixel(uint32_t x, uint32_t y, const Color& color);

        //! Blit method. Copy provided data into texture according to provided parameters
        void BlitPixels(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint8_t* data);

        //! Obtain Texture raw data
        std::vector<uint8_t>& GetTextureRawData();

        //! Setting texture parameters
        bool IsSmoothEnabled();
        void SetSmooth(bool smooth);

        bool IsRepeatedEnabled();
        void SetRepeated(bool isRepeated);

        bool GenerateMipmap();
        void InvalidateMipmap();

        //! Is texture asset valid
        bool IsValid() const override;

        uint32_t GetOpenGLTextureId() const;
        virtual const infra::AssetInfo& Info() const override;
        infra::AssetInfo& InfoRef();

        TextureInfo GetTextureInfo() const;
        void SetTextureInfo(const TextureInfo& val);

        //! Bind texture to opengl
        bool IsTextureBinded();
        void BindTexture() const;

    protected:

        infra::AssetInfo mInfo;

        //! Ortak kullanilabilecek havuzdan alinacak doku bilgisi!  
        mutable TextureInfo mTextureInfo;

        //! Raw image data
        std::vector<uint8_t> mRawData;
    };
}

#endif    // INC_TEXTURE_ASSET_H

/**
Copyright (c) [2023][Yazilimperver - yazilimpervergs@gmail.com]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */


