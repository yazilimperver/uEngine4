#include "gl_graphic_app.h"

#include "SDL.h"

#include "sdl_application/sdl_application.h"

#include "application_base/input_actions.h"
#include "application_base/keyboard_codes.h"

#include "spdlog/spdlog.h"

#include "graphics/point.h"

#include <GL/glut.h>

using namespace gl;

void GLGraphicApp::Initialize(SdlApplication& sdlApplication) {
	mRenderer = sdlApplication.GetSdlRenderer();
	mParameters = sdlApplication.GetWindowParametrs();

	sdlApplication.RegisterEventListener(static_cast<KeyboardEventListener*>(this));

	//Initialize Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, mParameters.Width, mParameters.Height, 0.0, 1.0, -1.0);

	//Initialize Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	mBasicPainter.InitializePainter();
	mBasicPainter.SetDisplayExtent(0, mParameters.Width, mParameters.Height, 0);
}
void GLGraphicApp::Update(double tickTimeInMsec) {
}

void GLGraphicApp::Display(double tickTimeInMsec) {

	static float rotationInDegree = 0;	
	rotationInDegree += 0.01f;
	rotationInDegree = fmod(rotationInDegree, 360.0f);

	float winWidth { static_cast<float>(mParameters.Width)};
	float winHeight{ static_cast<float>(mParameters.Height)};
	
	mBasicPainter.Begin();
	mBasicPainter.ResetTransform();
	mBasicPainter.SetPen(Pen{ PenStyle::SolidLine, Color::Red, 3 });
	mBasicPainter.SetBrush(Brush{ Color::Blue });

	mBasicPainter.Translate(glm::vec2{ winWidth / 2.f, winHeight / 2.f });
	mBasicPainter.SaveState();
	mBasicPainter.Rotate(rotationInDegree);
	mBasicPainter.DrawRect({ -100, -100, 200, 200 });
	mBasicPainter.RestoreState();

	constexpr float radius = 50.0f;
	mBasicPainter.SetBrush(Brush{ Color::Green });
	mBasicPainter.DrawEllipse(Point{ -winWidth / 2.f, -winHeight / 2.f }, radius, radius);

	mBasicPainter.SetBrush(Brush{ Color::Yellow });
	mBasicPainter.DrawEllipse(Point{ -winWidth / 2.f, winHeight / 2.f }, radius, radius);

	mBasicPainter.SetBrush(Brush{ Color::Red });
	mBasicPainter.DrawEllipse(Point{ winWidth / 2.f, winHeight / 2.f }, radius, radius);

	mBasicPainter.SetBrush(Brush{ Color::Magenta });
	mBasicPainter.DrawEllipse(Point{ winWidth / 2.f, -winHeight / 2.f }, radius, radius);

	mBasicPainter.End();
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