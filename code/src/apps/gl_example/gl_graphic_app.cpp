#include "gl_graphic_app.h"

#include <GL/glut.h>

#include "SDL.h"

#include "spdlog/spdlog.h"

#include "sdl_application/sdl_application.h"

#include "gl_texture/texture_asset.h"

#include "application_base/input_actions.h"
#include "application_base/keyboard_codes.h"

#include "graphics/point.h"

#include "configuration.h"

using namespace gl;

void GLGraphicApp::Initialize(SdlApplication& sdlApplication) {
    mSDLApplication = &sdlApplication;
    mRenderer = sdlApplication.GetSdlRenderer();
    mParameters = sdlApplication.GetWindowParametrs();

    SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_BLEND);

    // GL Painter'a yonelik ilkendirmeleri yapalim
    mPainter.RegisterFont("FreeSans_10", ASSET_ROOT_PATH + R"(FreeSans.ttf)", 10);
    mPainter.RegisterFont("FreeSans_12", ASSET_ROOT_PATH + R"(FreeSans.ttf)", 12);
    mPainter.RegisterFont("FreeSans_13", ASSET_ROOT_PATH + R"(FreeSans.ttf)", 13);
    mPainter.RegisterFont("FreeSans_20", ASSET_ROOT_PATH + R"(FreeSans.ttf)", 20);
    mPainter.RegisterFont("DefaultLazyFont_12", ASSET_ROOT_PATH + R"(lazy.ttf)", 20);
    mPainter.SetActiveFont("FreeSans_10");

    mPainter.SetBackgroundColor(Color::White);
    mPainter.InitializePainter();
    mPainter.SetDisplayExtent(0, mParameters.Width, mParameters.Height, 0);

    // Doku yukleme icin ilgili yukleyicinin tanimlayicisini alalim
    // Alternatif 1
    mTextureAssetHandle = sdlApplication.AssetService().LoadAsset("STBImageLoader", ASSET_ROOT_PATH + "sprite.png", "dragon");
    
    /* Alternatif 2
    auto loaderHandle = sdlApplication.AssetService().LoaderHandle("STBImageLoader");

    if (loaderHandle.has_value()) {
        mTextureAssetHandle = sdlApplication.AssetService().LoadAsset(loaderHandle.value(), ASSET_ROOT_PATH + "sprite.png", "dragon");
    }
    */

    if (!mTextureAssetHandle.has_value()) {
        spdlog::error("The provided asset load error!");
    }

    sdlApplication.RegisterEventListener(static_cast<KeyboardEventListener*>(this));    
}
void GLGraphicApp::Update(double tickTimeInMsec) {
}

