/**
 * @file   gl_sprite_sheet.h
 * @date   6/17/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_GL_SPRITE_SHEET_H
#define INC_GL_SPRITE_SHEET_H

#include <vector>

#include "gl_texture.h"
#include "vertex_data2d.h"

namespace gl {
    /** @brief   Sprite cizimi icin referans noktasi */    
    enum class SpriteOrigin {
        Center,
        TopLeft,
        BottomLeft,
        TopRight,
        BottomRight
    };

    class GLSpriteSheet
        : public GLTexture {
    public:
        GLSpriteSheet();
        ~GLSpriteSheet();

        /** @brief   Sprite parcasi/GLFont spritesheet dikdortgenleri eklemek icin kullanilacak fonksiyon */
        size_t AddClipSprite(infra::Rectangle<float>& newClip);

        /** @brief   GLFont spritesheet dikdortgenleri parcasi donmek icin kullanilacak fonksiyon */
        infra::Rectangle<float> Clip(int32_t index) const;
        
        /** @brief   Gerekli buffer'larin olusturulmasi icin kullanilacak API */
        bool GenerateDataBuffer(SpriteOrigin origin = SpriteOrigin::Center);

        /** @brief   Spritesheet'i temizlemek icin kullanilacak API */
        void FreeSheet();
        
        /** @brief   Doku ve Spritesheet'i temizlemek icin kullanilacak API */
        void FreeTexture();
        
        /** @brief   Sprisheet icerisinde verilen parcayi cizdirmek icin kullanilacak API */
        void RenderSprite(int32_t index);
    protected:
        /** @brief   GLFont spritesheet dikdortgenleri */
        std::vector<infra::Rectangle<float>> mClips;

        /** @brief   VBO/IBO verileri */
        GLuint mVertexDataBuffer;

        /** @brief   Index buffers */
        std::vector<GLuint> mIndexBuffers;
    };
}

#endif	// INC_FONT_SPRITE_SHEET_H

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


