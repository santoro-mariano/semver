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

#ifndef VERSIONING_BASE_VERSION_H
#define VERSIONING_BASE_VERSION_H

#include <string>
#include <vector>
#include "version_comparator.h"
#include "version_parser.h"
#include "version_modifier.h"
#include <memory>

namespace versioning {

    class BaseVersion {
    public:
        /// Construct Basic_version object using Parser object to parse default ("0.0.0") version string, Comparator for comparison and Modifier for modification.
        BaseVersion(std::shared_ptr<VersionParser> p, std::shared_ptr<VersionComparator> c, std::shared_ptr<VersionModifier> m);

        /// Construct Basic_version object using Parser to parse supplied version string, Comparator for comparison and Modifier for modification.
        BaseVersion(const std::string& v, std::shared_ptr<VersionParser> p, std::shared_ptr<VersionComparator> c, std::shared_ptr<VersionModifier> m);

        /// Construct Basic_version object using supplied Version_data, Parser, Comparator and Modifier objects.
        BaseVersion(const VersionData& v, std::shared_ptr<VersionParser> p, std::shared_ptr<VersionComparator> c, std::shared_ptr<VersionModifier> m);

        /// Construct Basic_version by copying data from another one.
        BaseVersion(const BaseVersion& v) = default;

        /// Copy version data from another Basic_version to this one.
        BaseVersion& operator=(const BaseVersion& v) = default;

        int Major() const; ///< Get major version.
        int Minor() const; ///< Get minor version.
        int Patch() const; ///< Get patch version.
        const std::string prerelease() const; ///< Get prerelease version string.
        const std::string build() const; ///< Get build version string.

        /// Return a copy of version with major component set to specified value.
        BaseVersion SetMajor(const int) const;

        /// Return a copy of version with the minor component set to specified value.
        BaseVersion SetMinor(const int) const;

        /// Return a copy of version with the patch component set to specified value.
        BaseVersion SetPatch(const int) const;

        /// Return a copy of version with the pre-release component set to specified value.
        BaseVersion SetPreRelease(const std::string &) const;

        /// Return a copy of version with the build component set to specified value.
        BaseVersion SetBuild(const std::string &) const;

        /// Return a copy of version with the major component reset to specified value.
        /**
        Exact implementation of reset is delegated to Modifier object.
        */
        BaseVersion ResetMajor(const int) const;

        /// Return a copy of version with the minor component reset to specified value.
        /**
        Exact implementation of reset is delegated to Modifier object.
        */
        BaseVersion ResetMinor(const int) const;

        /// Return a copy of version with the patch component reset to specified value.
        /**
        Exact implementation of reset is delegated to Modifier object.
        */
        BaseVersion ResetPatch(const int) const;

        /// Return a copy of version with the pre-release component reset to specified value.
        /**
        Exact implementation of reset is delegated to Modifier object.
        */
        BaseVersion ResetPreRelease(const std::string &) const;

        /// Return a copy of version with the build component reset to specified value.
        /**
        Exact implementation of reset is delegated to Modifier object.
        */
        BaseVersion ResetBuild(const std::string &) const;

        BaseVersion IncMajor(const int = 1) const;
        BaseVersion IncMinor(const int = 1) const;
        BaseVersion IncPatch(const int = 1) const;

        friend bool operator<(const BaseVersion&, const BaseVersion&);
        friend bool operator==(const BaseVersion&, const BaseVersion&);
        friend std::ostream& operator<<(std::ostream&s, const BaseVersion&);

    private:
        std::shared_ptr<VersionParser> parser_;
        std::shared_ptr<VersionComparator> comparator_;
        std::shared_ptr<VersionModifier> modifier_;
        VersionData ver_;
    };

    /// Test if left-hand version operand is of lower precedence than the right-hand version.
    bool operator<(const BaseVersion&, const BaseVersion&);

    /// Test if left-hand version operand if of equal precedence as the right-hand version.
    bool operator==(const BaseVersion&, const BaseVersion&);

    /// Output version object to stream using standard semver format (X.Y.Z-PR+B).
    std::ostream& operator<<(std::ostream&, const BaseVersion&);

    /// Test if left-hand version and right-hand version are of different precedence.
    bool operator!=(const BaseVersion&, const BaseVersion&);

    /// Test if left-hand version operand is of higher precedence than the right-hand version.
    bool operator>(const BaseVersion&, const BaseVersion&);

    /// Test if left-hand version operand is of higher or equal precedence as the right-hand version.
    bool operator>=(const BaseVersion&, const BaseVersion&);

    /// Test if left-hand version operand is of lower or equal precedence as the right-hand version.
    bool operator<=(const BaseVersion&, const BaseVersion&);
}

#endif //VERSIONING_BASE_VERSION_H
