#include "gl_basic_painter.h"

#include "spdlog/spdlog.h"

#include "graphics/line.h"
#include "graphics/point.h"
#include "graphics/polygon_triangulator.h"

#include "gl_include.h"
#include "simple_geometry.h"
#include "pen_stippling_data.h"
#include "brush_stippling_data.h"

#include "gl_font.h"
#include "gl_texture/texture_asset.h"

const uint32_t cNumberOfSegmentInCircle = 36U;

namespace gl {
	//! Opak imaj gosterimi icin kullanilacak renk
	Color g_whiteColor(Color::White);

	//! Varsayilan firca
	Brush g_painterDefaultBrush(Color::White);
	
	void GLBasicPainter::SetColor(const Color& color) {
		glColor4f(color.GetRedF(), color.GetGreenF(), color.GetBlueF(), color.GetAlphaF());
	}

	void GLBasicPainter::InitializePainter() {
		this->InitializeCircleGeometry();

		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Antialiasing/multisampling
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
		glDisable(GL_LINE_SMOOTH);
		glDisable(GL_POLYGON_SMOOTH);
		glDisable(GL_MULTISAMPLE);

		// Stippling oruntulerini aktiflestirelim (line/fill styles)
		glEnable(GL_LINE_STIPPLE);
		glEnable(GL_POLYGON_STIPPLE);


		//! Varsayilan isik ayarlari
		GLfloat aLightpos[] = { 1.0F, 1.0F, 1.0F, 0.0F };
		GLfloat aAmbientColor[] = { 0.3F, 0.3F, 0.3F, 1.0F };
		GLfloat aDifuseColor[] = { 0.2F, 0.2F, 0.2F, 1.0F };
		glLightfv(GL_LIGHT0, GL_POSITION, aLightpos);
		glLightfv(GL_LIGHT0, GL_AMBIENT, aAmbientColor);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, aDifuseColor);

		// Cizgi ve poliogon duzeltme ayarlari
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

		mAliasMode = AliasMode::MultiSample;

