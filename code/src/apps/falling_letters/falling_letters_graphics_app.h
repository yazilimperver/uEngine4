/**
 * @file falling_letters_graphics_app.h.
 * @date 8.11.2022
 * @author Yazilimperver
 * @brief 
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

constexpr int32_t cDropletterCount{ 50 };

class FallingLettersGraphicApp
	: public ClientGraphicApplication {
public:
	virtual void Initialize(SdlApplication& sdlApplication) override;
	virtual void Update(double tickTimeInMsec) override;
	virtual void Display(double tickTimeInMsec) override;
	virtual void Finalize() override;
	void SwitchRandomSource();
protected:
	SDL_Renderer* mRenderer{ nullptr };
	WindowParameter mParameters;
	basic_engine::Painter mPainter;


	// Her bir harfi temsil edecek nesne
	struct LetterDrop {
		Point2d Position;
		char    Letters[cDropletterCount][2];
		bool    IsExist{false};
		int16_t Speed { 5 };
		int16_t UpdateCount{ 0 };
		int16_t InitialAlpha{ 255 };
		Color   Color {0, 0xFF, 0x41};
	};

	// Kullanilan font ile ilgili veriler
	struct FontData {
		int32_t FontWidth{ 12 };
		int32_t FontHeight{ 12 };
	}mFontData;

	// Her guncellemede, ne kadarlik bir aydinlanma azaltmasi olacak
	int16_t mAlphaDecrement{ 2 };

	// Karakteri kac guncellemede bir degistirelim
	int16_t mWhenToUpdateLetter{ 6 };

	// Her bir sutun icin bir harfin konumunu belirtir
	std::vector<LetterDrop> mDrops;

	// Mersenne twister MT19937
	std::unique_ptr<std::mt19937> mRandEngine;

	// Random sayi kullanim kaynagimiz
	bool mUseMT{ true };
private:
	void UpdateDrops();

	// Random kullanimlari
	int32_t RandomInBetween(int32_t a, int32_t b);
	int32_t StdRandomInBetween(int32_t a, int32_t b);
	int32_t MTRandomInBetween(int32_t a, int32_t b);
	int32_t MTRandomInBetween2(int32_t a, int32_t b);
};

#endif // !FALLING_LETTERS_GRAPHICS_APP_H


// TODO
// +Random sayilari daha hizli ve duzgun almaca
// +Harfleri surekli degistirme
// +Birden fazla harf icerme
// +Matrix fontunu kullanma
// +Droplara omur bicme
// Ust uste gelen droplar