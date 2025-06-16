#pragma once
#include <algorithm>

namespace vecutils {
    template<typename T>
    auto get_key(const T& x) -> decltype(x.name) {
        return x.name;
    }

    template<typename T>
    auto get_info(const T& x) -> decltype(x.getInfo()) {
        return x.getInfo();
    }

    template <typename Container, typename T>
    Container::const_iterator find_in_vector(const Container& vec, const T& key) {
        return std::find_if(vec.begin(), vec.end(), [&](const auto& entry) {
            return get_key(entry) == key;
            });
    }

    template <typename Container, typename T>
    bool is_in_vector(const Container& vec, const T& key) {
        return find_in_vector(vec, key) != vec.end();
    }

    template <typename Container>
    size_t max_len(const Container& items) {
        size_t max_len = 0;
        for (const auto& entry : items) {
            max_len = std::max(max_len, get_key(entry).size());
        }
        return max_len;
    }
}