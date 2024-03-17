/**
 * @file   gl_texture.h
 * @date   6/14/2023
 * @author Yazilimperver
 * @brief  OpenGL font dokulari kullanilacak temel sinif
 *         Bu sinif hem GLPainter hem de bagimsiz opengl doku cizimlerinde kullanilabilir
 * @remark
 */

#ifndef INC_GL_TEXTURE_H
#define INC_GL_TEXTURE_H

#ifdef WIN32
    #include <windows.h>
#endif

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <vector>
#include <string_view>

#include "graphics/rectangle.h"

namespace gl {
    class GLTexture {
        const GLenum cDefaultTextureWrapMode{ GL_REPEAT };
    public:
        GLTexture();
        virtual ~GLTexture();

        /* @brief  DevIL kullanarak dosyadan 32 Bit doku okumak icin kullanilacak API */
        bool LoadTextureFromFile32(std::string_view path);

        /* @brief  DevIL kullanarak dosyadan ham 32 Bit piksel verisi okumak icin kullanilacak API */
        bool LoadPixelsFromFile32(std::string_view path);
        
        /* @brief  DevIL kullanarak dosyadan okunan 32 Bit doku icin renk anahtari ile transparan yaparak dosya okuma */
        bool LoadTextureFromFileWithColorKey32(std::string_view path, GLubyte r, GLubyte g, GLubyte b, GLubyte a = 000);

        /* @brief Sinifia gecirilen en son ham 32 Bit piksel verisi uzerinden GL dokusunu atamak icin kullanilacak API'dir */
        bool LoadTextureFromPixels32();

        /* @brief Verilen ham 32 Bit piksel verisi uzerinden GL dokusunu atamak icin kullanilacak API'dir */
        bool LoadTextureFromPixels32(GLuint* pixels, GLuint imgWidth, GLuint imgHeight, GLuint texWidth, GLuint texHeight);
    
        /* @brief Verilen 32 Bit resim boyutlari icin bos bir sinif hazirlamak icin kullanilacak API'dir */
        void CreatePixels32(GLuint imgWidth, GLuint imgHeight);

        /* @brief Verilen ham 32 Bit piksel verisi ve resim boyutlarini kopyalamak icin kullanilacak API'dir */
        void CopyPixels32(GLuint* pixels, GLuint imgWidth, GLuint imgHeight);
        
        /** @brief 2'nin kati olmayan 32 Bit resimleri 2'ye tamamlamak icin kullanacagimiz API  */
        void PadPixels32();
        
        /* @brief  DevIL kullanarak dosyadan ham 8 Bit piksel verisi okumak icin kullanilacak API */
        bool LoadPixelsFromFile8(std::string_view path);
        
        /* @brief  DevIL kullanarak dosyadan 8 Bit doku okumak icin kullanilacak API */
        bool LoadTextureFromPixels8();

        /* @brief Verilen 8 Bit resim boyutlari icin bos bir sinif hazirlamak icin kullanilacak API'dir */
        void CreatePixels8(GLuint imgWidth, GLuint imgHeight);
       
        /* @brief Verilen ham 8 Bit piksel verisi ve resim boyutlarini kopyalamak icin kullanilacak API'dir */
        void CopyPixels8(GLubyte* pixels, GLuint imgWidth, GLuint imgHeight);

        /** @brief 2'nin kati olmayan 8 Bit resimleri 2'ye tamamlamak icin kullanacagimiz API  */
        void PadPixels8();
        
        /** @brief   Doku/resim verilerini sifirlamak icin kullanacagimiz API */
        virtual void FreeTexture();
        
        /** @brief   GL'den ham doku verilerini sinifa cekmek icin (guncellemek vs) kullanacagimiz API */
        bool RetrieveTextureData();
        
        /** @brief   GL'e ham doku verilerini aktarmak icin kullanacagimiz API */
        bool UpdateTextureData();
        
        /** @brief Ham 32bit resim piksel verilerini almak icin kullanacagimiz API */
        GLuint* PixelData32();
        
        /** @brief Ham 8bit resim piksel verilerini almak icin kullanacagimiz API */
        GLubyte* PixelData8();
        
        /** @brief Spesifik piksel verisi almak ve guncellemek icin kullanacagimiz API */
        GLuint Pixel32(GLuint x, GLuint y) const;
        void UpdatePixel32(GLuint x, GLuint y, GLuint pixel);
        GLubyte Pixel8(GLuint x, GLuint y) const;
        void Pixel8(GLuint x, GLuint y, GLubyte pixel);
        
        /** @brief Dokuyu painter kullanmadan opengl uzerinden cizdirmek icin kullanilacagimiz API */
        void Render(GLfloat x, GLfloat y, infra::Rectangle<float>* clip = NULL);
        
        /** @brief 32bit Dokuyu, hedef doku sinifina kopyalamak icin kullanilacagimiz API */
        void BlitPixels32(GLuint x, GLuint y, GLTexture& destination);
        
        /** @brief 8bit Dokuyu, hedef doku sinifina kopyalamak icin kullanilacagimiz API */
        void BlitPixels8(GLuint x, GLuint y, GLTexture& destination);

        /* @brief   Temel tanimlamalari donmek icin kullanilacak API'lerdir */
        GLuint TextureID() const;
        GLuint TextureWidth() const;
        GLuint TextureHeight() const;
        GLuint ImageWidth() const;
        GLuint ImageHeight() const;
    protected:
        GLuint PowerOfTwo(GLuint num);
        void InitVBO();
        void FreeVBO();

        /** @brief   GL doku tanimlayicisi */
        GLuint mTextureID{ 0 };

        /** @brief   Ham piksel verileri */
        std::vector<GLuint>  mPixels32;
        std::vector<GLubyte> mPixels8;

        /** @brief   Piksel formati */
        GLuint mPixelFormat{ GL_RGBA };

        /** @brief   Doku boyutlari */
        GLuint mTextureWidth{ 0 };
        GLuint mTextureHeight{ 0 };

        /** @brief   Orjinal resim boyutlari */
        GLuint mImageWidth{ 0 };
        GLuint mImageHeight{ 0 };

        /** @brief   VBO/IBO OpenGL tanimlayicilari */
        GLuint mVBOID{ 0 };
        GLuint mIBOID{ 0 };
    };
}

#endif	// INC_GL_TEXTURE_H

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


