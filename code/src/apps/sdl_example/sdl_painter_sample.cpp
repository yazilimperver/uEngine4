#include "sdl_painter_sample.h"

#include "SDL.h"
#include "sdl_application/sdl_application.h"

#include "asset/asset_repository.h"
#include "sdl_asset/sdl_texture_loader.h"

#include "basic_engine/game.h"

using namespace basic_engine;

void SdlPainterSample::Initialize(SdlApplication& sdlApplication) {
	mRenderer = sdlApplication.GetSdlRenderer();
	mParameters = sdlApplication.GetWindowParametrs();

	mPainter.AssignRenderer(mRenderer);

	mPainter.RegisterBasicFont("Font_7_13_Bold", "./7x13B.fnt", 7, 13);
	mPainter.RegisterBasicFont("Font_10_20", "./10x20.fnt", 10, 20);

	mPainter.RegisterFont("FreeSans_Italic_10", "fonts/FreeSans.ttf", 10, Painter::FontStyle::Bold | Painter::FontStyle::Italic);
	mPainter.RegisterFont("FreeSans_Normal_20", "fonts/FreeSans.ttf", 20);
	mPainter.RegisterFont("FreeSans_ItalicBold_12", "fonts/FreeSans.ttf", 12, Painter::FontStyle::Bold | Painter::FontStyle::Italic);

	// Sprite'i yukleyelim
	dynamic_cast<AssetRepository&>(Game::GetAssetService()).AssignRenderer(mRenderer);
	Game::GetAssetService().RegisterLoader(std::move(std::make_unique<SdlTextureLoader>()));
	SpriteParameter params{ "sprite.png", "dragon", 350, 100, SDL_FLIP_NONE };
	mSampleSprite = std::make_unique<Sprite>(params);

	SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_BLEND);
}

void SdlPainterSample::Update(double tickTimeInMsec) {
}

#include "painter/gfx_primitives.h"
void SdlPainterSample::Display(double tickTimeInMsec) {
	//Clear screen
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(mRenderer);

	mSampleSprite->Display(mRenderer, SDL_Rect{40, 360, 120, 120 });

	constexpr Point2d screenCenter{ 320, 240 };

	mPainter.AssignPen(Pen{ Color::Black, 5});
	mPainter.AssignBrush(Brush{ Color{255, 0, 0, 100} });
	mPainter.DrawEllipse(Point2d{ screenCenter.x, screenCenter.y }, 100, 50);

	mPainter.AssignPen(Pen{ Color::Black, 0 });
	mPainter.AssignBrush(Brush{ Color{0, 0, 255} });
	mPainter.DrawEllipse(Point2d{ screenCenter.x + 200, screenCenter.y }, 50, 50);

	mPainter.AssignPen(Pen{ Color::Green });
	mPainter.AssignBrush(Brush{ Color{0, 0, 255, 0} });
	mPainter.DrawEllipse(Point2d{ screenCenter.x - 200, screenCenter.y }, 50, 50);

	mPainter.AssignPen(Pen{ Color::Black, 1 });
	mPainter.DrawLine(screenCenter + Point2d{-100, 0}, screenCenter + Point2d{ 100, 50 });

	mPainter.AssignPen(Pen{ Color::Red, 3 });
	mPainter.DrawLine(screenCenter + Point2d{ -100, -40 }, (screenCenter + Point2d{ 100, 50-40 }));
	
	mPainter.AssignPen(Pen{ Color::Blue, 10, Color::Green, 18 });
	mPainter.DrawLine(screenCenter + Point2d{ -100, -80 }, (screenCenter + Point2d{ 100, 50-80 }));
	
	mPainter.AssignPen(Pen{ Color::Yellow, 8, Color::Black, 17 });
	mPainter.DrawLine(screenCenter + Point2d{ -100, -120 }, (screenCenter + Point2d{ 100, 50-120 }));

	mPainter.AssignPen(Pen{ Color::Black});
	mPainter.AssignBrush(Brush{ Color::Yellow });
	mPainter.DrawRectangle(SDL_Rect{ screenCenter.x + 100 , screenCenter.y + 50, 100, 50 });

	mPainter.AssignPen(Pen{ Color::Red, 3, Color::Black, 7});
	mPainter.AssignBrush(Brush{ Color::Transparent});
	mPainter.DrawRectangle(SDL_Rect{ screenCenter.x + 100 , screenCenter.y + 150, 100, 50 });

	mPainter.AssignPen(Pen{ Color::Black, 0 });
	mPainter.AssignBrush(Brush{ Color::Red });
	mPainter.DrawRRectangle(SDL_Rect{ screenCenter.x - 100 , screenCenter.y + 150, 100, 50 }, 20);

	mPainter.AssignPen(Pen{ Color::Black });
	mPainter.AssignBrush(Brush{ Color::Yellow });
	mPainter.DrawRRectangle(SDL_Rect{ screenCenter.x - 100 , screenCenter.y + 50, 100, 50 }, 10);

	std::vector polygon = { Point2d{150, 250}, Point2d{200, 300}, Point2d{175, 350}, Point2d{125, 350}, Point2d{100, 300} };
	mPainter.DrawPolygon(&polygon[0], static_cast<uint32_t>(polygon.size()));

	mPainter.AssignPen(Pen{ Color::Black });
	mPainter.SetActiveBasicFont("Font_7_13_Bold");
	mPainter.SimpleText(screenCenter + Point2d{ -300, -240 }, "[Basit] Merhaba Dunya_Siyah");

	mPainter.SetActiveBasicFont("Font_10_20");
	std::string text{ "Merhaba Dunya_Merkez" };
	auto fontSizeInfo = mPainter.ActiveBasicFontSizeInfo("Font_10_20");
	mPainter.SimpleText(screenCenter - Point2d{ text.size() /2 * fontSizeInfo.first, fontSizeInfo.second/2 }, "[Basit] Merhaba Dunya_Merkez");

	mPainter.SetActiveBasicFont("Font_7_13_Bold");
	mPainter.AssignPen(Pen{ Color::Red });
	mPainter.SimpleText(screenCenter + Point2d{ +110, +220 }, "[Basit] Merhaba Dunya_Kirmazi");

	mPainter.SetActiveFont("FreeSans_Normal_20");
	mPainter.AssignPen(Pen{ Color::Green });
	mPainter.Text(screenCenter + Point2d{ -300, -230 }, Painter::Alignment::Left, "[Ileri] Merhaba Dunya_Yesil:%d", 2022);

	mPainter.SetActiveFont("FreeSans_ItalicBold_12");
	mPainter.AssignPen(Pen{ Color::Magenta });
	mPainter.Text(screenCenter + Point2d{ 0, -200 }, Painter::Alignment::Center, "[Ileri] Merhaba Dunya Bold Italic_Magenta Center %d", 2022);

	mPainter.SetActiveFont("FreeSans_Italic_10");
	mPainter.AssignPen(Pen{ Color::Black });
	mPainter.TextInColumn(screenCenter + Point2d{ -310, -180 }, Painter::Alignment::Left, 200, "[Ileri] Uzun bir yaziyi diyelimki gormek istediniz artik bunu da basmaniz oldukca mumkun. Elbette coklu satir destegi de \n\n gordugunuz gibi mumkun ;) %d", 2022);
}

void SdlPainterSample::Finalize() {
}
