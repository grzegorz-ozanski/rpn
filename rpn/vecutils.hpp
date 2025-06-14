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
}