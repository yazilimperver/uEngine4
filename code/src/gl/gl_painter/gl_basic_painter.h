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

#include "graphics/color.h"
#include "graphics/rectangle.h"
#include "graphics/polygon.h"

#include "brush.h"
#include "pen.h"
#include "alias_mode.h"

class Line;
class Point;

namespace gl {
	class SimpleGeometry;
	class uTextureAsset;
	class uIFontService;

	//! Either uses shader based rendering or traditional opengl calls based on derived classes
    class GLBasicPainter {
	public:
		//! Initialize opengl rendering
		void InitializePainter();

		//! The start/end of opengl rendering
		//! Some common settings happens here
		void Begin();
		void End();

		//! Basic settings
		void SetAliasingMode(AliasMode mode);
		void SetDepthTest(bool enableStatus);
		void SetBackgroundColor(const Color& color);
		void AssignPen(const Pen& pen);
        Pen ActivePen() const;
		void AssignBrush(const Brush& brush);
        Brush ActiveBrush() const;
		
		//! Orthographic projection setting
		void SetDisplayExtent(double left, double right, double bottom, double top);
		void SetOrtho(double left, double right, double bottom, double top, double zNear, double zFar);

		//! Transformation matrix API
		void Rotate(float rotation);
		void Translate(float tx, float ty);
		void Translate(const glm::vec2& translation);
		void Scale(float sx, float sy);
		void ResetTransform();
		void SaveState();
		void RestoreState();

		//! Primitive rendering API with specific geometry classes
		void DrawLine(const Line& line);
		void DrawPoint(const Point& point);
		void DrawPoint(const glm::vec2& point);
		void DrawRect(const infra::Rectangle<float>& rect);
		void DrawPolyline(Polygon& polygon, bool isLoop = false);
		void DrawPolygon(Polygon& polygon);
		void DrawConcavePolygon(Polygon& polygon);
		void DrawEllipse(const Point& center, float rx, float ry);
		
		//! Stenciling
		void BeginClippingArea();
		void EndClippingArea();
		void ResetClippingArea();

		//! Brightness
		void SetBrightness(float brightness);

		//! With generic geometry class for GIS like applications.
		void DrawGeometry(const SimpleGeometry& geometry);
	protected:
		//! Set current color
		void SetColor(const Color& color);

		//! Circle geometry preparation
		void InitializeCircleGeometry();
		void SetPenParameters(bool isStroke) const;

		//! Last binding texture id
		uint32_t mLastBindedTextureId;

		//! Current aliasing mode
		gl::AliasMode mAliasMode;

		//! Is painter initialized and ready to paint
		bool mIsInitialized;

		//! Pre-calculated circle
		Polygon mCircleGeometry;

		//! Active GL and GLStroke Pen
		Pen mActivePen;

		//! Active GL Brush
		Brush mActiveBrush;

		//! Background color
		Color mBackgroundColor;

		//! Font service
		uIFontService* mFontService;

		//! Brightness factor of the screen ranges [0.0 to 2.0]
		float mBrightness;

		//! Last set stencil value
		uint32_t mCurrentStencilValue;
    };
}

#endif	// INC_GL_BASIC_PAINTER_H

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