void GLGraphicApp::Display(double tickTimeInMsec) {

    mPainter.Begin();
    constexpr glm::vec2 screenCenter{ 320, 240 };

    mPainter.ResetTransform();
    mPainter.SaveState();

        static float rotationInDegree = 0;
        rotationInDegree += 0.01f;
        rotationInDegree = fmod(rotationInDegree, 360.0f);

        float winWidth{ static_cast<float>(mParameters.Width) };
        float winHeight{ static_cast<float>(mParameters.Height) };

        constexpr float radius = 50.0f;
        mPainter.AssignPen(Pen{ PenStyle::SolidLine, Color::Black, 2 });
        mPainter.AssignBrush(Brush{ Color::Green });
        mPainter.DrawEllipse(Point{ screenCenter.x - winWidth / 2.f, screenCenter.y - winHeight / 2.f }, radius, radius);

        mPainter.AssignBrush(Brush{Color::Orange, BrushStyle::HalfTonePattern});
        mPainter.DrawEllipse(Point{ screenCenter.x - winWidth / 2.f, screenCenter.y + winHeight / 2.f }, radius, radius);

        mPainter.AssignBrush(Brush{ Color::Red , BrushStyle::DensePattern });
        mPainter.DrawEllipse(Point{ screenCenter.x + winWidth / 2.f, screenCenter.y + winHeight / 2.f }, radius, radius);

        mPainter.AssignBrush(Brush{ Color::Blue, BrushStyle::CrossPattern});
        mPainter.DrawEllipse(Point{ screenCenter.x + winWidth / 2.f, screenCenter.y - winHeight / 2.f }, radius, radius);

        mPainter.AssignPen(Pen{ PenStyle::SolidLine, Color::Red, 3 });
        mPainter.AssignBrush(Brush{ Color::Blue, BrushStyle::DiagonalCrossPattern });

        mPainter.Translate(glm::vec2{screenCenter.x, screenCenter.y - 120 });
        mPainter.SaveState();
            mPainter.Rotate(rotationInDegree);
            mPainter.DrawRectangle({ -50, -50, 100, 100 });
        mPainter.RestoreState();

    mPainter.RestoreState();
    
    if (mTextureAssetHandle.has_value()) {
        auto textureAsset = std::static_pointer_cast<gl::TextureAsset>(mSDLApplication->AssetService().SharedAsset(mTextureAssetHandle.value()));
        
        // Resmi renklendirmek icin :)
        mPainter.AssignBrush(Brush{ Color::White });
        mPainter.DrawTexture(textureAsset.get(), Vector2f{100, 420}, 120, 120);
    }

    mPainter.AssignPen(Pen{PenStyle::SolidLine, Color::Black, 3});
    mPainter.AssignBrush(Brush{ Color::Magenta });
    mPainter.DrawEllipse(glm::vec2{ screenCenter.x, screenCenter.y }, 100, 50);

    mPainter.AssignPen(Pen{ PenStyle::SolidLine, Color::Black, 3 });
    mPainter.AssignBrush(Brush{ Color::Cyan, BrushStyle::CheckPattern });
    mPainter.DrawEllipse(glm::vec2{ screenCenter.x + 200, screenCenter.y }, 50, 50);

    mPainter.AssignPen(Pen{ PenStyle::SolidLine, Color::Green, 3 });
    mPainter.AssignBrush(Brush{ Color::Blue, BrushStyle::DotPattern });
    mPainter.DrawEllipse(glm::vec2{ screenCenter.x - 200, screenCenter.y }, 50, 50);

    mPainter.AssignPen(Pen{ PenStyle::DoubleDotLine, Color::Orange, 5 });
    mPainter.DrawLine(Line{ screenCenter + glm::vec2{-100, 40}, screenCenter + glm::vec2{ 100, 90 } });

    mPainter.AssignPen(Pen{ PenStyle::SolidLine, Color::Black, 1 });
    mPainter.DrawLine(Line{ screenCenter + glm::vec2{-100, 0}, screenCenter + glm::vec2{ 100, 50 } });

    mPainter.AssignPen(Pen{ PenStyle::DashLine, Color::Red, 3 });
    mPainter.DrawLine(Line{ screenCenter + glm::vec2{ -100, -40 }, screenCenter + glm::vec2{ 100, 50 - 40 } });

    mPainter.AssignPen(Pen{ PenStyle::SolidLine, Color::Blue, 1, 1, Color::Green, PenStyle::SolidLine, 15 });
    mPainter.DrawLine(Line{ screenCenter + glm::vec2{ -100, -80 }, screenCenter + glm::vec2{ 100, 50 - 80 } });
    
    mPainter.AssignPen(Pen{ PenStyle::DotLine, Color::Yellow, 3, 1, Color::Black, PenStyle::SolidLine, 7 });
    mPainter.DrawLine(Line{ screenCenter + glm::vec2{ -100, -120 }, screenCenter + glm::vec2{ 100, 50 - 120 } });

    mPainter.AssignPen(Pen{ PenStyle::SolidLine, Color::Black, 1 });
    mPainter.AssignBrush(Brush{ Color::Yellow });
    mPainter.DrawRectangle(infra::Rectangle<float>{ screenCenter.x + 100 , screenCenter.y + 50, 100, 50 });
    
    // Delikli bir cember de cizebilir mi? Elbette
    mPainter.BeginClippingArea();
    mPainter.DrawEllipse(glm::vec2{ screenCenter.x + 200, screenCenter.y - 150 }, 50, 50);
    mPainter.EndClippingArea();
    mPainter.DrawEllipse(glm::vec2{ screenCenter.x + 200, screenCenter.y - 150 }, 100, 100);
    mPainter.ResetClippingArea();

    mPainter.AssignPen(Pen{ PenStyle::SolidLine, Color::Red, 3, 1, Color::Black, PenStyle::SolidLine, 7 });
    mPainter.AssignBrush(Brush{ Color::Transparent });
    mPainter.DrawRectangle(infra::Rectangle<float>{ screenCenter.x + 100 , screenCenter.y + 150, 100, 50 });

    std::vector polygon = { glm::vec2{150, 250}, glm::vec2{200, 300}, glm::vec2{175, 350}, glm::vec2{125, 350}, glm::vec2{100, 300}, glm::vec2{150, 250} };

    infra::Polygon polygonToDisplay;
    polygonToDisplay.SetPoints(polygon);
    mPainter.AssignPen(Pen{ PenStyle::SolidLine, Color::Black, 1 });
    mPainter.AssignBrush(Brush{ Color::Orange });
    mPainter.DrawPolygon(polygonToDisplay);

    mPainter.AssignPen(gl::Pen{ gl::PenStyle::SolidLine, Color::Black, 1 });
    mPainter.SetActiveFont("FreeSans_13");
    mPainter.SimpleText(screenCenter + glm::vec2{ -300, -240 }, "[Text] Merhaba Dunya_Siyah");
    
    mPainter.SetActiveFont("FreeSans_20");
    std::string text{ "[Text] Merhaba Dunya_Merkez" };
    mPainter.AssignPen(gl::Pen{ gl::PenStyle::SolidLine, Color::Blue, 2 });
    mPainter.SimpleText(screenCenter - glm::vec2{ text.size() / 2 * 10, 10 / 2 }, text);
        
    mPainter.SetActiveFont("FreeSans_13");
    mPainter.AssignPen(Pen{ gl::PenStyle::SolidLine, Color::Red, 1 });
    mPainter.SimpleText(screenCenter + glm::vec2{ +110, +220 }, "[Text] Merhaba Dunya_Kirmazi");

    mPainter.End();
}

void GLGraphicApp::Finalize() {
}

void GLGraphicApp::KeyboardEvent(KeyboardCodes key, int32_t scancode, InputActions action, KeyboardModifier mods) {
    if (InputActions::PressAction == action) {
        if (KeyboardCodes::KEY_UP == key) {
            spdlog::info("Up key pressed");
        }
        if (KeyboardCodes::KEY_DOWN == key) {
            spdlog::info("Down key pressed");
        }
        if (KeyboardCodes::KEY_RIGHT == key) {
            spdlog::info("Right key pressed");
        }
        if (KeyboardCodes::KEY_LEFT == key) {
            spdlog::info("Left key pressed");
        }
    }
}