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

#ifndef VERSIONING_GENERIC_VERSION_H
#define VERSIONING_GENERIC_VERSION_H

#include "base_version.h"

namespace versioning {

    /// Base class for various version parsing, precedence ordering and data manipulation schemes.
    /**
    Basic_version class describes general version object without prescribing parsing,
    validation, comparison and modification rules. These rules are implemented by supplied Parser, Comparator
    and Modifier objects.
    */
    template<typename Parser, typename Comparator, typename Modifier>
    class GenericVersion: public BaseVersion {
    public:
        /// Construct Basic_version object using Parser object to parse default ("0.0.0") version string, Comparator for comparison and Modifier for modification.
        GenericVersion():BaseVersion(std::make_shared<Parser>(), std::make_shared<Comparator>(), std::make_shared<Modifier>())
        {}

        /// Construct Basic_version object using Parser to parse supplied version string, Comparator for comparison and Modifier for modification.
        GenericVersion(const std::string& v):BaseVersion(v, std::make_shared<Parser>(), std::make_shared<Comparator>(), std::make_shared<Modifier>())
        {}

        /// Construct Basic_version object using supplied Version_data, Parser, Comparator and Modifier objects.
        GenericVersion(const VersionData& v):BaseVersion(v, std::make_shared<Parser>(), std::make_shared<Comparator>(), std::make_shared<Modifier>())
        {}

    private:
        static_assert(std::is_base_of<VersionParser, Parser>::value, "Parser parameter must inherit from VersionParser");
        static_assert(std::is_base_of<VersionComparator, Comparator>::value, "Comparator parameter must inherit from VersionComparator");
        static_assert(std::is_base_of<VersionModifier, Modifier>::value, "Modifier parameter must inherit from VersionModifier");
    };
}

#endif //VERSIONING_GENERIC_VERSION_H
