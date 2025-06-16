#include <algorithm>

namespace vecutils {
    template<typename T>
    auto get_key(const T& x) {
        return std::get<0>(x);
    }

    template <typename Container, typename T>
    Container::const_iterator find_in_vector(const Container& vec, const T& key) {
        return std::find_if(vec.begin(), vec.end(), [&](const auto& entry) {
            return std::get<0>(entry) == key;
            });
    }

    template <typename Container, typename T>
    bool is_in_vector(const Container& vec, const T& key) {
        return find_in_vector(vec, key) != vec.end();
    }

    template <typename Container, size_t Index=0>
    size_t max_len(const Container& items) {
        size_t max_len = 0;
        for (const auto& entry : items) {
            max_len = std::max(max_len, std::get<Index>(entry).size());
        }
        return max_len;
    }
}