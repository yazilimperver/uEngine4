#ifndef UNIQUEIDGENERATOR
#define UNIQUEIDGENERATOR

/*!
 * @file	UniqueIDGenerator.h.
 * @date	1.01.2021
 * @author	Yazilimperver
 * @brief	Essiz bir tanimlayici uretmek icin kullanilabilece olan bir siniftir
 */
#include <cstdint>
#include <atomic>

class UniqueIDGenerator {
public:
	static void Reset();
	static uint64_t GetNextID();
private:
	inline static std::atomic<uint64_t> mIdSource{ 0U };
};

#endif // !UNIQUEIDGENERATOR

/*!
Copyright (c) [2021][yazilimpervergs@gmail.com]

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

