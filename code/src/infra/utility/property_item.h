/*!
 * @file	property_item.h.
 * @date	19.01.2021
 * @author	Yazilimperver
 * @brief	
 * @remark	Copyright (c) 2021, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#pragma once
#include <string>
#include <any>

/*! @brief	Property item for name value pair. */
struct PropertyItem {
	/*! @brief	Default constructor */
	PropertyItem();

	/*!
	 * @brief	Yapici
	 *
	 * @param 	name 	Ýsim
	 * @param 	value	Ýlgili deðer
	 */
	PropertyItem(const std::string& name, const std::any& value);

	/*! @brief	The name */
	std::string mName;
	
	/*! @brief	The value */
	std::any mValue;
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
