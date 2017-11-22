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

#include <string>
#include <sstream>
#include <utility>
#include <versioning/base_version.h>
#include "vector_utils.h"

namespace versioning {
    BaseVersion::BaseVersion(const VersionData data, const VersionComparator & comparator)
            : data_{ std::move(data) }, comparator_{ comparator } {}

    int BaseVersion::Major() const {
        return data_.major;
    }

    int BaseVersion::Minor() const {
        return data_.minor;
    }

    int BaseVersion::Patch() const {
        return data_.patch;
    }

    const std::string BaseVersion::PreRelease() const {
        std::stringstream ss;
        splice(ss, data_.prerelease_ids, ".", [](const auto& id) { return id.first;});
        return ss.str();
    }

    const std::string BaseVersion::Build() const {
        std::stringstream ss;
        splice(ss, data_.build_ids, ".", [](const auto& id) { return id;});
        return ss.str();
    }

    bool operator<(const BaseVersion& l, const BaseVersion& r) {
        return l.comparator_.Compare(l.data_, r.data_) == -1;
    }

    bool operator==(const BaseVersion& l, const BaseVersion& r) {
        return l.comparator_.Compare(l.data_, r.data_) == 0;
    }

    std::ostream& operator<<(std::ostream& os, const BaseVersion& v) {
        os << v.data_.major << "." << v.data_.minor << "." << v.data_.patch;
        std::string prl = v.PreRelease();
        if (!prl.empty()) {
            os << "-" << prl;
        }
        std::string bld = v.Build();
        if (!bld.empty()) {
            os << "+" << bld;
        }
        return os;
    }

    bool operator!=(const BaseVersion& l, const BaseVersion& r) {
        return !(l == r);
    }

    bool operator>(const BaseVersion& l, const BaseVersion& r) {
        return r < l;
    }

    bool operator>=(const BaseVersion& l, const BaseVersion& r) {
        return !(l < r);
    }

    bool operator<=(const BaseVersion& l, const BaseVersion& r) {
        return !(l > r);
    }
}