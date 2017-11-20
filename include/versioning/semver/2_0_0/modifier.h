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

#ifndef VERSIONING_MODIFIER_H
#define VERSIONING_MODIFIER_H

#include <versioning/version_modifier.h>

namespace versioning {
    namespace semver {
        namespace v200 {
            class Modifier: public VersionModifier {
            public:
                /// Set major version to specified value leaving all other components unchanged..
                VersionData SetMajor(const VersionData&, const int) const;

                /// Set minor version to specified value leaving all other components unchanged.
                VersionData set_minor(const VersionData&, const int) const;

                /// Set patch version to specified value leaving all other components unchanged.
                VersionData set_patch(const VersionData&, const int) const;

                /// Set pre-release version to specified value leaving all other components unchanged.
                VersionData set_prerelease(const VersionData&, const Prerelease_identifiers&) const;

                /// Set build version to specified value leaving all other components unchanged.
                VersionData set_build(const VersionData&, const Build_identifiers&) const;

                /// Set major version to specified value resetting all lower-priority components to zero/empty values.
                VersionData reset_major(const VersionData&, const int) const;

                /// Set minor version to specified value resetting all lower-priority components to zero/empty values.
                VersionData reset_minor(const VersionData&, const int) const;

                /// Set patch version to specified value resetting all lower-priority components to zero/empty values.
                VersionData reset_patch(const VersionData&, const int) const;

                /// Set pre-release version to specified value resetting all lower-priority components to zero/empty values.
                VersionData reset_prerelease(const VersionData&, const Prerelease_identifiers&) const;

                /// Set build version to specified value.
                VersionData reset_build(const VersionData&, const Build_identifiers&) const;
            };
        }
    }
}

#endif //VERSIONING_MODIFIER_H
