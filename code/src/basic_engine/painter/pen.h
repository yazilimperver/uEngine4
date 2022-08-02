#pragma once

#include <cstdint>

#include "graphics/color.h"

namespace basic_engine {
	class Pen {
	public:
		Pen();
		explicit Pen(const Color& color);
		Pen(const Color& color,
			uint8_t width,
			const Color& strokeColor = Color::Black,
			uint8_t strokeWidth = 0.0F);
		void SetWidth(uint8_t width);
		uint8_t Width() const;
		void SetStrokeWidth(uint8_t width);
		uint8_t StrokeWidth() const;

		void SetColor(const Color& color);
		Color PenColor() const;
		void SetStrokeColor(const Color& color);
		Color StrokeColor() const;
	protected:
		uint8_t mWidth;
		uint8_t mStrokeWidth;
		Color mColor;
		Color mStrokeColor;
	};
}
