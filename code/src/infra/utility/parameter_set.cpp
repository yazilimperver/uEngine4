#include "parameter_set.h"
#include <iostream>

void ParameterSet::PrintCurrentParameters() {
	for (auto &[key, val] : mParameters) {
		if (val.type() == typeid(int32_t))
			std::cout << "[" << key << " - int32_t type]: " << std::any_cast<int32_t>(val) << "\n";
		else if (val.type() == typeid(std::string))
			std::cout << "[" << key << " - string type]: " << std::any_cast<std::string>(val) << "\n";
		else if (val.type() == typeid(float))
			std::cout << "[" << key << " - float type]: " << std::any_cast<float>(val) << "\n";
		else if (val.type() == typeid(double))
			std::cout << "[" << key << " - double type]: " << std::any_cast<double>(val) << "\n";
		else if (val.type() == typeid(bool))
			std::cout << "[" << key << " - bool type]: " << (std::any_cast<bool>(val)?"TRUE":"FALSE") << "\n";
		else
			std::cout << "[" << key << " - unexpected type for print]!" << "\n";
	}
}

void ParameterSet::UpdateParameterValue(const std::string& paramName, const std::any& paramValue) {
	mParameters[paramName] = paramValue;
}

bool ParameterSet::HasParameter(const std::string& paramName) {
	return (mParameters.find(paramName) != mParameters.end());
}

bool ParameterSet::RemoveParameter(const std::string& paramName) {
	bool isItemFound{ false };

	if (auto itr = mParameters.find(paramName); itr != mParameters.end()) {
		mParameters.erase(paramName);
		isItemFound = true;
	}

	return isItemFound;
}

std::optional<std::any> ParameterSet::GetParameterValue(const std::string& paramName) {
	std::optional<std::any> parameterValue;

	if (auto itr = mParameters.find(paramName); itr != mParameters.end())
		parameterValue = itr->second;

	return parameterValue;
}

void ParameterSet::Clear() {
	mParameters.clear();
}
