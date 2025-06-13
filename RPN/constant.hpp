#pragma once

#include <map>
#include <numbers>
#include <string>
#include <tuple>

const std::map<std::string, std::tuple<double, std::string>> const_map = {
    {"pi", std::make_tuple(std::numbers::pi, "π")},
    {"e",  std::make_tuple(std::numbers::e, "e (Euler's constant)") }
};
