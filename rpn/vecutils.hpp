#include <algorithm>

namespace vecutils {
    template <typename TupleVector, typename T>
    TupleVector::const_iterator find_in_vector(const TupleVector& vec, const T& key) {
        return std::find_if(vec.begin(), vec.end(), [&](const auto& entry) {
            return std::get<0>(entry) == key;
            });
    }

    template <typename TupleVector, typename T>
    bool is_in_vector(const TupleVector& vec, const T& key) {
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