/**
 * @file falling_letters_graphics_app.h.
 * @date 8.11.2022
 * @author Yazilimperver
 * @brief  uEngine4 kullanýlarak Matriks düþen harf animasyonu gösterimi
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */

#ifndef FALLING_LETTERS_GRAPHICS_APP_H
#define FALLING_LETTERS_GRAPHICS_APP_H

#include <optional>
#include <vector>

#include "application_base/client_graphic_application.h"
#include "application_base/window_parameter.h"

#include "painter/painter.h"
#include "painter/common.h"

#include <random>
#include <ctime>

struct SDL_Renderer;

// Her bir harf sütununun içereceði harf adeti
constexpr int32_t cDropletterCount{ 50 };

/**
 * @class FallingLettersGraphicApp
 * @brief Düþen harflere iliþkin grafiksel jan janlarý yapacak yegane sýnýfýmýz
 */
class FallingLettersGraphicApp  // (4)
	: public ClientGraphicApplication {
public:
	virtual void Initialize(SdlApplication& sdlApplication) override;
	virtual void Update(double tickTimeInMsec) override;
	virtual void Display(double tickTimeInMsec) override;
	void SwitchRandomSource();
protected:
	// Her bir harfi temsil edecek nesne
	struct LetterDrop {  // (6)
		Point2d Position;
		char    Letters[cDropletterCount][2];
		bool    IsExist{false};	// Þu an aktif mi, deðil mi
		int16_t Speed { 5 };
		int16_t UpdateCount{ 0 };
		int16_t InitialAlpha{ 255 };
		Color   LetterColor {0, 0xFF, 0x41}; // Matriks yeþili
	};

	// Her bir sutun icin bir harfin konumunu belirtir (6)
	std::vector<LetterDrop> mDrops;

	// Kullanilan font ile ilgili veriler
	struct FontData {          // (7)
		int32_t FontWidth{ 14 };
		int32_t FontHeight{ 20 };
		std::string FontLabel{ "MatrixFont" };
		std::string FontPath{ "fonts/MatrixFont.ttf" };
	}mFontData; // (7)

	// Her guncellemede, ne kadarlik bir aydinlanma azaltmasi olacak (8)
	int16_t mAlphaDecrement{ 2 };

	// Karakteri kac guncellemede bir degistirelim (9)
	int16_t mWhenToUpdateLetter{ 6 };

	// Mersenne twister MT19937
	std::unique_ptr<std::mt19937> mRandEngine; // (10)

	// Random sayi kullanim kaynagimiz (10)
	bool mUseMT{ true };

	// SDL görselleþtirme nesnesi (11)
	SDL_Renderer* mRenderer{ nullptr };

	// Pencere parametreleri (12)
	WindowParameter mParameters;
	
	// Görselleþtirme nesnesi (13)
	basic_engine::Painter mPainter;
private:
	int32_t RandomInBetween(int32_t a, int32_t b); // (16)
};

#endif // !FALLING_LETTERS_GRAPHICS_APP_H

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