		mIsInitialized = true;
	}

	void GLBasicPainter::SetAliasingMode(AliasMode mode) {
		mAliasMode = mode;
	}

	void GLBasicPainter::Begin() {
		// Tamponlari temizleyelim
		glClear(GL_COLOR_BUFFER_BIT |
			GL_DEPTH_BUFFER_BIT |
			GL_STENCIL_BUFFER_BIT);

		// Verilen deger ile stencil tamponunu temizleyelim
		glClearStencil(0x0);

		glEnableClientState(GL_VERTEX_ARRAY);

		switch (mAliasMode)
		{
		case AliasMode::Aliased:
			glDisable(GL_LINE_SMOOTH);
			glDisable(GL_POLYGON_SMOOTH);
			glDisable(GL_MULTISAMPLE);
			break;

		case AliasMode::AntiAliased:
			glEnable(GL_LINE_SMOOTH);
			glEnable(GL_POLYGON_SMOOTH);
			glDisable(GL_MULTISAMPLE);
			break;

		case AliasMode::MultiSample:
			glDisable(GL_LINE_SMOOTH);
			glDisable(GL_POLYGON_SMOOTH);
			glEnable(GL_MULTISAMPLE);
			break;
		}

		// Blending fonksiyon ayarlamasi
		// e.g. red = sR * sA + dR * (1 - sA) where source is newly drawn and dest. is already drawn
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glClearColor(mBackgroundColor.GetRedF(),
			mBackgroundColor.GetGreenF(),
			mBackgroundColor.GetBlueF(),
			mBackgroundColor.GetAlphaF());

		this->SetBrush(g_painterDefaultBrush);
	}

	void GLBasicPainter::End() {
		glDisableClientState(GL_VERTEX_ARRAY);
		glFlush();
	}

	void GLBasicPainter::BeginClippingArea() {
		glEnable(GL_STENCIL_TEST);
		glStencilFunc(GL_NOTEQUAL, mCurrentStencilValue, 0xFF);
		glStencilMask(0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	}

	void GLBasicPainter::EndClippingArea()
	{
		glStencilFunc(GL_EQUAL, mCurrentStencilValue, 0xFF);
		mCurrentStencilValue = mCurrentStencilValue << 1;
	}

	void GLBasicPainter::ResetClippingArea() {
		glDisable(GL_STENCIL_TEST);
	}

    bool GLBasicPainter::SetActiveFont(std::string_view fontLabel) {
        std::string label{ static_cast<std::string>(fontLabel) };
        bool isFontFound{ false };
        if (mFonts.contains(label)) {
            mActiveFontLabel = label;
            mActiveFontInstance = mFonts[label];
            isFontFound = true;
        }

        return isFontFound;
    }

    bool GLBasicPainter::RegisterFont(std::string_view fontLabel, std::string_view fontPath, uint32_t size) {
        bool result = false;

        std::shared_ptr<GLFont> fontToRegister = std::make_shared<GLFont>();
        if (fontToRegister->LoadFreeType(static_cast<std::string>(fontPath), size)) {
            std::string label{ static_cast<std::string>(fontLabel) };
            mFonts.emplace(label, fontToRegister);
            result = true;
            spdlog::info("SDL Font {} registration succeed!");
        }
        else {
            spdlog::error("SDL Font register failed!");
        }

        return result;
    }

    void GLBasicPainter::SimpleText(const glm::vec2& point, std::string_view text) {
        if (nullptr != mActiveFontInstance) {
            SetColor(mActivePen.GetColor());
            mActiveFontInstance->RenderText(point.x, point.y, text);
        }
    }

	void GLBasicPainter::SetBackgroundColor(const Color& color) {
		mBackgroundColor = color;
	}

	void GLBasicPainter::SetDepthTest(bool enableStatus) {
		if (true == enableStatus) {
			glEnable(GL_DEPTH_TEST);
		}
		else {
			glDisable(GL_DEPTH_TEST);
		}
	}

	void GLBasicPainter::SetDisplayExtent(double left, double right, double bottom, double top)	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(left, right, bottom, top, 1.0, -1.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void GLBasicPainter::SetOrtho(double left, double right, double bottom, double top, double zNear, double zFar)	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(left, right, bottom, top, zNear, zFar);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void GLBasicPainter::Rotate(float rotation)	{
		glMatrixMode(GL_MODELVIEW);
		glRotatef(rotation, 0.0, 0.0, 1.0);
	}

	void GLBasicPainter::Translate(float tx, float ty)	{
		glMatrixMode(GL_MODELVIEW);
		glTranslatef(tx, ty, 0);
	}

	void GLBasicPainter::Translate(const glm::vec2& translation)	{
		glMatrixMode(GL_MODELVIEW);
		glTranslatef(translation.x, translation.y, 0);
	}

	void GLBasicPainter::Scale(float sx, float sy)	{
		glMatrixMode(GL_MODELVIEW);
		glScalef(sx, sy, 0.0);
	}

	void GLBasicPainter::ResetTransform()	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void GLBasicPainter::SaveState()	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
	}

	void GLBasicPainter::RestoreState()	{
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}

	void GLBasicPainter::DrawLine(const Line& line)	{
		if (false == mActivePen.HasStroke()) {
			SetColor(mActivePen.GetColor());

			glBegin(GL_LINES);
			glVertex2f(line.GetX1(), line.GetY1());
			glVertex2f(line.GetX2(), line.GetY2());
			glEnd();
		}
		else {
			this->SetPenParameters(true);
			this->SetColor(mActivePen.GetColor(true));

			glBegin(GL_LINES);
			glVertex2f(line.GetX1(), line.GetY1());
			glVertex2f(line.GetX2(), line.GetY2());
			glEnd();

			this->SetPenParameters(false);
			this->SetColor(mActivePen.GetColor(false));

			glBegin(GL_LINES);
			glVertex2f(line.GetX1(), line.GetY1());
			glVertex2f(line.GetX2(), line.GetY2());
			glEnd();
		}
	}

	void GLBasicPainter::DrawPoint(const Point& point)	{
		SetColor(mActivePen.GetColor());

		glBegin(GL_POINTS);
		glVertex2f(point.GetX(), point.GetY());
		glEnd();
	}

	void GLBasicPainter::DrawPoint(const glm::vec2& point)	{
		SetColor(mActivePen.GetColor());

		glBegin(GL_POINTS);
		glVertex2f(point.x, point.y);
		glEnd();
	}

	void GLBasicPainter::DrawRect(const infra::Rectangle<float>& rect) {
		float left = rect.GetLeft();
		float right = rect.GetRight();
		float top = rect.GetTop();
		float bottom = rect.GetBottom();

		float coordinateArray[8] = {
			left, bottom,
			left, top,
			right, top,
			right, bottom
		};

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, coordinateArray);

		SetColor(mActiveBrush.GetColor());

        glDrawArrays(GL_QUADS, 0, 4);

		SetColor(mActivePen.GetColor());
		glDrawArrays(GL_LINE_LOOP, 0, 4);

		glDisableClientState(GL_VERTEX_ARRAY);
	}

	void GLBasicPainter::DrawPolyline(infra::Polygon& polygon, bool isLoop) {
		if (false == mActivePen.HasStroke()) {
			SetColor(mActivePen.GetColor());
			glVertexPointer(2, GL_FLOAT, sizeof(glm::vec2), polygon.GetPointPtr());

			if (true == isLoop)	{
				glDrawArrays(GL_LINE_LOOP, 0, polygon.GetPointCount());
			}
			else {
				glDrawArrays(GL_LINE_STRIP, 0, polygon.GetPointCount());
			}
		}
		else {
			this->SetPenParameters(true);
			this->SetColor(mActivePen.GetColor(true));

			glVertexPointer(2, GL_FLOAT, sizeof(glm::vec2), polygon.GetPointPtr());
			glDrawArrays(GL_LINE_STRIP, 0, polygon.GetPointCount());

			this->SetPenParameters(false);
			this->SetColor(mActivePen.GetColor(false));

			glVertexPointer(2, GL_FLOAT, sizeof(glm::vec2), polygon.GetPointPtr());
			glDrawArrays(GL_LINE_STRIP, 0, polygon.GetPointCount());
		}
	}

	void GLBasicPainter::DrawPolygon(infra::Polygon& polygon) {
		glEnableClientState(GL_VERTEX_ARRAY);
		SetColor(mActiveBrush.GetColor());
		glVertexPointer(2, GL_FLOAT, sizeof(glm::vec2), polygon.GetPointPtr());
		glDrawArrays(GL_POLYGON, 0, polygon.GetPointCount());

		if (PenStyle::NoPen != mActivePen.GetPenStyle()) {
			DrawPolyline(polygon, true);
		}
	}

	void GLBasicPainter::DrawConcavePolygon(infra::Polygon& polygon)
	{
		std::vector<glm::vec2> results;
        infra::Polygon triangulatePolygon;

		if (false == PolygonTriangulator::Triangulate(polygon.GetPoints(), results)) {
			triangulatePolygon.SetPoints(results);

			glEnableClientState(GL_VERTEX_ARRAY);
			SetColor(mActiveBrush.GetColor());
			glVertexPointer(2, GL_FLOAT, sizeof(glm::vec2), triangulatePolygon.GetPointPtr());
			glDrawArrays(GL_TRIANGLES, 0, triangulatePolygon.GetPointCount());

			if (PenStyle::NoPen != mActivePen.GetPenStyle()) {
				DrawPolyline(polygon, true);
			}
		}
		else {
			this->DrawPolygon(polygon);
		}
	}


	void GLBasicPainter::DrawEllipse(const Point& center, float rx, float ry) {
		SaveState();

		SetColor(mActivePen.GetColor());
		Translate(center.GetX(), center.GetY());
		Scale(rx, ry);

		glEnableClientState(GL_VERTEX_ARRAY);

		glVertexPointer(2, GL_FLOAT, sizeof(glm::vec2), mCircleGeometry.GetPointPtr());
		glDrawArrays(GL_LINE_LOOP, 1, cNumberOfSegmentInCircle + 1);

		SetColor(mActiveBrush.GetColor());
		glDrawArrays(GL_POLYGON, 0, cNumberOfSegmentInCircle + 2);

		glDisableClientState(GL_VERTEX_ARRAY);

		RestoreState();
	}

	void GLBasicPainter::DrawTexture(const gl::TextureAsset* texture, const Vector2f& centerPos, float width, float height,
		float* textureCoordinates,
		const Color& color)	{
		float Left = centerPos.x - width * 0.5F;
		float Right = Left + width;
		float Top = centerPos.y - height * 0.5F;
		float Bottom = Top + height;

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture->GetOpenGLTextureId());

		SetColor(color);

		float coordinateArray[8] = {
			Left, Top,
			Left, Bottom,
			Right, Bottom,
			Right, Top
		};

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(2, GL_FLOAT, 0, coordinateArray);
		glTexCoordPointer(2, GL_FLOAT, 0, textureCoordinates);

		SetColor(mActiveBrush.GetColor());

		glDrawArrays(GL_QUADS, 0, 4);

		glDisableClientState(GL_VERTEX_ARRAY);

		glDisable(GL_TEXTURE_2D);
	}

	const float cTextureCoordinates[8] = {
		// Ust Sol
		0.0F, 0.0F,

		// Alt sol
		0.0F, 1.0F,

		// Alt sag
		1.0F, 1.0F,

		// Ust Sag
		1.0F, 0.0F,
	};

	void GLBasicPainter::DrawTexture(const gl::TextureAsset* texture, const Vector2f& centerPos, float width, float height,
		const Color& color) {
        float Left = centerPos.x - width * 0.5F;
        float Right = Left + width;
        float Top = centerPos.y - height * 0.5F;
        float Bottom = Top + height;

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture->GetOpenGLTextureId());

		SetColor(color);

		float coordinateArray[8] =
		{
			Left, Top,
			Left, Bottom,
			Right, Bottom,
			Right, Top
		};

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(2, GL_FLOAT, 0, coordinateArray);
		glTexCoordPointer(2, GL_FLOAT, 0, cTextureCoordinates);

		glDrawArrays(GL_QUADS, 0, 4);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

        glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);
	}

	void GLBasicPainter::DrawGeometry(const SimpleGeometry& geometry) {
		uint32_t pointCount = geometry.GetPointCount();

		if (pointCount > 0) {
			switch (geometry.GetGeometryType()) 	{
			case GeometryType::eGT_POINT:
			case GeometryType::eGT_POINT2D: {
				auto pnt = geometry.GetPoint2D();

				if (pnt.has_value()) {
					this->DrawPoint(pnt.value());
				}
			}
			break;

			case GeometryType::eGT_LINESTRING:
			case GeometryType::eGT_LINESTRING25D: {
				this->SetPenParameters(true);
				this->SetColor(mActivePen.GetColor(true));
				glVertexPointer(3, GL_FLOAT, sizeof(glm::vec3), geometry.GetPointPtr());
				glDrawArrays(GL_LINE_STRIP, 0, geometry.GetPointCount());

				this->SetPenParameters(false);
				this->SetColor(mActivePen.GetColor(false));
				glVertexPointer(3, GL_FLOAT, sizeof(glm::vec3), geometry.GetPointPtr());
				glDrawArrays(GL_LINE_STRIP, 0, geometry.GetPointCount());
			}
			break;

			case GeometryType::eGT_POLYGON:
			case GeometryType::eGT_POLYGON25D: {
				glEnableClientState(GL_VERTEX_ARRAY);
				SetColor(mActiveBrush.GetColor());
				glVertexPointer(3, GL_FLOAT, sizeof(glm::vec3), geometry.GetPointPtr());
				glDrawArrays(GL_POLYGON, 0, geometry.GetPointCount());

				if (PenStyle::NoPen != mActivePen.GetPenStyle()) {
					this->SetPenParameters(true);
					this->SetColor(mActivePen.GetColor(true));
					glVertexPointer(3, GL_FLOAT, sizeof(glm::vec3), geometry.GetPointPtr());
					glDrawArrays(GL_LINE_STRIP, 0, geometry.GetPointCount());

					this->SetPenParameters(false);
					this->SetColor(mActivePen.GetColor(false));
					glVertexPointer(3, GL_FLOAT, sizeof(glm::vec3), geometry.GetPointPtr());
					glDrawArrays(GL_LINE_STRIP, 0, geometry.GetPointCount());
				}
			}
			break;
			}
		}
	}

	void GLBasicPainter::InitializeCircleGeometry()	{
		constexpr float angleDelta = glm::radians(360.0F) / cNumberOfSegmentInCircle;
		float angle = 0.0F;

		glm::vec2 p1;

		for (uint32_t i = 0U; i <= cNumberOfSegmentInCircle; ++i) {
			p1.x = cos(angle);
			p1.y = sin(angle);

			angle = angle + angleDelta;
			mCircleGeometry.Append(p1);
		}

		p1.x = cos(0.0F);
		p1.y = sin(0.0F);
		mCircleGeometry.Append(p1);
	}

	void GLBasicPainter::SetPenParameters(bool isStroke) const	{
		glLineWidth(mActivePen.GetWidth(isStroke));
		glPointSize(mActivePen.GetWidth(isStroke));

		switch (mActivePen.GetPenStyle(isStroke)) {
		case gl::PenStyle::NoPen:
			glLineStipple(mActivePen.GetStyleFactor(), cNoPenStipple);
			break;
		case gl::PenStyle::SolidLine:
			glLineStipple(mActivePen.GetStyleFactor(), cSolidLineStipple);
			break;
		case gl::PenStyle::DashLine:
			glLineStipple(mActivePen.GetStyleFactor(), cDashLineStipple);
			break;
		case gl::PenStyle::DotLine:
			glLineStipple(mActivePen.GetStyleFactor(), cDotLineStipple);
			break;
		case gl::PenStyle::DoubleDotLine:
			glLineStipple(mActivePen.GetStyleFactor(), cDoubleDotLine);
			break;
		case gl::PenStyle::DashDotLine:
			glLineStipple(mActivePen.GetStyleFactor(), cDashDotLineStipple);
			break;
		case gl::PenStyle::ShortDashLongDashLine:
			glLineStipple(mActivePen.GetStyleFactor(), cShortDashLongDashStipple);
			break;
		default:
			glLineStipple(1, cDefaultLineStipple);
			break;
		}
	}

	void GLBasicPainter::SetPen(const Pen& pen)	{
		if (mActivePen != pen)	{
			mActivePen = pen;
			this->SetPenParameters(false);
		}
	}

	void GLBasicPainter::SetBrightness(float brightness) {
		mBrightness = brightness;
	}

	void GLBasicPainter::SetBrush(const Brush& brush) {
		if (mActiveBrush != brush) {
			mActiveBrush = brush;

			BrushStyle brushStyle = brush.GetStyle();

			switch (brushStyle) {
			case gl::BrushStyle::NoBrush:
				glPolygonStipple(&cNoPattern[0]);
				break;
			case gl::BrushStyle::SolidPattern:
				glPolygonStipple(&cSolidPattern[0]);
				break;
			case gl::BrushStyle::HalfTonePattern:
				glPolygonStipple(&cHalfTonePattern[0]);
				break;
			case gl::BrushStyle::DotPattern:
				glPolygonStipple(&cDotPattern[0]);
				break;
			case gl::BrushStyle::LinePattern:
				glPolygonStipple(&cLinePattern[0]);
				break;
			case gl::BrushStyle::DensePattern:
				glPolygonStipple(&cDensePattern[0]);
				break;
			case gl::BrushStyle::DashPattern:
				glPolygonStipple(&cDashPattern[0]);
				break;
			case gl::BrushStyle::CheckPattern:
				glPolygonStipple(&cCheckPattern[0]);
				break;
			case gl::BrushStyle::CrossPattern:
				glPolygonStipple(&cCrossPattern[0]);
				break;
			case gl::BrushStyle::HorizontalPattern:
				glPolygonStipple(&cHorizontalPattern[0]);
				break;
			case gl::BrushStyle::VerticalPattern:
				glPolygonStipple(&cVerticalPattern[0]);
				break;
			case gl::BrushStyle::BackwardDiagonalPattern:
				glPolygonStipple(&cBackwardDiagonalPattern[0]);
				break;
			case gl::BrushStyle::ForwardDiagonalPattern:
				glPolygonStipple(&cForwardDiagonalPattern[0]);
				break;
			case gl::BrushStyle::DiagonalCrossPattern:
				glPolygonStipple(&cDiagonalCrossPattern[0]);
				break;
			default:
				break;
			}
		}
	}
}