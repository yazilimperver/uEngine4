/**
 * @file   gl_font.h
 * @date   6/17/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_FONT_H
#define INC_FONT_H

#include <string_view>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "gl_sprite_sheet.h"

namespace gl {
    class GLFont 
        : private GLSpriteSheet {
    public:
        GLFont();
        virtual ~GLFont();

        /* @brief  Verilen dosyadan ilgili fontu okuman icin kullanilacak olan API */
        bool LoadFromBitmap(std::string_view path);

        /* @brief  Verilen dosyayi ve fontu okuyarak ilgili hazirliklari yapar */
        bool LoadFreeType(std::string_view path, GLuint pixelSize);

        /** @brief GLFont verilerini sifirlar */
        void FreeFont();

        /** @brief Verilen konumda metni cizer */
        void RenderText(GLfloat x, GLfloat y, std::string_view text);

    private:
        /** @brief Freetype kutuphanesi nesnesi */
        static FT_Library mLibrary;

        /** @brief GLFont bosluk parametreleri */
        GLfloat mSpace;
        GLfloat mLineHeight;
        GLfloat mNewLine;
    };
}

#endif	// INC_FONT_H

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


