#include "gl_texture.h"

#undef _UNICODE
#define ILUT_USE_OPENGL	// This MUST be defined before calling the DevIL headers or we don't get OpenGL functionality

#include <IL/il.h>
#include <IL/ilu.h>

#include "spdlog/spdlog.h"

#include "vertex_data2d.h"

namespace gl {
    GLTexture::GLTexture() {
        // Temel verileri sifirlayalim
        mTextureID = 0;
        mPixelFormat = 0;

        // Resim boyutlarini verelim
        mImageWidth = 0;
        mImageHeight = 0;

        // Doku boyutlarini verelim
        mTextureWidth = 0;
        mTextureHeight = 0;

        // VBO tanimlamalari
        mVBOID = 0;
        mIBOID = 0;
    }

    GLTexture::~GLTexture()   {
        // Doku verilerini bosaltalim
        FreeTexture();

        // VBO/IBO'lari bosaltalim
        FreeVBO();
    }

    bool GLTexture::LoadTextureFromFile32(std::string_view path)  {
        bool textureLoaded = false;

        ILuint imgID = 0;
        ilGenImages(1, &imgID);
        ilBindImage(imgID);

        ILboolean success = ilLoadImage(path.data());

        if (success == IL_TRUE) {
            // Resmi RGBA'ye dondurelim
            success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
            if (success == IL_TRUE) {
                GLuint imgWidth  = static_cast<GLuint>(ilGetInteger(IL_IMAGE_WIDTH));
                GLuint imgHeight = static_cast<GLuint>(ilGetInteger(IL_IMAGE_HEIGHT));
                GLuint texWidth = PowerOfTwo(imgWidth);
                GLuint texHeight = PowerOfTwo(imgHeight);

                // Okunan resim dosyasi 2'nin kati degilse bir takla atiliyor
                if (imgWidth != texWidth || imgHeight != texHeight) {
                    iluImageParameter(ILU_PLACEMENT, ILU_UPPER_LEFT);
                    iluEnlargeCanvas((int32_t)texWidth, (int32_t)texHeight, 1);
                }

                // Dokuyu olusturalim
                textureLoaded = LoadTextureFromPixels32(reinterpret_cast<GLuint*>(ilGetData()), imgWidth, imgHeight, texWidth, texHeight);
            }

            ilDeleteImages(1, &imgID);
            mPixelFormat = GL_RGBA;
        }

        if (!textureLoaded) {
            spdlog::error("Unable to load {}\n", static_cast<std::string>(path));
        }

        return textureLoaded;
    }

    bool GLTexture::LoadPixelsFromFile32(std::string_view path)  {
        // Mevcut dokuyu silelim
        FreeTexture();

        bool pixelsLoaded = false;

        ILuint imgID = 0;
        ilGenImages(1, &imgID);
        ilBindImage(imgID);

        ILboolean success = ilLoadImage(path.data());

        if (success == IL_TRUE) {
            success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
            if (success == IL_TRUE) {
                GLuint imgWidth = (GLuint)ilGetInteger(IL_IMAGE_WIDTH);
                GLuint imgHeight = (GLuint)ilGetInteger(IL_IMAGE_HEIGHT);
                GLuint texWidth = PowerOfTwo(imgWidth);
                GLuint texHeight = PowerOfTwo(imgHeight);

                if (imgWidth != texWidth || imgHeight != texHeight) {
                    iluImageParameter(ILU_PLACEMENT, ILU_UPPER_LEFT);
                    iluEnlargeCanvas((int32_t)texWidth, (int32_t)texHeight, 1);
                }

                GLuint size = texWidth * texHeight;
                mPixels32.resize(size);

                mImageWidth = imgWidth;
                mImageHeight = imgHeight;
                mTextureWidth = texWidth;
                mTextureHeight = texHeight;

                memcpy(&mPixels32[0], ilGetData(), size * 4);
                pixelsLoaded = true;
            }

            ilDeleteImages(1, &imgID);

            mPixelFormat = GL_RGBA;
        }

        if (!pixelsLoaded) {
            spdlog::error("Unable to load {}\n", static_cast<std::string>(path));
        }

        return pixelsLoaded;
    }

