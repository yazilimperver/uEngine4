#include "gl_font.h"
#include FT_BITMAP_H

#include "spdlog/spdlog.h"

namespace gl {
    FT_Library GLFont::mLibrary;

    GLFont::GLFont()   {
        mSpace = 0.f;
        mLineHeight = 0.f;
        mNewLine = 0.f;
    }

    GLFont::~GLFont()  {
        FreeFont();
    }

    bool GLFont::LoadFromBitmap(std::string_view path)   {
        bool isLoadSuccess = true;

        // arka plan pikseli
        const GLubyte BLACK_PIXEL = 0x00;

        // Zaten yuklenmis fontu once temizleyelim
        FreeFont();

        // GLFont imaj pikselini okuyalim
        if (LoadPixelsFromFile8(path))    {
            GLfloat cellW = ImageWidth() / 16.f;
            GLfloat cellH = ImageHeight() / 16.f;

            GLuint top = static_cast<GLuint>(cellH);
            GLuint bottom = 0;
            GLuint aBottom = 0;

            int32_t pX = 0;
            int32_t pY = 0;

            int32_t bX = 0;
            int32_t bY = 0;

            // Dosyayi ayristirmaya baslayalim
            GLuint currentChar = 0;
            infra::Rectangle<float> nextClip = { 0.f, 0.f, cellW, cellH };

            // Satirdaki hucreleri dolasalim
            for (uint32_t rows = 0; rows < 16; ++rows)   {
                // Ilgili satirdaki butun sutunlara bakalim
                for (uint32_t cols = 0; cols < 16; ++cols)    {
                    // Hucreyi ayiklayalim
                    // Temel ofsetleri ayarlayalim
                    bX = static_cast<int32_t>(cellW * cols);
                    bY = static_cast<int32_t>(cellH * rows);

                    // Hucre dikdortgenini olusturalim
                    nextClip.Left = cellW * cols;
                    nextClip.Top = cellH * rows;

                    nextClip.Width = cellW;
                    nextClip.Height = cellH;

                    // Karakterin SOL sinirini bulalim
                    for (int32_t pCol = 0; pCol < cellW; ++pCol)   {
                        for (int32_t pRow = 0; pRow < cellH; ++pRow)   {
                            // Pixel offset
                            pX = bX + pCol;
                            pY = bY + pRow;

                            // Ilk arkaplan renginde olmayan piksel bulundu
                            if (Pixel8(pX, pY) != BLACK_PIXEL)   {
                                // Piksel x offsetini ayarla
                                nextClip.Left = static_cast<float>(pX);

                                // donguden cikalim
                                pCol = static_cast<int32_t>(cellW);
                                pRow = static_cast<int32_t>(cellH);
                            }
                        }
                    }

                    // Karakterin SAG sinirini bulalim
                    for (int32_t pCol_w = static_cast<int32_t>(cellW - 1.0F); pCol_w >= 0; pCol_w--)  {
                        for (int32_t pRow_w = 0; pRow_w < cellH; pRow_w++)   {
                            pX = bX + pCol_w;
                            pY = bY + pRow_w;

                            if (Pixel8(pX, pY) != BLACK_PIXEL)   {
                                nextClip.Width = (pX - nextClip.Left) + 1;

                                pCol_w = -1;
                                pRow_w = static_cast<int32_t>(cellH);
                            }
                        }
                    }

                    // Karakterin UST sinirini bulalim
                    for (uint32_t pRow = 0; pRow < cellH; ++pRow)   {
                        for (uint32_t pCol = 0; pCol < cellW; ++pCol)  {
                            pX = bX + pCol;
                            pY = bY + pRow;

                            if (Pixel8(pX, pY) != BLACK_PIXEL)     {
                                if (pRow < top)      {
                                    top = pRow;
                                }

                                pCol = static_cast<uint32_t>(cellW);
                                pRow = static_cast<uint32_t>(cellH);
                            }
                        }
                    }

                    // Karakterin ALT sinirini bulalim
                    for (int32_t pRow_b = static_cast<int32_t>(cellH - 1.0F); pRow_b >= 0; --pRow_b)     {
                        for (int32_t pCol_b = 0; pCol_b < cellW; ++pCol_b)    {
                            pX = bX + pCol_b;
                            pY = bY + pRow_b;

                            if (Pixel8(pX, pY) != BLACK_PIXEL)    {
                                if (currentChar == 'A')    {
                                    aBottom = pRow_b;
                                }

                                if (static_cast<uint32_t>(pRow_b) > bottom)   {
                                    bottom = pRow_b;
                                }

                                pCol_b = static_cast<int32_t>(cellW);
                                pRow_b = -1;
                            }
                        }
                    }

                    // Bir sonraki karaktere gecelim
                    mClips.push_back(nextClip);
                    ++currentChar;
                }
            }

            // Ust kisimlarini ayarlayalim
            for (int32_t t = 0; t < 256; ++t) {
                mClips[t].Top += top;
                mClips[t].Height -= top;
            }

            // Okunan piksellerden dokuyu olusturalim
            if (LoadTextureFromPixels8())  {
                // Vertex buffer'i sprite sheet verisinden olusturalim
                if (!GenerateDataBuffer(SpriteOrigin::TopLeft))   {
                    spdlog::error("Unable to create vertex buffer for bitmap font!\n");
                    isLoadSuccess = false;
                }
            }
            else   {
                spdlog::error("Unable to create texture from bitmap font pixels!\n");
                isLoadSuccess = false;
            }

            glBindTexture(GL_TEXTURE_2D, TextureID());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

            // Bosluk degiskenlerini ayarlayalim
            mSpace      = static_cast<float>(cellW / 2.0F);
            mNewLine    = static_cast<float>(aBottom - top);
            mLineHeight = static_cast<float>(bottom - top);
        }
        else  {
            spdlog::error("Could not load bitmap font image: {}!\n", static_cast<std::string>(path));
            isLoadSuccess = false;
        }

        return isLoadSuccess;
    }

