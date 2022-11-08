/**
 * @file painter.h.
 * @date 29.07.2022
 * @author Yazilimperver
 * @brief	SDL2, SDL Font, SDL_Image, Gfx Primitives, Font Cache kutuphanesini kullanarak temel cizimler icin kullanilabilecek painter sinifidir.
 * 			Temel API arayuzu QPainter'dan esinlenmistir. 
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef PAINTER_H
#define PAINTER_H

#include <vector>
#include <memory>
#include <string_view>
#include <unordered_map>

#include "SDL.h"
#include "SDL_FontCache.h"
#include "spdlog/spdlog.h"

#include "basic_engine/sprite.h"

#include "common.h"
#include "pen.h"
#include "brush.h"

/** On tanimlamalar */
struct FC_Font;

/**
 * @class Painter
 * @brief Basit cizim islerini kotarmasi icin kullanabilecegimiz sinif
 * 		  TODO: Arc, Bezier, PIE cizimlerini de ekleyelim
 */
namespace basic_engine {
	class Painter {
	public:

		/** @brief Ileri font bilgileri */
		enum class FontStyle {
			Normal = 0x00,
			Bold = 0x01,
			Italic = 0x2,
			Underline = 0x4,
			StrikeThrough = 0x8
		};
		enum class Alignment {
			Left,
			Center,
			Right
		};

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

		/** @brief Temel sprite cizim API'leri */
		void DrawSprite(const Sprite* sprite);
		void DrawSprite(const Sprite* sprite, const SDL_Rect& destRect);

		/** @brief Ileri Font API'leri
				   Bu API'ler .ttf uzantili fontlari kullanmakta */

		/** @brief Ileri metin cizmi API'si */
		// Pack expansion kullanarak va_list vs ile didinmemize gerek kalmiyor ;)
		template <class ... Args>
		void Text(const Point2d& point, Alignment alignment, std::string_view formattedText, Args ... args);

		template <class ... Args>
		void TextInColumn(const Point2d& point, Alignment alignment, int32_t columnWidth, std::string_view formattedText, Args ... args);

		bool SetActiveFont(std::string_view fontLabel);
		bool RegisterFont(std::string_view fontLabel, std::string_view fontPath, uint32_t size = 12, FontStyle style = FontStyle::Normal);

		/** @brief Basit metin cizmi API'si */
		void SimpleText(const Point2d& point, std::string_view text);

		/** @brief Basit Font API'leri
				   Bu API'ler .fnt uzantili fontlari kullanmakta */
		std::pair<uint32_t, uint32_t> ActiveBasicFontSizeInfo(std::string_view fontLabel) const;
		void SetActiveBasicFont(std::string_view fontLabel);
		bool RegisterBasicFont(std::string_view fontLabel, std::string_view fontPath, uint32_t cw, uint32_t ch);
	protected:
		void _DrawPolyline(SDL_Renderer* renderer, const Point2d* polygon, int n, Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;
		void _DrawPolygon(SDL_Renderer* renderer, const Point2d* polygon, int n, Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;

		struct FontData {
			FC_Font* Font{nullptr};
			uint32_t Size{12};
			std::string Path;
			FontStyle Style{FontStyle::Normal};
			~FontData();
		};

		Pen mActivePen;
		Brush mActiveBrush;
		SDL_Renderer* mRenderer{ nullptr };		

		/** @brief Ileri font bilgileri */
		std::string mActiveFont{ "Default" };
		std::unordered_map<std::string, std::unique_ptr<FontData>> mFonts;

		/** @brief Temel font bilgileri */
		std::string mActiveBasicFont{ "Default" };
		std::unordered_map<std::string, std::vector<std::byte>> mBasicFonts;
		std::unordered_map<std::string, std::pair<uint32_t, uint32_t>> mBasicFontSizeInfoList;

	};

	/** @brief Ileri metin cizmi API'si */
	// Pack expansion kullanarak va_list vs ile didinmemize gerek kalmiyor ;)
	template<class ...Args>
	void Painter::Text(const Point2d& point, Alignment alignment, std::string_view formattedText, Args ...args) {
		if (nullptr != mRenderer) {
			auto penColor = mActivePen.PenColor();
			FC_Effect effect{ static_cast<FC_AlignEnum>(alignment),{ 1, 1 },{ penColor.R, penColor.G, penColor.B, penColor.A } };
			FC_DrawEffect(mFonts[mActiveFont]->Font, mRenderer, point.x, point.y, effect, formattedText.data(), args...);
		}
		else {
			spdlog::error("SDL Renderer not assigned!");
		}
	};

	template <class ... Args>
	void Painter::TextInColumn(const Point2d& point, Alignment alignment, int32_t columnWidth, std::string_view formattedText, Args ... args)	{
		if (nullptr != mRenderer) {
			auto penColor = mActivePen.PenColor();
			FC_Effect effect{ static_cast<FC_AlignEnum>(alignment),{ 1, 1 },{ penColor.R, penColor.G, penColor.B, penColor.A } };
			FC_DrawColumnEffect(mFonts[mActiveFont]->Font, mRenderer, point.x, point.y, columnWidth, effect, formattedText.data(), args...);
		}
		else {
			spdlog::error("SDL Renderer not assigned!");
		}
	}

	inline Painter::FontStyle operator |(Painter::FontStyle a, Painter::FontStyle b)
	{
		return static_cast<Painter::FontStyle>(static_cast<int>(a) | static_cast<int>(b));
	}

	inline Painter::FontStyle operator &(Painter::FontStyle a, Painter::FontStyle b)
	{
		return static_cast<Painter::FontStyle>(static_cast<int>(a) & static_cast<int>(b));
	}

	inline Painter::FontStyle& operator |=(Painter::FontStyle& a, Painter::FontStyle b)
	{
		return a = a | b;
	}
}
#endif // !PAINTER_H

/**
Copyright (c) [2022][Yazilimperver - yazilimpervergs@gmail.com]

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
