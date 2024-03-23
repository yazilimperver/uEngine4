/**
 * @file   texture_info.h
 * @date   5/22/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_TEXTURE_INFO_H
#define INC_TEXTURE_INFO_H

#include "texture_common.h"

#include "pixel_type.h"
#include "pixel_format.h"
#include "texture_bpp.h"

namespace gl {
    struct TextureInfo {
        uint32_t           OpenGLTextureId = 0;
        bool               IsEverBinded = false;
        uint32_t           Width = 1;
        uint32_t           Height = 1;
        gl::PixelType      PixelType;
        gl::PixelFormat    PixelFormat;
        // TODO internal pixel format
        gl::TextureBPP     BPP;
        bool               IsCompressed;
        bool               HasMipmap = false;
        uint32_t           MipMapCount = 0;
        TextureAssetHandle TextureHandle = -1;
        bool               IsRepeated = false;
        bool               IsSmooth = true;
        bool               IsTextureClamp = true;
        bool               PixelsFlipped = false;
        
        //! will be used for compressed DDS Textures to prevent additional calculations at bind time
        uint32_t mDDSTextureSize;
        
        void Initialize()
        {
            OpenGLTextureId = 0;
            IsEverBinded = false;
            Width = 1;
            Height = 1;
            HasMipmap = false;
            MipMapCount = 0;
            TextureHandle = -1;
            IsRepeated = false;
            IsSmooth = true;
            IsTextureClamp = true;
            PixelsFlipped = false;
        }
    };
}

#endif	// INC_TEXTURE_INFO_H

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


