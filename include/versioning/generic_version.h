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

#include "read_only_version.h"

namespace vsn {

    /// Base class for various version parsing, precedence ordering and data manipulation schemes.
    /**
    Basic_version class describes general version object without prescribing parsing,
    validation, comparison and modification rules. These rules are implemented by supplied Parser, Comparator
    and Modifier objects.
    */
    template<typename Parser, typename Comparator, typename Modifier>
    class GenericVersion: public ReadOnlyVersion {
    public:
        /// Construct Basic_version object using Parser object to parse default ("0.0.0") version string, Comparator for comparison and Modifier for modification.
        GenericVersion():ReadOnlyVersion(parser_.Parse("0.0.0"), &comparator_)
        {}

        /// Construct Basic_version object using Parser to parse supplied version string, Comparator for comparison and Modifier for modification.
        explicit GenericVersion(const std::string version):ReadOnlyVersion(parser_.Parse(std::move(version)), &comparator_)
        {}

        /// Construct Basic_version object using supplied Version_data, Parser, Comparator and Modifier objects.
        explicit GenericVersion(const VersionData data):ReadOnlyVersion(std::move(data), &comparator_)
        {}

        /// Return a copy of version with major component set to specified value.
        GenericVersion<Parser, Comparator, Modifier> SetMajor(const int m) const {
            return GenericVersion<Parser, Comparator, Modifier>(modifier_.SetMajor(data_, m));
        };

        /// Return a copy of version with the minor component set to specified value.
        GenericVersion<Parser, Comparator, Modifier> SetMinor(const int m) const {
            return GenericVersion<Parser, Comparator, Modifier>(modifier_.SetMinor(data_, m));
        };

        /// Return a copy of version with the patch component set to specified value.
        GenericVersion<Parser, Comparator, Modifier> SetPatch(const int p) const {
            return GenericVersion<Parser, Comparator, Modifier>(modifier_.SetPatch(data_, p));
        };

        /// Return a copy of version with the pre-release component set to specified value.
        GenericVersion<Parser, Comparator, Modifier> SetPreRelease(const std::string & pr) const {
                auto vd = parser_.Parse("0.0.0-" + pr);
                return GenericVersion<Parser, Comparator, Modifier>(modifier_.SetPreRelease(data_, vd.prerelease_ids));
        };

        /// Return a copy of version with the build component set to specified value.
        GenericVersion<Parser, Comparator, Modifier> SetBuild(const std::string & b) const {
            auto vd = parser_.Parse("0.0.0+" + b);
            return GenericVersion<Parser, Comparator, Modifier>(modifier_.SetBuild(data_, vd.build_ids));
        };

        /// Return a copy of version with the major component reset to specified value.
        /**
        Exact implementation of reset is delegated to Modifier object.
        */
        GenericVersion<Parser, Comparator, Modifier> ResetMajor(const int m) const {
            return GenericVersion<Parser, Comparator, Modifier>(modifier_.ResetMajor(data_, m));
        };

        /// Return a copy of version with the minor component reset to specified value.
        /**
        Exact implementation of reset is delegated to Modifier object.
        */
        GenericVersion<Parser, Comparator, Modifier> ResetMinor(const int m) const {
            return GenericVersion<Parser, Comparator, Modifier>(modifier_.ResetMinor(data_, m));
        };

        /// Return a copy of version with the patch component reset to specified value.
        /**
        Exact implementation of reset is delegated to Modifier object.
        */
        GenericVersion<Parser, Comparator, Modifier> ResetPatch(const int p) const {
            return GenericVersion<Parser, Comparator, Modifier>(modifier_.ResetPatch(data_, p));
        };

        /// Return a copy of version with the pre-release component reset to specified value.
        /**
        Exact implementation of reset is delegated to Modifier object.
        */
        GenericVersion<Parser, Comparator, Modifier> ResetPreRelease(const std::string & pr) const {
            std::string ver = "0.0.0-" + pr;
            auto vd = parser_.Parse(ver);
            return GenericVersion<Parser, Comparator, Modifier>(modifier_.ResetPreRelease(data_, vd.prerelease_ids));
        };

        /// Return a copy of version with the build component reset to specified value.
        /**
        Exact implementation of reset is delegated to Modifier object.
        */
        GenericVersion<Parser, Comparator, Modifier> ResetBuild(const std::string & b) const {
                std::string ver = "0.0.0+" + b;
                auto vd = parser_.Parse(ver);
                return GenericVersion<Parser, Comparator, Modifier>(modifier_.ResetBuild(data_, vd.build_ids));
        };

        GenericVersion<Parser, Comparator, Modifier> IncMajor(const int i = 1) const {
            return ResetMajor(data_.major + i);
        };

        GenericVersion<Parser, Comparator, Modifier> IncMinor(const int i = 1) const {
            return ResetMinor(data_.minor + i);
        };

        GenericVersion<Parser, Comparator, Modifier> IncPatch(const int i = 1) const {
            return ResetPatch(data_.patch + i);
        };

    private:
        static_assert(std::is_base_of<VersionParser, Parser>::value, "Parser parameter must inherit from VersionParser");
        static_assert(std::is_base_of<VersionComparator, Comparator>::value, "Comparator parameter must inherit from VersionComparator");
        static_assert(std::is_base_of<VersionModifier, Modifier>::value, "Modifier parameter must inherit from VersionModifier");

        static VersionParser& parser_;
        static VersionComparator& comparator_;
        static VersionModifier& modifier_;
    };

    template<typename Parser, typename Comparator, typename Modifier>
    VersionParser& GenericVersion<Parser,Comparator,Modifier>::parser_ = Parser();

    template<typename Parser, typename Comparator, typename Modifier>
    VersionComparator& GenericVersion<Parser,Comparator,Modifier>::comparator_ = Comparator();

    template<typename Parser, typename Comparator, typename Modifier>
    VersionModifier& GenericVersion<Parser,Comparator,Modifier>::modifier_ = Modifier();
}

#endif //VERSIONING_GENERIC_VERSION_H
