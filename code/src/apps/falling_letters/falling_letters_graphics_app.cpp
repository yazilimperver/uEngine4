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
	mPainter.RegisterFont(cFontToUse, "fonts/FreeSans.ttf", 12, Painter::FontStyle::Bold);

	// Harfleri dolduralim
	int column = 0;
	int height = 0;
	int fontWidth = 12;
	int fontHeight = 12;
	int columCount = mParameters.Width / fontWidth;

	std::random_device device;
	mRandEngine = std::make_unique< std::mt19937>(device());

	std::generate_n(std::back_inserter(mDrops),
		columCount,
		[&column, &height, fontWidth, fontHeight, this]() mutable {
			LetterDrop drop;
			drop.Position.x = column;
			drop.Position.y = RandomInBetween(0, mParameters.Height / 2);
			drop.Letter[0] = RandomInBetween('A', 'Z');
			drop.Color.A = RandomInBetween(128, 255);
			drop.Speed = RandomInBetween(2, 5);
			column += fontWidth;
			height += fontHeight/2;

			drop.IsExist = (rand() % 2) == 0;

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
			mPainter.AssignPen(Pen{ drop.Color});
			mPainter.Text(drop.Position, Painter::Alignment::Left, drop.Letter);
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
	for (auto& drop : mDrops) {
		if (drop.IsExist) { // var olanin konumu
			drop.Position.y+= drop.Speed;
			drop.UpdateCount++;

			if (drop.UpdateCount == mWhenToUpdateLetter) {
				drop.Letter[0] = RandomInBetween('A', 'Z');
				drop.UpdateCount = 0;
			}

			if (drop.Position.y > static_cast<int16_t>(mParameters.Height)) {
				drop.IsExist = false;
			}
		}
		else { // yeniden olusturalim
			drop.Position.y = RandomInBetween(0, mParameters.Height/2);
			drop.Letter[0] = RandomInBetween('A', 'Z');
			drop.Color.A = RandomInBetween(128, 255);
			drop.Speed = RandomInBetween(2, 5);
			drop.IsExist = true;
			drop.UpdateCount = 0;
		}
	}
}

int32_t FallingLettersGraphicApp::RandomInBetween(int32_t a, int32_t b) {
	if (mUseMT) {
		return MTRandomInBetween(a, b);
	}
	else {
		return StdRandomInBetween(a, b);
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
