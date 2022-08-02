#include "sdl_painter_sample.h"

#include "SDL.h"
#include "sdl_application/sdl_application.h"

using namespace basic_engine;

void SdlPainterSample::Initialize(SdlApplication& sdlApplication) {
	mRenderer = sdlApplication.GetSdlRenderer();
	mParameters = sdlApplication.GetWindowParametrs();

	mPainter.AssignRenderer(mRenderer);

	mPainter.RegisterFont("Font_7_13_Bold", "./7x13B.fnt", 7, 13);
	mPainter.RegisterFont("Font_10_20", "./10x20.fnt", 10, 20);
}

void SdlPainterSample::Update(double tickTimeInMsec) {
}


#include "painter/gfx_primitives.h"

void SdlPainterSample::Display(double tickTimeInMsec) {
	//Clear screen
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(mRenderer);

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
	mPainter.DrawPolygon(&polygon[0], polygon.size());

	mPainter.AssignPen(Pen{ Color::Black });
	mPainter.SetActiveFont("Font_7_13_Bold");
	mPainter.DrawText(screenCenter + Point2d{ -300, -240 }, "Merhaba Dunya_Siyah");

	mPainter.SetActiveFont("Font_10_20");
	std::string text{ "Merhaba Dunya_Merkez" };
	auto fontSizeInfo = mPainter.ActiveFontSizeInfo("Font_10_20");
	mPainter.DrawText(screenCenter - Point2d{ text.size() /2 * fontSizeInfo.first, fontSizeInfo.second/2 }, "Merhaba Dunya_Merkez");

	mPainter.SetActiveFont("Font_7_13_Bold");
	mPainter.AssignPen(Pen{ Color::Red });
	mPainter.DrawText(screenCenter + Point2d{ +110, +220 }, "Merhaba Dunya_Kirmazi");
}

void SdlPainterSample::Finalize() {
}
