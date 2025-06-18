#pragma once

#include <format>
#include <numbers>
#include <string>
#include <vector>
#include "entry.hpp"

namespace rpn {
	class ConstantInfo : public EntryInfo {
	public:
		double value;

		ConstantInfo(const std::string& name, double value, const std::string& info)
			: EntryInfo(name, info), value(value) {
		}

		virtual std::string get_info() const {
			return info + " (value: " + std::format("{:.5f}", value) + ")";
		}

	};

	template <>
	inline const std::vector<ConstantInfo> EntryRegistry<ConstantInfo>::all = {
		{"pi", std::numbers::pi, "π" },
		{"e",  std::numbers::e, "e (Euler's constant)" }
	};

	using ReqisteredConstants = EntryRegistry<ConstantInfo>;
}