#include <random>
#include <ctime>

#include "SDL.h"

#include "sdl_application/sdl_application.h"

#include "falling_letters_graphics_app.h"

using namespace basic_engine;

void FallingLettersGraphicApp::Initialize(SdlApplication& sdlApplication) {
	mRenderer = sdlApplication.GetSdlRenderer();
	mParameters = sdlApplication.GetWindowParametrs();

	// Painter'a muhakkak renderer'i gecirmeliyiz
	mPainter.AssignRenderer(mRenderer);

	// Kullanacagimiz font
	const std::string cFontToUse{ "MatrixFont" };
	mPainter.RegisterFont(cFontToUse, "fonts/MatrixFont.ttf", 20, Painter::FontStyle::Bold);
	mPainter.SetActiveFont(cFontToUse);

	std::random_device device;
	mRandEngine = std::make_unique< std::mt19937>(device());

	// Harfleri dolduralim
	int32_t column = 0;
	int32_t height = 0;
	int32_t columCount = mParameters.Width / mFontData.FontWidth;

	std::generate_n(std::back_inserter(mDrops),
		columCount,
		[&column, &height, this]() mutable {
			LetterDrop drop;
			drop.Position.x = column;
			for (auto& letter : drop.Letters) {
				letter[0] = '\0';
				letter[1] = '\0';
			}
			column += mFontData.FontWidth;
			return drop;
		}
	);
}

void FallingLettersGraphicApp::Update(double tickTimeInMsec) {
	UpdateDrops();
}

void FallingLettersGraphicApp::Display(double tickTimeInMsec) {
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(mRenderer);	

	Color colorToUse;

	for (const auto& drop : mDrops) {
		if (drop.IsExist) {
			colorToUse = Color::White;
			colorToUse.A = static_cast<uint8_t>(drop.InitialAlpha + 50);

			mPainter.AssignPen(Pen{ colorToUse });
			mPainter.Text(drop.Position, Painter::Alignment::Left, drop.Letters[0]);

			for (int32_t i = 1; i < cDropletterCount; i++) {
				colorToUse = drop.Color;
				if (drop.InitialAlpha - i * mAlphaDecrement > 0) {
					colorToUse.A = static_cast<uint8_t>(drop.InitialAlpha - i * mAlphaDecrement);
					mPainter.AssignPen(Pen{colorToUse});
					mPainter.Text(drop.Position - Point2d{ 0, i * mFontData.FontHeight }, Painter::Alignment::Left, drop.Letters[i]);
				}
				else 
					break; // sonraki harflere bu damla icin gerek yok
			}
		}
	}
}

void FallingLettersGraphicApp::Finalize() {
}

void FallingLettersGraphicApp::SwitchRandomSource() {
	mUseMT = !mUseMT;
	spdlog::info("Random fonksiyon kaynagi degistirildi. Son durumu: MT aktif mi? {}!", mUseMT);
}

void FallingLettersGraphicApp::UpdateDrops() {
	for (LetterDrop& drop : mDrops) {
		if (drop.IsExist) {
			drop.Position.y+= drop.Speed;
			drop.UpdateCount++;
			drop.InitialAlpha--;

			// Ilk harf disinda, degistirelim
			if (drop.UpdateCount == mWhenToUpdateLetter) {
				for (int32_t i = rand()%3; i < cDropletterCount;) {
					if (i%3)
						drop.Letters[i][0] = RandomInBetween('A', 'Z');
					else
						drop.Letters[i][0] = RandomInBetween('a', 'z');
					i = i + rand() % 3;
				}
				drop.UpdateCount = 0;
			}

			if ((drop.Position.y - cDropletterCount* mFontData.FontHeight) > static_cast<int16_t>(mParameters.Height)
				||
				drop.InitialAlpha <= 30) 
				drop.IsExist = false;
		}
		else {
			drop.Position.y = RandomInBetween(-48, mParameters.Height/4);			
			for (auto& letter: drop.Letters) 
				letter[0] = RandomInBetween('a', 'z');

			drop.InitialAlpha = RandomInBetween(180, 255);
			drop.Speed = RandomInBetween(2, 5);
			drop.IsExist = true;
			drop.UpdateCount = 0;
		}
	}
}

int32_t FallingLettersGraphicApp::RandomInBetween(int32_t a, int32_t b) {
	if (mUseMT) {
		std::uniform_int_distribution<int32_t> distribution(a, b);
		return distribution(*mRandEngine);
	}
	else 
		return a + rand() % (b + 1 - a);
}
