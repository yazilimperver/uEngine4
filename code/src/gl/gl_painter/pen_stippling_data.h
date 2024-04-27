/**
 * @file   pen_stippling_data.h
 * @date   4/23/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_PEN_STIPPLING_DATA_H
#define INC_PEN_STIPPLING_DATA_H

#include <cstdint>

const uint16_t cNoPenStipple				= 0x0000;//
const uint16_t cSolidLineStipple		    = 0xFFFF;//_________
const uint16_t cDashLineStipple		    = 0x00FF;//---------
const uint16_t cDotLineStipple		    = 0x0101;//.........
const uint16_t cDoubleDotLine			= 0xCCCC;//..  ..  ..
const uint16_t cDashDashDotLineStipple   = 0x1C47;//--.--.--.
const uint16_t cDashDotLineStipple		= 0xF820;//-.-.-.-.-
const uint16_t cShortDashLongDashStipple = 0xCFF3; //- -- - --
const uint16_t cDefaultLineStipple		= 0xFFFF;//_________

#endif	// INC_PEN_STIPPLING_DATA_H

/**
Copyright (c) [2023][Yazilimperver - yazilimpervergs@gmail.com]

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


