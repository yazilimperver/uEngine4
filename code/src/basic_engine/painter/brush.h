#pragma once

#include <cstdint>

#include "graphics/color.h"

namespace  basic_engine {
	class Brush {
	public:
		Brush();
		Brush(const Color& color);
		void SetColor(const Color& color);
		Color BrushColor() const;
	protected:
		Color mColor;
	};
}
