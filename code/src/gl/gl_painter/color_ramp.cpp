#include "color_ramp.h"
#include <math.h>

namespace gl {
	const int32_t cEpsilon = 1;

	ColorRamp::ColorRamp(int32_t maxColorTableSize)
		: mMaxColorTableSize(maxColorTableSize)
	{

	}

	void ColorRamp::AddColor(int32_t value, const Color& color)
	{
		bool found = false;
		uint32_t index = 0U;

		for (; index < mAltitudeValues.size() && !found; ++index) {
			double currentValue = 0.0;
			currentValue = mAltitudeValues[index];

			if (mAltitudeValues[index] == value) {
				value += cEpsilon;
			}

			if (currentValue > value) {
				found = true;
			}
		}

		mAltitudeValues.push_back(value);
		mColors.push_back(color);
		
		if (mAltitudeValues.size() > 1U) {
			GenerateColorTable();
		}
	}

	void ColorRamp::GetColor(int32_t value, Color& color)	{
		// At least there must be two values otherwise color ramp is invalid.
		if (mAltitudeValues.size() > 1) {
			double minValue = 0.0;
			double maxValue = 0.0;
			minValue = mAltitudeValues[0];
			maxValue = mAltitudeValues[mAltitudeValues.size() - 1];

			if (value >= minValue && value <= maxValue) {
				uint32_t colorIndex = static_cast<int32_t>(((value - minValue) / (maxValue - minValue))*(mMaxColorTableSize - 1.0));

				if (colorIndex < mColorTable.size()) {
					color = mColorTable[colorIndex];
				}
			}
		}
	}

	void ColorRamp::GenerateColorTable() {
		double minValue = 0.0;
		double maxValue = 0.0;
		minValue = mAltitudeValues[0];
		maxValue = mAltitudeValues[mAltitudeValues.size() - 1];

		double valueStep = (maxValue - minValue) / mMaxColorTableSize;

		double currentValue = minValue;
		int32_t index = 0;

		Color startColor;
		Color endColor;
		startColor = mColors[index];
		endColor = mColors[index + 1];

		double startValue = 0.0;
		double endValue = 0.0;
		startValue = mAltitudeValues[index];
		endValue = mAltitudeValues[index + 1];

		for (int32_t i = 0; i < mMaxColorTableSize; ++i) {
			// if color
			if (currentValue > endValue) {
				index++;

				startValue = mAltitudeValues[index];
				endValue = mAltitudeValues[index + 1];

				startColor = mColors[index];
				endColor = mColors[index + 1];
			}

			// Calculate interpolated color.
			int32_t startRed = startColor.R;
			int32_t startGreen = startColor.G;
			int32_t startBlue = startColor.B;

			int32_t endRed = endColor.R;
			int32_t endGreen = endColor.G;
			int32_t endBlue = endColor.B;

			double colorScale = (currentValue - startValue) / (endValue - startValue);
			double red = startRed + (endRed - startRed) * colorScale;
			double green = startGreen + (endGreen - startGreen) * colorScale;
			double blue = startBlue + (endBlue - startBlue) * colorScale;

			Color color(static_cast<int32_t>(round(red)), static_cast<int32_t>(round(green)), static_cast<int32_t>(round(blue)));

			mColorTable.push_back(color);

			currentValue += valueStep;
		}

		if (mAltitudeValues.size() > 1) {
			mMinValue = mAltitudeValues[0];
			mMaxValue = mAltitudeValues[mAltitudeValues.size() - 1];

			mMaxMindDiffValue = (mMaxValue - mMinValue) / (mMaxColorTableSize - 1.0F);
		}
		else {
			mMinValue = 0.0F;
			mMaxValue = 0.0F;
			mMaxMindDiffValue = 1.0F;
		}
	}
}