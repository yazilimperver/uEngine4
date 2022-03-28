/**
 * @file gamepad_button_data.h.
 * @date 15.03.2022
 * @author Yazilimperver
 * @brief 
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#pragma once
#include <cstdint>

 /**
 * @struct uGamepadButtonData
 * @brief A gamepad button data.
 */
struct GamepadButtonData {
	/** @brief The left dpad */
	int8_t mLeftDPAD;
	/** @brief The right dpad */
	int8_t mRightDPAD;
	/** @brief The down dpad */
	int8_t mDownDPAD;
	/** @brief The up dpad */
	int8_t mUpDPAD;
	/** @brief a button */
	int8_t mAButton;
	/** @brief The b button */
	int8_t mBButton;
	/** @brief The x coordinate button */
	int8_t mXButton;
	/** @brief The y coordinate button */
	int8_t mYButton;
	/** @brief The start button */
	int8_t mStartButton;
	/** @brief The select button */
	int8_t mSelectButton;
	/** @brief The right shoulder button */
	int8_t mRightShoulderButton;
	/** @brief The left shoulder button */
	int8_t mLeftShoulderButton;
	/** @brief The guide button */
	int8_t mGuideButton;
	/** @brief The left stick button */
	int8_t mLeftStickButton;
	/** @brief The right stick button */
	int8_t mRightStickButton;
};

/**
Copyright (c) [2022][Yazilimperver - yazilimpervergs@gmail.com]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */
