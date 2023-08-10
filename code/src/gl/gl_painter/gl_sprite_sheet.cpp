#include "gl_sprite_sheet.h"

#include "spdlog/spdlog.h"

namespace gl {
    GLSpriteSheet::GLSpriteSheet() {
        mVertexDataBuffer = NULL;
    }

    GLSpriteSheet::~GLSpriteSheet()  {
        FreeSheet();
    }

    size_t GLSpriteSheet::AddClipSprite(infra::Rectangle<float>& newClip)  {
        mClips.push_back(newClip);
        return mClips.size() - 1;
    }

    infra::Rectangle<float> GLSpriteSheet::Clip(int32_t index)  const {
        return mClips[index];
    }

    bool GLSpriteSheet::GenerateDataBuffer(SpriteOrigin origin)  {
        if (TextureID() != 0 && mClips.size() > 0) {
            size_t totalSprites = mClips.size();
            VertexData2D* vertexData = new VertexData2D[totalSprites * 4];
            mIndexBuffers.resize(totalSprites);

            glGenBuffers(1, &mVertexDataBuffer);
            glGenBuffers(static_cast<GLsizei>(totalSprites), &mIndexBuffers[0]);

            GLfloat tW = static_cast<float>(TextureWidth());
            GLfloat tH = static_cast<float>(TextureHeight());
            GLuint spriteIndices[4] = { 0, 0, 0, 0 };

            GLfloat vTop = 0.f;
            GLfloat vBottom = 0.f;
            GLfloat vLeft = 0.f;
            GLfloat vRight = 0.f;

            for (size_t i = 0; i < totalSprites; ++i)  {
                spriteIndices[0] = static_cast<uint32_t>(i * 4 + 0);
                spriteIndices[1] = static_cast<uint32_t>(i * 4 + 1);
                spriteIndices[2] = static_cast<uint32_t>(i * 4 + 2);
                spriteIndices[3] = static_cast<uint32_t>(i * 4 + 3);

                switch (origin)         {
                case SpriteOrigin::TopLeft:
                    vTop = 0.f;
                    vBottom = mClips[i].Height;
                    vLeft = 0.f;
                    vRight = mClips[i].Width;
                    break;

                case SpriteOrigin::TopRight:
                    vTop = 0.f;
                    vBottom = mClips[i].Height;
                    vLeft = -mClips[i].Width;
                    vRight = 0.f;
                    break;

                case SpriteOrigin::BottomLeft:
                    vTop = -mClips[i].Height;
                    vBottom = 0.f;
                    vLeft = 0.f;
                    vRight = mClips[i].Width;
                    break;

                case SpriteOrigin::BottomRight:
                    vTop = -mClips[i].Height;
                    vBottom = 0.f;
                    vLeft = -mClips[i].Width;
                    vRight = 0.f;
                    break;

                    // Merkez
                default:
                    vTop = -mClips[i].Height / 2.f;
                    vBottom = mClips[i].Height / 2.f;
                    vLeft = -mClips[i].Width / 2.f;
                    vRight = mClips[i].Width / 2.f;
                    break;
                }

                // Sol Ust
                vertexData[spriteIndices[0]].Position.x = vLeft;
                vertexData[spriteIndices[0]].Position.y = vTop;

                vertexData[spriteIndices[0]].TexCoord.s = (mClips[i].Left) / tW;
                vertexData[spriteIndices[0]].TexCoord.t = (mClips[i].Top) / tH;

                // Sag Ust
                vertexData[spriteIndices[1]].Position.x = vRight;
                vertexData[spriteIndices[1]].Position.y = vTop;

                vertexData[spriteIndices[1]].TexCoord.s = (mClips[i].Left + mClips[i].Width) / tW;
                vertexData[spriteIndices[1]].TexCoord.t = (mClips[i].Top) / tH;

                // Sag Alt
                vertexData[spriteIndices[2]].Position.x = vRight;
                vertexData[spriteIndices[2]].Position.y = vBottom;

                vertexData[spriteIndices[2]].TexCoord.s = (mClips[i].Left + mClips[i].Width) / tW;
                vertexData[spriteIndices[2]].TexCoord.t = (mClips[i].Top + mClips[i].Height) / tH;

                // Sol Alt
                vertexData[spriteIndices[3]].Position.x = vLeft;
                vertexData[spriteIndices[3]].Position.y = vBottom;

                vertexData[spriteIndices[3]].TexCoord.s = (mClips[i].Left) / tW;
                vertexData[spriteIndices[3]].TexCoord.t = (mClips[i].Top + mClips[i].Height) / tH;

                // Index buffer verisini baglayalim
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffers[i]);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), spriteIndices, GL_STATIC_DRAW);
            }

            // Vertex buffer verisini baglayalim
            glBindBuffer(GL_ARRAY_BUFFER, mVertexDataBuffer);
            glBufferData(GL_ARRAY_BUFFER, totalSprites * 4 * sizeof(VertexData2D), vertexData, GL_STATIC_DRAW);

            delete[] vertexData;
        }
        else   {
            if (TextureID() == 0)  {
                spdlog::error("No texture to render with!\n");
            }

            if (mClips.size() <= 0)  {
                spdlog::error("No clips to generate vertex data from!\n");
            }

            return false;
        }

        return true;
    }

    void GLSpriteSheet::FreeSheet()  {
        if (mVertexDataBuffer != NULL)  {
            glDeleteBuffers(1, &mVertexDataBuffer);
            mVertexDataBuffer = NULL;
        }

        if (mIndexBuffers.size() != 0)  {
            glDeleteBuffers(static_cast<GLsizei>(mClips.size()), &mIndexBuffers[0]);
            mIndexBuffers.clear();
        }

        mClips.clear();
    }

    void GLSpriteSheet::FreeTexture()  {
        FreeSheet();
        GLTexture::FreeTexture();
    }

    void GLSpriteSheet::RenderSprite(int32_t index) {
        if (mVertexDataBuffer != NULL)  {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, TextureID());

            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);

            glBindBuffer(GL_ARRAY_BUFFER, mVertexDataBuffer);
            glTexCoordPointer(2, GL_FLOAT, sizeof(VertexData2D), (GLvoid*)offsetof(VertexData2D, TexCoord));

            glVertexPointer(2, GL_FLOAT, sizeof(VertexData2D), (GLvoid*)offsetof(VertexData2D, Position));

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffers[index]);
            glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, NULL);

            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            glDisableClientState(GL_VERTEX_ARRAY); 
            
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);
        }
    }
}