/*!
 * @file	UniqueIDGenerator.h.
 * @date	1.01.2021
 * @author	Yazilimperver
 * @brief	Declares the unique id generator class
 */
#pragma once

#include <cstdint>
#include <atomic>

/*!
 * @class	UniqueIDGenerator
 *
 * @brief	A unique ID generator.
 */
class UniqueIDGenerator {
public:

	/*!
	 * @fn	static void UniqueIDGenerator::reset();
	 *
	 * @brief	Resets this object
	 */
	static void Reset();

	/*!
	 * @fn	static uint64_t UniqueIDGenerator::getNextID();
	 *
	 * @brief	Gets the next ID
	 *
	 * @returns	The next ID.
	 */
	static uint64_t GetNextID();
private:

	/*! @brief	The ID source */
	inline static std::atomic<uint64_t> mIdSource{ 0U };
};

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

