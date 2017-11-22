/*
The MIT License (MIT)

Copyright (c) 2015 Marko Zivanovic

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef VERSIONING_VECTOR_UTILS_H
#define VERSIONING_VECTOR_UTILS_H

#include <ostream>
#include <vector>

namespace vsn {
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
