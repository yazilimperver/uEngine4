/**
 * @file painter.h.
 * @date 29.07.2022
 * @author Yazilimperver
 * @brief	Gfx Primitives kutuphanesini kullanarak temel cizimler icin kullanilabilecek painter sinifidir.
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef PAINTER_H
#define PAINTER_H

#include <vector>
#include <string_view>
#include <unordered_map>

#include "SDL.h"

#include "common.h"

#include "pen.h"
#include "brush.h"

/**
 * @class Painter
 * @brief Basit cizim islerini kotarmasi icin kullanabilecegimiz sinif
 * 		  TODO: Arc, Bezier, PIE cizimlerini de ekleyelim
 */
namespace basic_engine {
	class Painter {
	public:
		void AssignRenderer(SDL_Renderer* renderer);
		void AssignPen(const Pen& pen);
		Pen ActivePen() const;
		void AssignBrush(const Brush& brush);
		Brush ActiveBrush() const;

		/** @brief Jenerik poligon cizme API'si 
				   Cerceve boyutu sabit ve stroke mevcut degil */
		void DrawPolygon(const Point2d* polygon, uint32_t vertexCount) const;
		void DrawPolyline(const Point2d* polygon, uint32_t vertexCount) const;

		/** @brief Jenerik dikdortgen cizme API'leri
				   Cerceve boyutu sabit */
		void DrawRectangle(const SDL_Rect& rect) const;

		/** @brief Jenerik yuvarlak kenarli dikdortgen cizme API'leri
				   Cerceve boyutu sabit ve stroke mevcut degil */
		void DrawRRectangle(const SDL_Rect& rect, int16_t radius) const;
		
		/** @brief Jenerik cizgi cizme API'si */
		void DrawLine(const Point2d& start, const Point2d& end) const;

		/** @brief Jenerik nokte cizme API'si */
		void DrawPoint(const Point2d& point) const;

		/** @brief Jenerik elips cizme API'si */
		void DrawEllipse(const Point2d& point, int16_t radiusX, int16_t radiusY) const;

		/** @brief Jenerik metin cizmi API'si */
		void DrawText(const Point2d& point, std::string_view text);

		/** @brief Font kontrolleri */
		std::pair<uint32_t, uint32_t> ActiveFontSizeInfo(std::string_view fontLabel) const;
		void SetActiveFont(std::string_view fontLabel);
		bool RegisterFont(std::string_view fontLabel, std::string_view fontPath, uint32_t cw, uint32_t ch);
	protected:
		void _DrawPolyline(SDL_Renderer* renderer, const Point2d* polygon, int n, Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;
		void _DrawPolygon(SDL_Renderer* renderer, const Point2d* polygon, int n, Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;

		Pen mActivePen;
		Brush mActiveBrush;
		SDL_Renderer* mRenderer{ nullptr };		

		std::string mActiveFont{ "Default" };
		std::unordered_map<std::string, std::vector<std::byte>> mFonts;
		std::unordered_map<std::string, std::pair<uint32_t, uint32_t>> mFontSizeInfoList;
	};
}
#endif // !PAINTER_H

