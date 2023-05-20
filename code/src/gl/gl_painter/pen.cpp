#include "pen.h"

namespace gl {
	Pen::Pen(PenStyle penStyle,
		const Color& color,
		float width,
		int32_t styleFactor,
		const Color& strokeColor,
		PenStyle strokeStyle,
		float strokeWidth)
		: mPenStyle(penStyle)
		, mWidth(width)
		, mColor(color)
		, mStyleFactor(styleFactor)
		, mStrokeColor(strokeColor)
		, mStrokePenStyle(strokeStyle)
		, mStrokePenWidth(strokeWidth)	{
	}

	Pen::Pen()
		: mPenStyle(PenStyle::SolidLine)
		, mWidth(1.0F)
		, mColor(Color::Black)
		, mStyleFactor(1)
		, mStrokePenStyle(PenStyle::SolidLine)
		, mStrokePenWidth(0.0F)
		, mStrokeColor(Color::Black)	{
	}

	Pen::Pen(const Color& color)
		: mColor(color)
		, mPenStyle(PenStyle::SolidLine)
		, mWidth(1.0F)
		, mStrokePenStyle(PenStyle::SolidLine)
		, mStrokePenWidth(0.0F)
		, mStrokeColor(Color::Black)	{
	}

	Pen::~Pen(void)	{
	}

	bool Pen::HasStroke() const	{
		return mStrokeWidth > 0.0F;
	}

	PenStyle Pen::GetPenStyle(bool isStroke) const	{
		if (true == isStroke){
			return mStrokePenStyle;
		}
		else {
			return mPenStyle;
		}
	}

	void Pen::SetPenStyle(PenStyle penStyle, bool isStroke)	{
		if (true == isStroke) {
			mStrokePenStyle = penStyle;
		}
		else {
			mPenStyle = penStyle;
		}
	}

	float Pen::GetWidth(bool isStroke) const {
		if (true == isStroke) {
			return mStrokePenWidth;
		}
		else {
			return mWidth;
		}
	}

	void Pen::SetWidth(float width, bool isStroke) {
		if (true == isStroke) {
			mStrokePenWidth = width;
		}
		else {
			mWidth = width;
		}
	}

	Color Pen::GetColor(bool isStroke) const {
		if (true == isStroke) {
			return mStrokeColor;
		}
		else {
			return mColor;
		}
	}

	void Pen::SetColor(const Color& color, bool isStroke) {
		if (true == isStroke) {
			mStrokeColor = color;
		}
		else {
			mColor = color;
		}
	}

	bool Pen::operator!=(const Pen& rhs)	{
		return !(*this == rhs);
	}

	bool Pen::operator==(const Pen& rhs) {
		return ((mStyleFactor == rhs.mStyleFactor) &&
			(mPenStyle == rhs.mPenStyle) &&
			(mWidth == rhs.mWidth) &&
			(mColor == rhs.mColor) &&
			(mStrokePenStyle == rhs.mStrokePenStyle) &&
			(mStrokePenWidth == rhs.mStrokePenWidth) &&
			(mStrokeColor == rhs.mStrokeColor));
	}

	void Pen::SetStyleFactor(int32_t factor)	{
		mStyleFactor = factor;
	}

	int32_t Pen::GetStyleFactor() const	{
		return mStyleFactor;
	}
}