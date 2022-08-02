#include "brush.h"

namespace basic_engine {
	Brush::Brush()
		: mColor{ Color::Black } {
	}

	Brush::Brush(const Color& color)
		: mColor{ color } {
	}
	void Brush::SetColor(const Color& color) {
		mColor = color;
	}
	Color Brush::BrushColor() const {
		return mColor;
	}
}