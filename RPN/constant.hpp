#pragma once

#include <format>
#include <numbers>
#include <string>
#include <tuple>
#include <vector>
#include "info.hpp"
#include "vecutils.hpp"

class ConstantInfo : public BaseInfo {
public:
    double value;
    
    ConstantInfo(const std::string& name, double value, const std::string& info)
		: BaseInfo(name, info), value(value) {
	}

	virtual std::string getInfo() const {
		return info + " (value: " + std::format("{:.5f}", value) + ")";
	}

};

class ReqisteredConstants {
public:
    inline static const std::vector<ConstantInfo> all = {
        {"pi", std::numbers::pi, "π" },
        {"e",  std::numbers::e, "e (Euler's constant)" }
    };
    static bool contains(const Token& token) {
        return vecutils::is_in_vector(all, token.get_token());
    }
};