    bool GLTexture::LoadTextureFromFileWithColorKey32(std::string_view path, GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
        if (!LoadPixelsFromFile32(path)) {
            return false;
        }

        GLuint size = mTextureWidth * mTextureHeight;
        for (uint32_t i = 0; i < size; ++i) {
            GLubyte* colors = reinterpret_cast<GLubyte*>(&mPixels32[0]);

            // Tutan renkleri transparan yapalim
            if (colors[0] == r && colors[1] == g && colors[2] == b && (0 == a || colors[3] == a)) {
                colors[0] = 255;
                colors[1] = 255;
                colors[2] = 255;
                colors[3] = 000;
            }
        }

        if (!LoadTextureFromPixels32()) {
            return false;
        }

        mPixelFormat = GL_RGBA;

        return true;
    }

    bool GLTexture::LoadTextureFromPixels32()  {
        bool success = true;

        if (mTextureID == 0 && mPixels32.size() != 0) {
            glGenTextures(1, &mTextureID);
            glBindTexture(GL_TEXTURE_2D, mTextureID);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mTextureWidth, mTextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, &mPixels32[0]);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, cDefaultTextureWrapMode);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, cDefaultTextureWrapMode);

            glBindTexture(GL_TEXTURE_2D, 0);

            GLenum error = glGetError();
            if (error != GL_NO_ERROR)      {
                spdlog::error("Error loading texture from pixels! Error: {}\n", reinterpret_cast<const char*>(gluErrorString(error)));
                success = false;
            }
            else {
                mPixels32.clear();

                InitVBO();
                mPixelFormat = GL_RGBA;
            }
        }
        else {
            spdlog::error("Cannot load texture from current pixels! ");

            if (mTextureID != 0) {
                spdlog::error("A texture is already loaded!\n");
            }
            else if (mPixels32.size() == 0) {
                spdlog::error("No pixels to create texture from!\n");
            }

            success = false;
        }

        return success;
    }

    bool GLTexture::LoadTextureFromPixels32(GLuint* pixels, GLuint imgWidth, GLuint imgHeight, GLuint texWidth, GLuint texHeight) {
        FreeTexture();

        mImageWidth = imgWidth;
        mImageHeight = imgHeight;
        mTextureWidth = texWidth;
        mTextureHeight = texHeight;

        glGenTextures(1, &mTextureID);
        glBindTexture(GL_TEXTURE_2D, mTextureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mTextureWidth, mTextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, cDefaultTextureWrapMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, cDefaultTextureWrapMode);

        glBindTexture(GL_TEXTURE_2D, 0);

        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            spdlog::error("Error loading texture from pixels! Error: {}\n", reinterpret_cast<const char*>(gluErrorString(error)));
            return false;
        }

        InitVBO();

        mPixelFormat = GL_RGBA;
        return true;
    }

    void GLTexture::CreatePixels32(GLuint imgWidth, GLuint imgHeight) {
        if (imgWidth > 0 && imgHeight > 0) {
            FreeTexture();

            GLuint size = imgWidth * imgHeight;
            mPixels32.resize(size);            
            memset(&mPixels32[0], 0, size * 4);

            mImageWidth = imgWidth;
            mImageHeight = imgHeight;
            mTextureWidth = mImageWidth;
            mTextureHeight = mImageWidth;

            mPixelFormat = GL_RGBA;
        }
    }

    void GLTexture::CopyPixels32(GLuint* pixels, GLuint imgWidth, GLuint imgHeight) {
        if (imgWidth > 0 && imgHeight > 0) {
            FreeTexture();

            GLuint size = imgWidth * imgHeight;
            mPixels32.resize(size);
            memset(&mPixels32[0], 0, size * 4);

            mImageWidth = imgWidth;
            mImageHeight = imgHeight;
            mTextureWidth = mImageWidth;
            mTextureHeight = mImageWidth;

            mPixelFormat = GL_RGBA;
        }
    }

    void GLTexture::PadPixels32() {
        if (mPixels32.size() > 0) {
            GLuint oTextureWidth = mTextureWidth;
            GLuint oTextureHeight = mTextureHeight;

            mTextureWidth = PowerOfTwo(mImageWidth);
            mTextureHeight = PowerOfTwo(mImageHeight);

            if (mTextureWidth != mImageWidth || mTextureHeight != mImageHeight) {
                GLuint size = mTextureWidth * mTextureHeight;
                std::vector<GLuint> pixels;
                pixels.resize(size);

                for (uint32_t i = 0; i < mImageHeight; ++i){
                    memcpy(&pixels[i * mTextureWidth], &mPixels32[i * oTextureWidth], mImageWidth * 4);
                }

                mPixels32 = pixels;
            }
        }
    }

    bool GLTexture::LoadPixelsFromFile8(std::string_view path) {
        FreeTexture();

        bool pixelsLoaded = false;

        ILuint imgID = 0;
        ilGenImages(1, &imgID);
        ilBindImage(imgID);

        ILboolean success = ilLoadImage(path.data());

        if (success == IL_TRUE) {
            success = ilConvertImage(IL_LUMINANCE, IL_UNSIGNED_BYTE);
            if (success == IL_TRUE) {
                GLuint imgWidth = (GLuint)ilGetInteger(IL_IMAGE_WIDTH);
                GLuint imgHeight = (GLuint)ilGetInteger(IL_IMAGE_HEIGHT);

                GLuint texWidth = PowerOfTwo(imgWidth);
                GLuint texHeight = PowerOfTwo(imgHeight);

                if (imgWidth != texWidth || imgHeight != texHeight) {
                    iluImageParameter(ILU_PLACEMENT, ILU_UPPER_LEFT);
                    iluEnlargeCanvas((int32_t)texWidth, (int32_t)texHeight, 1);
                }

                GLuint size = texWidth * texHeight;
                mPixels8.resize(size);

                mImageWidth = imgWidth;
                mImageHeight = imgHeight;
                mTextureWidth = texWidth;
                mTextureHeight = texHeight;

                memcpy(&mPixels8[0], ilGetData(), size);
                pixelsLoaded = true;
            }

            ilDeleteImages(1, &imgID);

            mPixelFormat = GL_ALPHA;
        }

        if (!pixelsLoaded) {
            spdlog::error("Unable to load {}\n", static_cast<std::string>(path));
        }

        return pixelsLoaded;
    }

    bool GLTexture::LoadTextureFromPixels8() {
        bool success = true;

        if (mTextureID == 0 && mPixels8.size() > 0) {
            glGenTextures(1, &mTextureID);
            glBindTexture(GL_TEXTURE_2D, mTextureID);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, mTextureWidth, mTextureHeight, 0, GL_ALPHA, GL_UNSIGNED_BYTE, &mPixels8[0]);
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, cDefaultTextureWrapMode);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, cDefaultTextureWrapMode);
            
            glBindTexture(GL_TEXTURE_2D, 0);
            
            GLenum error = glGetError();
            if (error != GL_NO_ERROR) {
                spdlog::error("Error loading texture from pixels! {}\n", reinterpret_cast<const char*>(gluErrorString(error)));
                success = false;
            }
            else {
                mPixels8.clear();
                InitVBO();
                mPixelFormat = GL_ALPHA;
            }
        }
        else {
            spdlog::error("Cannot load texture from current pixels! ");

            if (mTextureID != 0) {
                spdlog::error("A texture is already loaded!\n");
            }
            else if (mPixels8.size() == 0) {
                spdlog::error("No pixels to create texture from!\n");
            }
        }

        return success;
    }

    void GLTexture::CreatePixels8(GLuint imgWidth, GLuint imgHeight) {
        if (imgWidth > 0 && imgHeight > 0) {
            FreeTexture();

            GLuint size = imgWidth * imgHeight;
            mPixels8.resize(size);
            memset(&mPixels8[0], 0, size);

            mImageWidth = imgWidth;
            mImageHeight = imgHeight;
            mTextureWidth = mImageWidth;
            mTextureHeight = mImageWidth;

            mPixelFormat = GL_ALPHA;
        }
    }

    void GLTexture::CopyPixels8(GLubyte* pixels, GLuint imgWidth, GLuint imgHeight) {
        if (imgWidth > 0 && imgHeight > 0) {
            FreeTexture();

            GLuint size = imgWidth * imgHeight;
            mPixels8.resize(size);
            memcpy(&mPixels8[0], pixels, size);

            mImageWidth = imgWidth;
            mImageHeight = imgHeight;
            mTextureWidth = mImageWidth;
            mTextureHeight = mImageWidth;

            mPixelFormat = GL_ALPHA;
        }
    }

    void GLTexture::PadPixels8() {
        if (mPixels8.size() > 0) {
            GLuint oTextureWidth = mTextureWidth;
            GLuint oTextureHeight = mTextureHeight;

            mTextureWidth = PowerOfTwo(mImageWidth);
            mTextureHeight = PowerOfTwo(mImageHeight);

            if (mTextureWidth != mImageWidth || mTextureHeight != mImageHeight) {
                GLuint size = mTextureWidth * mTextureHeight;
                std::vector<GLubyte> pixels;
                pixels.resize(size);

                for (uint32_t i = 0; i < mImageHeight; ++i) {
                    memcpy(&pixels[i * mTextureWidth], &mPixels8[i * oTextureWidth], mImageWidth);
                }
                
                mPixels8.clear();
                mPixels8 = pixels;
            }
        }
    }

    void GLTexture::FreeTexture() {
        if (mTextureID != 0) {
            glDeleteTextures(1, &mTextureID);
            mTextureID = 0;
        }

        mPixels32.clear();
        mPixels8.clear();

        mImageWidth = 0;
        mImageHeight = 0;
        mTextureWidth = 0;
        mTextureHeight = 0;
        mPixelFormat = 0;
    }

    bool GLTexture::RetrieveTextureData() {
        if (mPixels32.size() == 0 && mPixels8.size() == 0 && mTextureID != 0) {
            GLuint size = mTextureWidth * mTextureHeight;
            if (mPixelFormat == GL_RGBA) {
                mPixels32.resize(size);
            }
            else if (mPixelFormat == GL_ALPHA) {
                mPixels8.resize(size);
            }

            glBindTexture(GL_TEXTURE_2D, mTextureID);
            glGetTexImage(GL_TEXTURE_2D, 0, mPixelFormat, GL_UNSIGNED_BYTE, &mPixels32[0]);
            glBindTexture(GL_TEXTURE_2D, 0);

            return true;
        }

        return false;
    }

    bool GLTexture::UpdateTextureData() {
        if (mPixels32.size() == 0 && mPixels8.size() == 0 && mTextureID != 0) {
            glBindTexture(GL_TEXTURE_2D, mTextureID);
            void* pixels = (mPixelFormat == GL_RGBA) ? reinterpret_cast<void*>(&mPixels32[0]) : reinterpret_cast<void*>(&mPixels8[0]);
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mTextureWidth, mTextureHeight, mPixelFormat, GL_UNSIGNED_BYTE, pixels);

            mPixels32.clear();
            mPixels8.clear();

            glBindTexture(GL_TEXTURE_2D, 0);

            return true;
        }

        return false;
    }

    GLuint* GLTexture::PixelData32()   {
        return &mPixels32[0];
    }

    GLubyte* GLTexture::PixelData8()   {
        return &mPixels8[0];
    }

    GLuint GLTexture::Pixel32(GLuint x, GLuint y) const {
        return mPixels32[y * mTextureWidth + x];
    }

    void GLTexture::UpdatePixel32(GLuint x, GLuint y, GLuint pixel)   {
        mPixels32[y * mTextureWidth + x] = pixel;
    }

    GLubyte GLTexture::Pixel8(GLuint x, GLuint y) const {
        return mPixels8[y * mTextureWidth + x];
    }

    void GLTexture::Pixel8(GLuint x, GLuint y, GLubyte pixel)   {
        mPixels8[y * mTextureWidth + x] = pixel;
    }

    void GLTexture::Render(GLfloat x, GLfloat y, infra::Rectangle<float>* clip) {
        if (mTextureID != 0)   {
            // Mevcut durumu koruyalim
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();

            GLfloat texTop = 0.f;
            GLfloat texBottom = static_cast<float>(mImageHeight) / static_cast<float>(mTextureHeight);
            GLfloat texLeft = 0.f;
            GLfloat texRight = static_cast<float>(mImageWidth) / static_cast<float>(mTextureWidth);

            GLfloat quadWidth  = static_cast<float>(mImageWidth);
            GLfloat quadHeight = static_cast<float>(mImageHeight);

            if (clip != NULL)   {
                texLeft = clip->Left / mTextureWidth;
                texRight = (clip->Left + clip->Width) / mTextureWidth;
                texTop = clip->Top / mTextureHeight;
                texBottom = (clip->Top + clip->Height) / mTextureHeight;

                quadWidth = clip->Width;
                quadHeight = clip->Height;
            }

            glTranslatef(x, y, 0.f);

            VertexData2D vData[4];

            vData[0].TexCoord.s = texLeft; vData[0].TexCoord.t = texTop;
            vData[1].TexCoord.s = texRight; vData[1].TexCoord.t = texTop;
            vData[2].TexCoord.s = texRight; vData[2].TexCoord.t = texBottom;
            vData[3].TexCoord.s = texLeft; vData[3].TexCoord.t = texBottom;

            vData[0].Position.x = 0.f; vData[0].Position.y = 0.f;
            vData[1].Position.x = quadWidth; vData[1].Position.y = 0.f;
            vData[2].Position.x = quadWidth; vData[2].Position.y = quadHeight;
            vData[3].Position.x = 0.f; vData[3].Position.y = quadHeight;

            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, mTextureID);

            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);

            glBindBuffer(GL_ARRAY_BUFFER, mVBOID);
            glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * sizeof(VertexData2D), vData);

            glTexCoordPointer(2, GL_FLOAT, sizeof(VertexData2D), (GLvoid*)offsetof(VertexData2D, TexCoord));
            glVertexPointer(2, GL_FLOAT, sizeof(VertexData2D), (GLvoid*)offsetof(VertexData2D, Position));

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBOID);
            glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, NULL);

            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            glDisableClientState(GL_VERTEX_ARRAY);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);

            glMatrixMode(GL_MODELVIEW);
            glPopMatrix();
        }
    }

    void GLTexture::BlitPixels32(GLuint x, GLuint y, GLTexture& destination) {
        if (mPixels32.size() > 0 && destination.mPixels32.size() > 0) {
            GLuint* dPixels = &destination.mPixels32[0];
            GLuint* sPixels = &mPixels32[0];
            
            for (uint32_t i = 0; i < mImageHeight; ++i) {
                memcpy(&dPixels[(i + y) * destination.mTextureWidth + x], &sPixels[i * mTextureWidth], mImageWidth * 4);
            }
        }
    }

    void GLTexture::BlitPixels8(GLuint x, GLuint y, GLTexture& destination) {
        if (mPixels8.size() > 0 && destination.mPixels8.size() > 0) {
            GLubyte* dPixels = &destination.mPixels8[0];
            GLubyte* sPixels = &mPixels8[0];

            for (uint32_t i = 0; i < mImageHeight; ++i) {
                memcpy(&dPixels[(i + y) * destination.mTextureWidth + x], &sPixels[i * mTextureWidth], mImageWidth);
            }
        }
    }

    GLuint GLTexture::TextureID() const{
        return mTextureID;
    }

    GLuint GLTexture::TextureWidth() const {
        return mTextureWidth;
    }

    GLuint GLTexture::TextureHeight() const {
        return mTextureHeight;
    }

    GLuint GLTexture::ImageWidth() const  {
        return mImageWidth;
    }

    GLuint GLTexture::ImageHeight() const {
        return mImageHeight;
    }

    GLuint GLTexture::PowerOfTwo(GLuint num) {
        if (num != 0) {
            num--;
            num |= (num >> 1); //Or first 2 bits
            num |= (num >> 2); //Or next 2 bits
            num |= (num >> 4); //Or next 4 bits
            num |= (num >> 8); //Or next 8 bits
            num |= (num >> 16); //Or next 16 bits
            num++;
        }

        return num;
    }

    void GLTexture::InitVBO() {
        if (mTextureID != 0 && mVBOID == 0) {
            VertexData2D vData[4];
            GLuint iData[4];

            iData[0] = 0;
            iData[1] = 1;
            iData[2] = 2;
            iData[3] = 3;

            // VBO Olustur
            glGenBuffers(1, &mVBOID);
            glBindBuffer(GL_ARRAY_BUFFER, mVBOID);
            glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(VertexData2D), vData, GL_DYNAMIC_DRAW);

            // IBO Olustur
            glGenBuffers(1, &mIBOID);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBOID);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), iData, GL_DYNAMIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    }

    void GLTexture::FreeVBO() {
        if (mVBOID != 0) {
            glDeleteBuffers(1, &mVBOID);
            glDeleteBuffers(1, &mIBOID);
        }
    }
}