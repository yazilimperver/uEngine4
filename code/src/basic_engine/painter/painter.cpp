#include "painter.h"

#include <filesystem>

#include "spdlog/spdlog.h"

#include "utility/file_operations.h"

#include "gfx_primitives.h"

// Kullanilan bir takimGFX Private API'leri
extern int _gfxPrimitivesCompareInt(const void* a, const void* b);
extern int hline(SDL_Renderer* renderer, Sint16 x1, Sint16 x2, Sint16 y);

namespace basic_engine {
	void Painter::AssignRenderer(SDL_Renderer* renderer) {
		mRenderer = renderer;
	}

	void Painter::AssignPen(const Pen& pen) {
		mActivePen = pen;
	}

	Pen Painter::ActivePen() const {
		return mActivePen;
	}

	void Painter::AssignBrush(const Brush& brush) {
		mActiveBrush = brush;
	}

	Brush Painter::ActiveBrush() const {
		return mActiveBrush;
	}

	void Painter::DrawPolygon(const Point2d* polygon, uint32_t vertexCount) const {
		if (nullptr != mRenderer) {
			auto penColor = mActivePen.PenColor();
			auto brushColor = mActiveBrush.BrushColor();

			// poligonun icini cizdirelim
			_DrawPolygon(mRenderer, polygon, vertexCount, brushColor.R, brushColor.G, brushColor.B, brushColor.A);

			// Dikdortgen cercevesi var mi?
			if (mActivePen.Width() > 0) {
				_DrawPolyline(mRenderer, polygon, vertexCount, penColor.R, penColor.G, penColor.B, penColor.A);
			}
		}
		else {
			spdlog::error("SDL Renderer not assigned!");
		}
	}

	void Painter::DrawPolyline(const Point2d* polygon, uint32_t vertexCount) const	{
		if (nullptr != mRenderer) {
			auto penColor = mActivePen.PenColor();

			// Dikdortgen cercevesi var mi?
			if (mActivePen.Width() > 0) {
				_DrawPolyline(mRenderer, polygon, vertexCount, penColor.R, penColor.G, penColor.B, penColor.A);
			}
		}
		else {
			spdlog::error("SDL Renderer not assigned!");
		}
	}

	void Painter::DrawLine(const Point2d& start, const Point2d& end) const {
		if (nullptr != mRenderer) {
			auto penColor = mActivePen.PenColor();
			auto strokeColor = mActivePen.StrokeColor();

			// Kalem genisligine gore kullanacagimiz API degisecek
			if (1 == mActivePen.Width()) {
				// En basit ve hizli cizgimizi cizelim
				if (mActivePen.StrokeWidth() < 2) {
					lineRGBA(mRenderer, start.x, start.y, end.x, end.y, penColor.R, penColor.G, penColor.B, penColor.A);
				}
				else {
					// Once stroke'u cizelim
					thickLineRGBA(mRenderer, start.x, start.y, end.x, end.y, mActivePen.StrokeWidth(), strokeColor.R, strokeColor.G, strokeColor.B, strokeColor.A);

					// Asil cizgiyi cizelim
					lineRGBA(mRenderer, start.x, start.y, end.x, end.y, penColor.R, penColor.G, penColor.B, penColor.A);
				}
			}
			else {
				if (mActivePen.StrokeWidth() < 2) {
					thickLineRGBA(mRenderer, start.x, start.y, end.x, end.y, mActivePen.Width(), penColor.R, penColor.G, penColor.B, penColor.A);
				}
				else {
					// Once stroke'u cizelim
					thickLineRGBA(mRenderer, start.x, start.y, end.x, end.y, mActivePen.StrokeWidth(), strokeColor.R, strokeColor.G, strokeColor.B, strokeColor.A);

					// Asil cizgiyi cizelim
					thickLineRGBA(mRenderer, start.x, start.y, end.x, end.y, mActivePen.Width(), penColor.R, penColor.G, penColor.B, penColor.A);
				}
			}
		}
		else {
			spdlog::error("SDL Renderer not assigned!");
		}
	}

	void Painter::DrawPoint(const Point2d& point) const {
		if (nullptr != mRenderer) {
			auto penColor = mActivePen.PenColor();
			pixelRGBA(mRenderer, point.x, point.y, penColor.R, penColor.G, penColor.B, penColor.A);
		}
		else {
			spdlog::error("SDL Renderer not assigned!");
		}
	}

	void Painter::DrawRectangle(const SDL_Rect& rect) const	{
		if (nullptr != mRenderer) {
			auto penColor = mActivePen.PenColor();
			auto brushColor = mActiveBrush.BrushColor();

			// Dikdortgenin icini cizdirelim
			boxRGBA(mRenderer, rect.x + rect.w, rect.y, rect.x, rect.y + rect.h, brushColor.R, brushColor.G, brushColor.B, brushColor.A);

			// Dikdortgen cercevesi var mi?
			if (mActivePen.Width() > 0) {
				DrawLine(Point2d{ rect.x, rect.y }, Point2d{ rect.x + rect.w, rect.y });
				DrawLine(Point2d{ rect.x + rect.w, rect.y }, Point2d{ rect.x + rect.w, rect.y + rect.h });
				DrawLine(Point2d{ rect.x + rect.w, rect.y + rect.h }, Point2d{ rect.x, rect.y + rect.h });
				DrawLine(Point2d{ rect.x, rect.y + rect.h }, Point2d{ rect.x, rect.y});
			}
		}
		else {
			spdlog::error("SDL Renderer not assigned!");
		}
	}

