#include "pen.h"

namespace basic_engine {
	Pen::Pen()
		: mWidth{ 1 }
		, mStrokeWidth{ 0 }
		, mColor{Color::Black}
		, mStrokeColor{ Color::Black } 	{
	}

	Pen::Pen(const Color& color)
		: mWidth{ 1 }
		, mStrokeWidth{ 0 }
		, mColor{ color }
		, mStrokeColor{ Color::Black } 	{
	}

	Pen::Pen(const Color& color, uint8_t width, const Color& strokeColor, uint8_t strokeWidth)
		: mWidth{ width }
		, mStrokeWidth{ strokeWidth }
		, mColor{ color }
		, mStrokeColor{ strokeColor } 	{
	}
	void Pen::SetWidth(uint8_t width) {
		mWidth = width;
	}
	uint8_t Pen::Width() const {
		return mWidth;
	}
	void Pen::SetStrokeWidth(uint8_t width) {
		mStrokeWidth = width;
	}
	uint8_t Pen::StrokeWidth() const {
		return mStrokeWidth;
	}
	void Pen::SetColor(const Color& color) {
		mColor = color;
	}
	Color Pen::PenColor() const {
		return mColor;
	}
	void Pen::SetStrokeColor(const Color& color) {
		mStrokeColor = color;
	}
	Color Pen::StrokeColor() const {
		return mStrokeColor;
	}
}