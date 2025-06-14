#pragma once

#include <numbers>
#include <string>
#include <tuple>
#include <vector>

const std::vector<std::tuple<std::string, double, std::string>> const_map = {
    {"pi", std::numbers::pi, "π" },
    {"e",  std::numbers::e, "e (Euler's constant)" }
};