	void Painter::DrawRRectangle(const SDL_Rect& rect, int16_t radius) const {
		if (nullptr != mRenderer) {
			auto penColor = mActivePen.PenColor();
			auto brushColor = mActiveBrush.BrushColor();

			// Dikdortgenin icini cizdirelim
			roundedBoxRGBA(mRenderer, rect.x + rect.w, rect.y, rect.x, rect.y + rect.h, radius, brushColor.R, brushColor.G, brushColor.B, brushColor.A);

			// Dikdortgen cercevesi var mi?
			if (mActivePen.Width() > 0) {
				roundedRectangleRGBA(mRenderer, rect.x + rect.w, rect.y, rect.x, rect.y + rect.h, radius, penColor.R, penColor.G, penColor.B, penColor.A);
			}
		}
		else {
			spdlog::error("SDL Renderer not assigned!");
		}
	}

	void Painter::DrawEllipse(const Point2d& point, int16_t radiusX, int16_t radiusY) const {
		if (nullptr != mRenderer) {
			auto penColor = mActivePen.PenColor();
			auto brushColor = mActiveBrush.BrushColor();

			// Elips ici dolu mu?
			if (0 != brushColor.A) {
				aaFilledEllipseRGBA(mRenderer, point.x, point.y, radiusX, radiusY, brushColor.R, brushColor.G, brushColor.B, brushColor.A);
			}

			// Elips cercevesi var mi?
			if (mActivePen.Width() > 0) {
				thickEllipseRGBA(mRenderer, point.x, point.y, radiusX, radiusY, penColor.R, penColor.G, penColor.B, penColor.A, mActivePen.Width());
			}
		}
		else {
			spdlog::error("SDL Renderer not assigned!");
		}
	}

	void Painter::DrawText(const Point2d& point, std::string_view text) {
		if (nullptr != mRenderer) {
			auto penColor = mActivePen.PenColor();
			stringRGBA(mRenderer, point.x, point.y, text.data(), penColor.R, penColor.G, penColor.B, penColor.A);
		}
		else {
			spdlog::error("SDL Renderer not assigned!");
		}
	}

	std::pair<uint32_t, uint32_t> Painter::ActiveFontSizeInfo(std::string_view fontLabel) const {
		std::string label{ fontLabel.data() };
		if (mFontSizeInfoList.contains(label)) {
			return mFontSizeInfoList.at(label);
		}
		return std::pair<uint32_t, uint32_t>(0, 0);
	}

	void Painter::SetActiveFont(std::string_view fontLabel) {
		std::string label{ fontLabel.data() };
		if (mFonts.contains(label)) {
			mActiveFont = label;

			auto fontSize = mFontSizeInfoList[mActiveFont];
			gfxPrimitivesSetFont(&mFonts[mActiveFont][0], fontSize.first, fontSize.second);
		}
	}

	bool Painter::RegisterFont(std::string_view fontLabel, std::string_view fontPath, uint32_t cw, uint32_t ch) {
		std::error_code ec;
		std::string label{ fontLabel.data() };
		try {
			mFonts.emplace(label, FileOperations::LoadFile(fontPath));
			mFontSizeInfoList.emplace(label, std::make_pair(cw, ch));

			spdlog::info("Font {} loaded successfully! Path: {}", fontLabel.data(), fontPath.data());
		}
		catch (const std::runtime_error& err) {
			spdlog::error("Error in loading \"{}\". Error: {}", fontPath.data(), err.what());
		}

		return false;
	}

	void Painter::_DrawPolyline(SDL_Renderer* renderer, const Point2d* polygon, int n, Uint8 r, Uint8 g, Uint8 b, Uint8 a) const {
		int i;
		const Point2d* point1;
		const Point2d * point2;

		// Vertex array NULL check
		if (nullptr == polygon) {
			return;
		}

		// Sanity check
		if (n < 3) {
			return;
		}

		// Pointer setup
		point1 = polygon;
		point2 = polygon;
		point2++;

		/*
		* Draw
		*/
		for (i = 1; i < n; i++) {
			aalineRGBA(renderer, point1->x, point1->y, point2->x, point2->y, r, g, b, a);
			point1 = point2;
			point2++;
		}

		aalineRGBA(renderer, polygon[0].x, polygon[0].y, point1->x, point1->y, r, g, b, a);
	}

