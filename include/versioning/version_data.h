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

#ifndef VERSIONING_VERSION_DATA_H
#define VERSIONING_VERSION_DATA_H

#include <vector>
#include <string>

namespace versioning {

    /// Type of prerelease identifier: alphanumeric or numeric.
    /**
    Type of identifier affects comparison: alphanumeric identifiers are compared as ASCII strings, while
    numeric identifiers are compared as numbers.
    */
    enum class Id_type {
        alnum, ///< Identifier is alphanumerical
        num ///< Identifier is numeric
    };

    /// Container for prerelease identifier value and it's type.
    /**
    Prerelease version string consist of an optional series of dot-separated identifiers.
    These identifiers can be either numerical or alphanumerical.
    This structure describes one such identifier.
    */
    using Prerelease_identifier = std::pair<std::string, Id_type>;

    /// Container for all prerelease identifiers for a given version string.
    using Prerelease_identifiers = std::vector<Prerelease_identifier>;

    /// Build identifier is arbitrary string with no special meaning with regards to version precedence.
    using Build_identifier = std::string;

    /// Container for all build identifiers of a given version string.
    using Build_identifiers = std::vector<Build_identifier>;

    /// Description of version broken into parts, as per semantic versioning specification.
    struct VersionData {

        VersionData(const int M, const int m, const int p, const Prerelease_identifiers& pr, const Build_identifiers& b)
                : major{ M }, minor{ m }, patch{ p }, prerelease_ids{ pr }, build_ids{ b } {}

        int major; ///< Major version, change only on incompatible API modifications.
        int minor; ///< Minor version, change on backwards-compatible API modifications.
        int patch; ///< Patch version, change only on bugfixes.

        /// Optional series of prerelease identifiers.
        Prerelease_identifiers prerelease_ids;

        /// Optional series of build identifiers.
        Build_identifiers build_ids;
    };
}

#endif //VERSIONING_VERSION_DATA_H
