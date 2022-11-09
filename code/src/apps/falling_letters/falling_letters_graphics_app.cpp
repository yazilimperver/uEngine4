#include <random>
#include <ctime>

#include "falling_letters_graphics_app.h"
#include "SDL.h"

#include "sdl_application/sdl_application.h"

using namespace basic_engine;

static const std::string cFontToUse{ "FreeSans_Bold_12" };

void FallingLettersGraphicApp::Initialize(SdlApplication& sdlApplication) {
	mRenderer = sdlApplication.GetSdlRenderer();
	mParameters = sdlApplication.GetWindowParametrs();

	// Painter'a muhakkak renderer'i gecirmeliyiz
	mPainter.AssignRenderer(mRenderer);

	// Kullanacagimiz font
	mPainter.RegisterFont(cFontToUse, "fonts/MatrixFont.ttf", 20, Painter::FontStyle::Bold);

	// Harfleri dolduralim
	int column = 0;
	int height = 0;
	int fontWidth = 16;
	int fontHeight = 32;
	int columCount = mParameters.Width / fontWidth;

	std::random_device device;
	mRandEngine = std::make_unique< std::mt19937>(device());

	std::generate_n(std::back_inserter(mDrops),
		columCount,
		[&column, &height, fontWidth, fontHeight, this]() mutable {
			LetterDrop drop;
			drop.Position.x = column;
			drop.Position.y = RandomInBetween(0, mParameters.Height / 3);
			for (auto& letter : drop.Letters) {
				letter[0] = '\0';
				letter[1] = '\0';
			}
			drop.Speed = RandomInBetween(4, 10);
			column += fontWidth;
			height += fontHeight/2;
			return drop;
		}
	);
}

void FallingLettersGraphicApp::Update(double tickTimeInMsec) {
	UpdateDrops();
}

void FallingLettersGraphicApp::Display(double tickTimeInMsec) {
	//Clear screen
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(mRenderer);	

	mPainter.SetActiveFont(cFontToUse);

	for (const auto& drop : mDrops) {
		if (drop.IsExist) {
			mPainter.AssignPen(Pen{ Color {255, 255, 255, static_cast<uint8_t>(drop.InitialAlpha + 50)} });
			mPainter.Text(drop.Position, Painter::Alignment::Left, drop.Letters[0]);

			for (int32_t i = 1; i < cDropletterCount; i++) {
				if (drop.InitialAlpha - i * mAlphaDecrement > 0) {
					mPainter.AssignPen(Pen{
										Color{ drop.Color.R, drop.Color.G, drop.Color.B,
										 static_cast<uint8_t>(drop.InitialAlpha - i * mAlphaDecrement)} });
					mPainter.Text(drop.Position - Point2d{ 0, i * mFontData.FontHeight }, Painter::Alignment::Left, drop.Letters[i]);
				}
				else {
					break;
				}
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
	// Oncelikle kaybolan bir drop var ise ekleyelim
	for (LetterDrop& drop : mDrops) {
		if (drop.IsExist) { // var olanin konumu
			drop.Position.y+= drop.Speed;
			drop.UpdateCount++;
			drop.InitialAlpha--;

			// Ilk harf disinda, degistirelim
			if (drop.UpdateCount == mWhenToUpdateLetter) {
				for (int i = rand()%3; i < cDropletterCount;) {
					drop.Letters[i][0] = RandomInBetween('a', 'z');
					i = i + rand() % 3;
				}
				drop.UpdateCount = 0;
			}

			if ((drop.Position.y - cDropletterCount* mFontData.FontHeight) > static_cast<int16_t>(mParameters.Height)
				||
				drop.InitialAlpha <= 30) {
				drop.IsExist = false;
			}
		}
		else { // yeniden olusturalim
			drop.Position.y = RandomInBetween(-48, mParameters.Height/4);
			for (auto& letter: drop.Letters) {
				letter[0] = RandomInBetween('a', 'z');
			}
			drop.InitialAlpha = RandomInBetween(180, 255);
			drop.Speed = RandomInBetween(2, 5);
			drop.IsExist = true;
			drop.UpdateCount = 0;
		}
	}
}

int32_t FallingLettersGraphicApp::RandomInBetween(int32_t a, int32_t b) {
	if (mUseMT) {
		return MTRandomInBetween2(a, b);
	}
	else {
		return MTRandomInBetween(a, b);
	}
}

int32_t FallingLettersGraphicApp::StdRandomInBetween(int32_t a, int32_t b) {
	return a + rand() % (b + 1 - a);
}

int32_t FallingLettersGraphicApp::MTRandomInBetween(int32_t a, int32_t b) {
	// Mersenne twister MT19937
	std::uniform_int_distribution<int32_t> distribution(a, b);
	return distribution(*mRandEngine);
}

int32_t FallingLettersGraphicApp::MTRandomInBetween2(int32_t a, int32_t b)
{
	std::uniform_int_distribution<int32_t> distribution;
	return a + distribution(*mRandEngine) % (b + 1 - a);
}
