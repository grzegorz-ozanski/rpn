#pragma once
#include <string>

class BaseInfo {
public:
	std::string name;
	std::string info;

	BaseInfo(const std::string& name, const std::string& info) : name(name), info(info) {}
	virtual ~BaseInfo() = default;
	virtual std::string getInfo() const {
		return info;
	}
};