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

#ifndef VERSIONING_READ_ONLY_VERSION_H
#define VERSIONING_READ_ONLY_VERSION_H

#include <string>
#include <vector>
#include "version_comparator.h"
#include "version_parser.h"
#include "version_modifier.h"
#include <memory>

namespace vsn {

    class ReadOnlyVersion {
    public:
        ReadOnlyVersion(VersionData data, const VersionComparator * comparator);

        int Major() const; ///< Get major version.
        int Minor() const; ///< Get minor version.
        int Patch() const; ///< Get patch version.
        const std::string PreRelease() const; ///< Get prerelease version string.
        const std::string Build() const; ///< Get build version string.

        friend bool operator<(const ReadOnlyVersion&, const ReadOnlyVersion&);
        friend bool operator==(const ReadOnlyVersion&, const ReadOnlyVersion&);
        friend std::ostream& operator<<(std::ostream&s, const ReadOnlyVersion&);

    protected:
        VersionData data_;

    private:
        const VersionComparator * comparator_;
    };

    /// Test if left-hand version operand is of lower precedence than the right-hand version.
    bool operator<(const ReadOnlyVersion&, const ReadOnlyVersion&);

    /// Test if left-hand version operand if of equal precedence as the right-hand version.
    bool operator==(const ReadOnlyVersion&, const ReadOnlyVersion&);

    /// Output version object to stream using standard semver format (X.Y.Z-PR+B).
    std::ostream& operator<<(std::ostream&, const ReadOnlyVersion&);

    /// Test if left-hand version and right-hand version are of different precedence.
    bool operator!=(const ReadOnlyVersion&, const ReadOnlyVersion&);

    /// Test if left-hand version operand is of higher precedence than the right-hand version.
    bool operator>(const ReadOnlyVersion&, const ReadOnlyVersion&);

    /// Test if left-hand version operand is of higher or equal precedence as the right-hand version.
    bool operator>=(const ReadOnlyVersion&, const ReadOnlyVersion&);

    /// Test if left-hand version operand is of lower or equal precedence as the right-hand version.
    bool operator<=(const ReadOnlyVersion&, const ReadOnlyVersion&);
}

#endif //VERSIONING_READ_ONLY_VERSION_H
