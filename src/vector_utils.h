//
// Created by mariano on 11/19/17.
//

#ifndef VERSIONING_VECTOR_UTILS_H
#define VERSIONING_VECTOR_UTILS_H

#include <ostream>
#include <vector>

namespace versioning {

    /// Utility function to splice all vector elements to output stream, using designated separator
    /// between elements and function object for getting values from vector elements.
    template<typename T, typename F>
    std::ostream& splice(std::ostream& os, const std::vector<T>& vec, const std::string& sep, F read) {
        if (!vec.empty()) {
            for (auto it = vec.cbegin(); it < vec.cend() - 1; ++it) {
                os << read(*it) << sep;
            }
            os << read(*vec.crbegin());
        }
        return os;
    }
}

#endif //VERSIONING_VECTOR_UTILS_H
