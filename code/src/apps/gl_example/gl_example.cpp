#include "gl_example.h"
#include "application_base/input_actions.h"
#include "application_base/keyboard_codes.h"
#include "spdlog/spdlog.h"

GLExample::GLExample() {
	mClientGraphicalApplication = mGLGraphicApp;
	RegisterEventListener(this);
}

void GLExample::KeyboardEvent(KeyboardCodes key, int32_t scancode, InputActions action, KeyboardModifier mods) {
	static auto sampleIndex{ 0 };

	if (InputActions::PressAction == action) {
		if (KeyboardCodes::KEY_F12 == key) {
		}
		else if (KeyboardCodes::KEY_F11 == key) {
		}
	}
}