    bool GLFont::LoadFreeType(std::string_view path, GLuint pixelSize) {
        FT_Error error = NULL;
        
        error = FT_Init_FreeType(&mLibrary);
        if (error) {
            printf("FreeType error:%X", error);
            return false;
        }

        // Hucre boyutlari
        GLuint cellW = 0;
        GLuint cellH = 0;
        int32_t maxBearing = 0;
        int32_t minHang = 0;

        // Karakter verileri
        std::vector<GLTexture> bitmaps;
        bitmaps.resize(256);

        std::vector<FT_Glyph_Metrics> metrics;
        metrics.resize(256);

        FT_Face face = NULL;

        error = FT_New_Face(mLibrary, path.data(), 0, &face);
        if (!error)   {

            // Face boyutunu ayarlayalim
            error = FT_Set_Pixel_Sizes(face, 0, pixelSize);
            if (!error)  {

                // ASCII karakterleri uzerinden giderek glyph verilerini alalim
                for (int32_t i = 0; i < 256; ++i)  {
                    // Ilgili karakteri yukleyip gorsellestirelim
                    error = FT_Load_Char(face, i, FT_LOAD_RENDER);
                    if (!error)   {
                        // Metrikleri alalim
                        metrics[i] = face->glyph->metrics;

                        // Glpyh verisini kopyalayalim
                        bitmaps[i].CopyPixels8(face->glyph->bitmap.buffer, face->glyph->bitmap.width, face->glyph->bitmap.rows);

                        // Bearing degerini hesaplayalim
                        if (metrics[i].horiBearingY / 64 > maxBearing)     {
                            maxBearing = metrics[i].horiBearingY / 64;
                        }

                        // Maks genisligi hesaplayalim
                        if (static_cast<uint32_t>(metrics[i].width / 64) > cellW) {
                            cellW = metrics[i].width / 64;
                        }

                        // Calculate gylph hang
                        int32_t glyphHang = (metrics[i].horiBearingY - metrics[i].height) / 64;
                        if (glyphHang < minHang)  {
                            minHang = glyphHang;
                        }
                    }
                    else {
                        spdlog::error("Unable to load glyph. FreeType error:%X\n", error);
                        error = NULL;
                    }
                }

                // Bitmap ham font verisini olusturalim
                cellH = maxBearing - minHang;
                CreatePixels8(cellW * 16, cellH * 16);

                // GLFont bitmap verisini olusturalim
                GLuint currentChar = 0;
                infra::Rectangle<float> nextClip = { 0.f, 0.f, static_cast<float>(cellW), static_cast<float>(cellH) };

                // Cizim kordinatlari
                int32_t bX = 0;
                int32_t bY = 0;

                // Satirdaki hucreleri dolasalim
                for (uint32_t rows = 0; rows < 16; rows++) {
                    // Ilgili satirdaki butun sutunlara bakalim
                    for (uint32_t cols = 0; cols < 16; cols++)  {
                        // Hucreyi ayiklayalim
                        // Temel ofsetleri ayarlayalim
                        bX = cellW * cols;
                        bY = cellH * rows;

                        // Hucre dikdortgenini olusturalim
                        nextClip.Left = static_cast<float>(bX);
                        nextClip.Top  = static_cast<float>(bY);
                        nextClip.Width = static_cast<float>(metrics[currentChar].width / 64.0F);
                        nextClip.Height = static_cast<float>(cellH);

                        // Karakteri cizdirelim
                        bitmaps[currentChar].BlitPixels8(bX, bY + maxBearing - metrics[currentChar].horiBearingY / 64, *this);

                        // Sonraki karaktere gecelim
                        mClips.push_back(nextClip);
                        currentChar++;
                    }
                }

                // Dokuyu 2'nin kati yapalim
                PadPixels8();

                // Okunan piksellerden dokuyu olusturalim
                if (LoadTextureFromPixels8()) {
                    // Vertex buffer'i sprite sheet verisinden olusturalim
                    if (!GenerateDataBuffer(SpriteOrigin::TopLeft))  {
                        spdlog::error("Unable to create vertex buffer for bitmap font!");
                        error = 0xA2;
                    }
                }
                else   {
                    spdlog::error("Unable to create texture from generated bitmap font!\n");
                    error = 0xA2;
                }
                
                glBindTexture(GL_TEXTURE_2D, TextureID());
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

                // Bosluk degiskenlerini ayarlayalim
                mSpace = static_cast<float>(cellW / 2.0F);
                mNewLine = static_cast<float>(maxBearing);
                mLineHeight = static_cast<float>(cellH);
            }
            else  {
                spdlog::error("Unable to set font size. FreeType error:%X\n", error);
            }

            FT_Done_Face(face);
        }
        else    {
            spdlog::error("Unable to load load font face. FreeType error:%X\n", error);
            return false;
        }

        FT_Done_FreeType(mLibrary);
        return error == NULL;
    }

