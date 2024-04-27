#include "brush.h"

namespace gl {
	Brush::Brush(const Color& color, BrushStyle brushStyle)
		: mColor(color)
		, mStyle(brushStyle){
	}

	Brush::Brush()
		: mColor(Color::Black)
		, mStyle(BrushStyle::SolidPattern)	{
	}

	Brush::~Brush(void)	{
	}

	Color Brush::GetColor() const	{
		return mColor;
	}

	void Brush::SetColor(Color color)	{
		mColor = color;
	}

	BrushStyle Brush::GetStyle() const	{
		return mStyle;
	}

	void Brush::SetStyle(BrushStyle brushStyle)	{
		mStyle = brushStyle;
	}

	bool Brush::operator!=(const Brush& rhs) {
		return !(*this == rhs);
	}

	bool Brush::operator==(const Brush& rhs) {
		return ((mStyle == rhs.mStyle) &&
			(mColor == rhs.mColor));
	}
}