	/*!
	\brief Global vertex array to use if optional parameters are not given in filledPolygonMT calls.
	Note: Used for non-multithreaded (default) operation of filledPolygonMT. */
	static int* gfxPrimitivesPolyIntsGlobal = NULL;

	/*!
	\brief Flag indicating if global vertex array was already allocated.
	Note: Used for non-multithreaded (default) operation of filledPolygonMT. */
	static int gfxPrimitivesPolyAllocatedGlobal = 0;

	void Painter::_DrawPolygon(SDL_Renderer* renderer, const Point2d* polygon, int n, Uint8 r, Uint8 g, Uint8 b, Uint8 a) const {

		int result;
		int i;
		int y, xa, xb;
		int miny, maxy;
		int x1, y1;
		int x2, y2;
		int ind1, ind2;
		int ints;
		int* gfxPrimitivesPolyInts = NULL;
		int* gfxPrimitivesPolyIntsNew = NULL;
		int gfxPrimitivesPolyAllocated = 0;
		int** polyInts{nullptr};
		int* polyAllocated{ nullptr };
		/*
		* Vertex array NULL check
		*/
		if (nullptr == polygon) {
			return;
		}

		/*
		* Sanity check number of edges
		*/
		if (n < 3) {
			return;
		}

		/*
		* Map polygon cache
		*/
		/* Use global cache */
		gfxPrimitivesPolyInts = gfxPrimitivesPolyIntsGlobal;
		gfxPrimitivesPolyAllocated = gfxPrimitivesPolyAllocatedGlobal;

		/*
		* Allocate temp array, only grow array
		*/
		if (!gfxPrimitivesPolyAllocated) {
			gfxPrimitivesPolyInts = (int*)malloc(sizeof(int) * n);
			gfxPrimitivesPolyAllocated = n;
		}
		else {
			if (gfxPrimitivesPolyAllocated < n) {
				gfxPrimitivesPolyIntsNew = (int*)realloc(gfxPrimitivesPolyInts, sizeof(int) * n);
				if (!gfxPrimitivesPolyIntsNew) {
					if (!gfxPrimitivesPolyInts) {
						free(gfxPrimitivesPolyInts);
						gfxPrimitivesPolyInts = NULL;
					}
					gfxPrimitivesPolyAllocated = 0;
				}
				else {
					gfxPrimitivesPolyInts = gfxPrimitivesPolyIntsNew;
					gfxPrimitivesPolyAllocated = n;
				}
			}
		}

		/*
		* Check temp array
		*/
		if (gfxPrimitivesPolyInts == NULL) {
			gfxPrimitivesPolyAllocated = 0;
		}

		/*
		* Update cache variables
		*/
		gfxPrimitivesPolyIntsGlobal = gfxPrimitivesPolyInts;
		gfxPrimitivesPolyAllocatedGlobal = gfxPrimitivesPolyAllocated;

		/*
		* Check temp array again
		*/
		if (gfxPrimitivesPolyInts == NULL) {
			return;
		}

		/*
		* Determine Y maxima
		*/
		miny = polygon[0].y;
		maxy = polygon[0].y;
		for (i = 1; (i < n); i++) {
			if (polygon[i].y < miny) {
				miny = polygon[i].y;
			}
			else if (polygon[i].y > maxy) {
				maxy = polygon[i].y;
			}
		}

		/*
		* Draw, scanning y
		*/
		result = 0;
		for (y = miny; (y <= maxy); y++) {
			ints = 0;
			for (i = 0; (i < n); i++) {
				if (!i) {
					ind1 = n - 1;
					ind2 = 0;
				}
				else {
					ind1 = i - 1;
					ind2 = i;
				}
				y1 = polygon[ind1].y;
				y2 = polygon[ind2].y;
				if (y1 < y2) {
					x1 = polygon[ind1].x;
					x2 = polygon[ind2].x;
				}
				else if (y1 > y2) {
					y2 = polygon[ind1].y;
					y1 = polygon[ind2].y;
					x2 = polygon[ind1].x;
					x1 = polygon[ind2].x;
				}
				else {
					continue;
				}
				if (((y >= y1) && (y < y2)) || ((y == maxy) && (y > y1) && (y <= y2))) {
					gfxPrimitivesPolyInts[ints++] = ((65536 * (y - y1)) / (y2 - y1)) * (x2 - x1) + (65536 * x1);
				}
			}

			qsort(gfxPrimitivesPolyInts, ints, sizeof(int), _gfxPrimitivesCompareInt);

			/*
			* Set color
			*/
			result = 0;
			result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? ::SDL_BLENDMODE_NONE : ::SDL_BLENDMODE_BLEND);
			result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);

			for (i = 0; (i < ints); i += 2) {
				xa = gfxPrimitivesPolyInts[i] + 1;
				xa = (xa >> 16) + ((xa & 32768) >> 15);
				xb = gfxPrimitivesPolyInts[i + 1] - 1;
				xb = (xb >> 16) + ((xb & 32768) >> 15);
				result |= hline(renderer, xa, xb, y);
			}
		}
	}
}