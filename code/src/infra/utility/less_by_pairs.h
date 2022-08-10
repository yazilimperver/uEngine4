/**
 * @file less_by_pairs.h.
 * @date 3.07.2022
 * @author Yazilimperver
 * @brief  Karmasik veri yapilarini map ve benzeri konteynerlerde kullanmak icin kullanailabilecek bir karsilastirma yardimcisi
 * 		   Burada variadic olarak gecirilme mekanizamsi ile farkli sayida uye iceren veri yapilari karsilastirilabilecektir.
 * 		   Bu fonksiyon karsilastirma operatorleri icerisinde kullanilabilir
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef LESS_BY_PAIRS_H
#define LESS_BY_PAIRS_H

bool LessByPairs();

template <typename T, typename U, typename ...Args>
bool LessByPairs(const T& v1, const U& v2, Args... args) {
	return v1 != v2 ? v1 < v2 : LessByPairs(args...);
}

#endif // LESS_BY_PAIRS_H

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