    void GLFont::FreeFont()  {
        FreeTexture();

        mSpace = 0.f;
        mLineHeight = 0.f;
        mNewLine = 0.f;
    }

    void GLFont::RenderText(GLfloat x, GLfloat y, std::string_view text)   {
        if (TextureID() != 0) {
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();

            GLfloat dX = x;
            GLfloat dY = y;

            glTranslatef(x, y, 0.f);

            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, TextureID());

            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);

            glBindBuffer(GL_ARRAY_BUFFER, mVertexDataBuffer);
            glTexCoordPointer(2, GL_FLOAT, sizeof(VertexData2D), (GLvoid*)offsetof(VertexData2D, TexCoord));
            glVertexPointer(2, GL_FLOAT, sizeof(VertexData2D), (GLvoid*)offsetof(VertexData2D, Position));

            for (int32_t i = 0; i < text.length(); ++i) {
                // Bosluk
                if (text[i] == ' ') {
                    glTranslatef(mSpace, 0.f, 0.f);
                    dX += mSpace;
                }
                // Yeni satir
                else if (text[i] == '\n') {
                    glTranslatef(x - dX, mNewLine, 0.f);
                    dY += mNewLine;
                    dX += x - dX;
                }
                // Karakter
                else {
                    GLuint ascii = (unsigned char)text[i];

                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffers[ascii]);
                    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, NULL);

                    glTranslatef(mClips[ascii].Width, 0.f, 0.f);
                    dX += mClips[ascii].Width;
                }
            }

            // GL cizim bufferlarini ve dokuyu sifirlayalim
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);

            // Vertex ve doku kordinat dizilerini pasif hale getirelim
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            glDisableClientState(GL_VERTEX_ARRAY);

            // Onceki durumu geri alalim
            glMatrixMode(GL_MODELVIEW);
            glPopMatrix();
        }
    }
}