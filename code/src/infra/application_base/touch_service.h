/**
 * @file touch_service.h
 * @date 15.03.2022
 * @author Yazilimperver
 * @brief  SDL dokunma kabiliyetlerini kullanmak icin kullanilabilecek olan arayuzudr
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */

#ifndef TOUCH_SERVICE
#define TOUCH_SERVICE

#include <cstdint>
#include <optional>

struct FingerData;

class TouchService {
public:
    /**
        * @brief Get touch finger count
        * @param 	touchId The touch ID.
        * @returns The touch finger count.
        */
    virtual int32_t GetTouchFingerCount(int64_t touchId) = 0;

    /**
    * @brief Gets touch finger data
    * @param 		  	touchId    The touch ID.
    * @param 		  	index	   Zero-based index of the.
    * @returns The touch finger data.
    */
    virtual std::optional<FingerData> GetTouchFingerData(int64_t touchId, int32_t index) = 0;

    /**
    * @brief Gets touch device ID
    * @param 		  	index   Zero-based index of the.
    * @param [in,out]	touchId The touch ID.
    * @returns The touch device ID.
    */
    virtual std::optional<int64_t> GetTouchDeviceId(int32_t index) = 0;

    /**
    * @brief Gets touch device count
    * @returns The touch device count.
    */
    virtual int32_t GetTouchDeviceCount() = 0;
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


#endif /* TOUCH_SERVICE */
