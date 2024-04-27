/*!
 * @file	parameter_set.h.
 * @date	1.01.2021
 * @author	Yazilimperver
 * @brief	Isim/deger parametreleri tutmak icin kullanilabilecek olan yardimci siniftir.
 */

#ifndef PARAMETERSET
#define PARAMETERSET

#include <any>
#include <string>
#include <optional>
#include <unordered_map>

class ParameterSet {
public:
	void PrintCurrentParameters();
	void UpdateParameterValue(const std::string& paramName, const std::any& paramValue);
	bool HasParameter(const std::string& paramName);
	bool RemoveParameter(const std::string& paramName);
	std::optional<std::any> GetParameterValue(const std::string& paramName);

	template <typename T>
	bool GetParameterValue(const std::string& paramName, T& paramValue) const;

	void Clear();
protected:
	std::unordered_map<std::string, std::any> mParameters;
};

template <typename T>
bool ParameterSet::GetParameterValue(const std::string& paramName, T& paramValue) const {
	bool isValueExist{ false };

	if (auto itr = mParameters.find(paramName); itr != mParameters.end()) {
		if (auto valPtr = std::any_cast<T>(&itr->second); valPtr) {
			paramValue = *valPtr;
			isValueExist = true;
		}
	}

	return isValueExist;
}

#endif // !PARAMETERSET

/*!
Copyright (c) [2022][yazilimpervergs@gmail.com]

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