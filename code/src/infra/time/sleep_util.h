/**
 * @file sleep_util.h.
 * @date 30.04.2022
 * @author Yazilimperver
 * @brief Yuksek hassasiyette task uyutma icin kullanilabilecek fonksyonlar
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */

#ifndef SLEEPUTIL
#define SLEEPUTIL

#include <cstdint>

class SleepUtil {
public:
	/** @brief Windows platformuna ozel, hassas bekletme fonksiyonalitesi sunan bir metottur	 */
	static void USleep(int64_t sleepInUSec);

	/** @brief Platform bagimsiz, hassas bekletme fonksiyonalitesi sunan fonksiyondur
		       - Sleep API'si ile CPU korunmakta, fakat hassasiyet kaybolmaktadir.
			   - Spin-Lock ile de hassasiyet basarilmakta fakat CPU harcanmaktadir (temelde while loop icerisinde bekleme)
			   *  Welford’s algoritmasi kullanilmaktadir. Ref: https://www.wikiwand.com/en/Algorithms_for_calculating_variance#/Welford's_online_algorithm
		*/
	static void PreciseSleep(double seconds);
};

#endif // !SLEEPUTIL

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
