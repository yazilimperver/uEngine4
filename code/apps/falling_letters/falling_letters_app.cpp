
#include "falling_letters_app.h"
#include "application_base/input_actions.h"
#include "application_base/keyboard_codes.h"
#include "spdlog/spdlog.h"

FallingLettersApp::FallingLettersApp() {
	UpdateGraphicApplication(mApp); // (5)
	RegisterEventListener(this); // (3)
}

void FallingLettersApp::KeyboardEvent(KeyboardCodes key, int32_t scancode, InputActions action, KeyboardModifier mods) {
	if (InputActions::PressAction == action) {
		if (KeyboardCodes::KEY_F1 == key) {
			// Animasyonu s�f�rlayal�m
		}
		else if (KeyboardCodes::KEY_Q== key) {
			spdlog::info("Uygulamadan cikalim!");
			Stop();
		}
		else if (KeyboardCodes::KEY_SPACE == key) {
			mApp->SwitchRandomSource();
		}
	}
}