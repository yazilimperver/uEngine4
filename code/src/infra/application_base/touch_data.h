/**
 * @file touch_data.h.
 * @date 15.03.2022
 * @author Yazilimperver
 * @brief  Dokunma verilerini temsil eden veri yapisidir
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */

#ifndef TOUCH_DATA
#define TOUCH_DATA

#include <cstdint>

struct TouchData {
    /** @brief The touch device id (valid also for multi gesture) */
    uint64_t TouchDeviceId;

    /** @brief The finger id */
    uint64_t FingerId;

    /**
     * @brief	The x-axis location of the touch event, normalized (0...1)
     * 				the normalized center of gesture (valid  for multi gesture)
     */
    float X;

    /**
     * @brief	The y-axis location of the touch event, normalized (0...1)
     * 				the normalized center of gesture (valid  for multi gesture)
     */
    float Y;

    /** @brief The distance moved in the x - axis, normalized(-1...1) */
    float DX;

    /** @brief The distance moved in the y-axis, normalized (-1...1) */
    float DY;

    /** @brief The amount that the fingers rotated during this motion */
    float ThetaInRadian;

    /** @brief The amount that the fingers pinched during this motion */
    float DDist;

    /** @brief The quantity of pressure applied, normalized (0..1) */
    float Pressure;

    /** @brief Timestamp of the event (valid also for multi gesture) */
    uint32_t Timestamp;

    /** @brief Finger count (only valid for multi gesture) */
    uint16_t FingerCount;
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


#endif /* TOUCH_DATA */
