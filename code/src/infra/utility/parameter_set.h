/*!
 * @file	parameter_set.h.
 * @date	1.01.2021
 * @author	Yazilimperver
 * @brief	Class responsible for holding set of parameters that can be used for different purposes such as configuration
 */
#pragma once

#include <any>
#include <string>
#include <optional>
#include <unordered_map>

/*! @brief	This class is responsible for holding set of parameters */
class ParameterSet
{
public:
	/*! @brief	Print currently registered parameters */
	void PrintCurrentParameters();

	/*!
	 * @brief	This method update existing parameter value and add given parameter if not exist
	 *
	 * @param	paramName 	Parameter Name.
	 * @param	paramValue	Parameter Value.
	 */
	void UpdateParameterValue(const std::string& paramName, const std::any& paramValue);

	/*!
	 * @brief	This method check if current mapping contains given parameter name
	 *
	 * @param	paramName	The parameter that we will check.
	 *
	 * @returns	true if it exist, false o.w.
	 */
	bool HasParameter(const std::string& paramName);

	/*!
	 * @brief	paramName ile belirtilen parametre var ise temizler
	 *
	 * @param 	paramName	Name of the parameter.
	 *
	 * @returns	true if it exist, false o.w.
	 */
	bool RemoveParameter(const std::string& paramName);

	/*!
	 * @brief	Obtain parameter value with respect to given fiParametereld name
	 *
	 * @param	paramName	Parameter Name.
	 *
	 * @returns	The value of parameter if exist o.w. no value is returned!
	 */
	std::optional<std::any> GetParameterValue(const std::string& paramName);

	/*!
	 * @brief	The template version of getParameterValue which returns the requested value as
	 * 			parameter to prevent any cast
	 *
	 * @tparam	T	Generic type parameter.
	 * @param 		  	paramName 	Parameter Name.
	 * @param [in,out]	paramValue	Parameter Value.
	 *
	 * @returns	true if parameter is found, o.w. false.
	 */
	template <typename T>
	bool GetParameterValue(const std::string& paramName, T& paramValue);

	/*! @brief	Mevcut parametre listesini temizler */
	void Clear();
protected:

	/*! @brief	Each parameter will be registered via a Parameter name in string as they will not affect the runtime performance
				Each communication medium is responsible for specific parameter */
	std::unordered_map<std::string, std::any> mParameters;
};

/*!
 * @brief	Gets parameter value
 *
 * @tparam	T	Generic type parameter.
 * @param 		  	paramName 	Name of the parameter.
 * @param [in,out]	paramValue	The parameter value.
 *
 * @returns	True if it succeeds, false if it fails.
 */
template <typename T>
bool ParameterSet::GetParameterValue(const std::string& paramName, T& paramValue)
{
	bool isValueExist{ false };

	if (auto itr = mParameters.find(paramName); itr != mParameters.end())
	{
		if (auto valPtr = std::any_cast<T>(&itr->second); valPtr)
		{
			paramValue = *valPtr;
			isValueExist = true;
		}
	}

	return isValueExist;
}

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
