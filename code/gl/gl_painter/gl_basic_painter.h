/**
 * @file   gl_basic_painter.h
 * @date   4/25/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_GL_BASIC_PAINTER_H
#define INC_GL_BASIC_PAINTER_H

#include <cstdint>

#include <memory>
#include <unordered_map>

#include "graphics/color.h"
#include "graphics/rectangle.h"
#include "graphics/polygon.h"

#include "asset/asset.h"

#include "glm/glm.hpp"

#include "brush.h"
#include "pen.h"
#include "alias_mode.h"

class Line;
class Point;

using Vector2f = glm::tvec2<float>;

namespace gl {
    class SimpleGeometry;
    class TextureAsset;
    class GLFont;

    class GLBasicPainter {
    public:
        /** @brief   GL Painter ilklendirmeleri icin kullanilacak API */
        virtual void InitializePainter();

        /** @brief   OpenGL cizimi baslangic/son kisimlari
                     Bir takim state ayarlamalari burada yapiliyor*/
        void Begin();
        void End();

        /** @brief   Temel OpenGL ayarlamalarina iliskin API */
        void SetDepthTest(bool enableStatus);
        void SetBackgroundColor(const Color& color);
        void AssignPen(const Pen& pen);
        void AssignBrush(const Brush& brush);
        
        /** @brief   Ortografik projeksiyon ayarlari */
        void SetDisplayExtent(double left, double right, double bottom, double top);
        void SetOrtho(double left, double right, double bottom, double top, double zNear, double zFar);
        
        /** @brief   OpenGL Painter transformasyon API'si */
        void Rotate(float rotation);
        void Translate(float tx, float ty);
        void Translate(double tx, double ty);
        void Translate(const glm::vec2& translation);
        void Scale(float sx, float sy);
        void ResetTransform();
        void SaveState();
        void RestoreState();

        /** @brief   Temel geometri cizim API'leri */
        void DrawLine(const Line& line);
        void DrawPoint(const Point& point);
        void DrawPoint(const glm::vec2& point);
        void DrawRectangle(const infra::Rectangle<float>& rect);
        void DrawPolyline(infra::Polygon& polygon, bool isLoop = false);
        void DrawPolylineRaw(double* polyline, uint32_t pointCount, bool isLoop = false);
        void DrawPolygon(infra::Polygon& polygon);
        void DrawConcavePolygon(infra::Polygon& polygon);
        void DrawEllipse(const Point& center, float rx, float ry);
        
        /** @brief   Stencil API'leri */
        void BeginClippingArea();
        void EndClippingArea();
        void ResetClippingArea();

        /** @brief   Font API'leri */
        bool SetActiveFont(std::string_view fontLabel);
        bool RegisterFont(std::string_view fontLabel, std::string_view fontPath, uint32_t size = 12);

        /** @brief Basit metin cizmi API'si */
        void SimpleText(const glm::vec2& point, std::string_view text);

        /** @brief   Doku cizim API'leri */
        void DrawTexture(const gl::TextureAsset* texture, const Vector2f& centerPos, float width, float height);
        void DrawTexture(const gl::TextureAsset* texture, const Vector2f& centerPos, float width, float height, float* textureCoordinates);
        
        /** @brief   Parlaklik API'si*/
        void SetBrightness(float brightness);

        /** @brief   CBS benzeri jenerik geometri cizimleri icin kullanilacak API */
        virtual void DrawGeometry(const SimpleGeometry& geometry);

        /** @brief   Son atanan stencil degeri */
        uint32_t mCurrentStencilValue{ 1 };
    protected:
        /** @brief   Renk atama API'si*/
        void SetColor(const Color& color);

        /** @brief   Cember geometri ilklendirme */
        void InitializeCircleGeometry();
        void SetPenParameters(bool isStroke) const;

        /** @brief Temel font bilgileri */
        std::string mActiveFontLabel{ "Default" };
        std::shared_ptr<GLFont> mActiveFontInstance{ nullptr };
        std::unordered_map<std::string, std::shared_ptr<GLFont>> mFonts;

        /** @brief   En son aktif olan doku tanimlayicisi */
        uint32_t mLastBindedTextureId;

        /** @brief   Painter ilklendirme durumu */
        bool mIsInitialized;

        /** @brief   Onceden hesaplanan cember geometrisi */
        infra::Polygon mCircleGeometry;

        /** @brief   Aktif kalem */
        Pen mActivePen;

        /** @brief   Aktif firca */
        Brush mActiveBrush;

        /** @brief   Arka plan rengi */
        Color mBackgroundColor;

        /** @brief   Son atanan parlaklik ekran faktoru [0.0 to 2.0] */
        float mBrightness;

        /** @brief   Surucuye gore cizgi genislik sinirlarini kontrol edelim[ 2] */
        float mLineWidthRange[2];
    };
}

#endif    // INC_GL_BASIC_PAINTER_H

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


