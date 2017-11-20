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

#include <climits>
#include "versioning/semver/2_0_0/modifier.h"
#include "../../exceptions.h"

namespace versioning {
	namespace semver {
		namespace v200 {
			VersionData Modifier::SetMajor(const VersionData & s, const int m) const {
				if (m < 0) throw ModificationError("major version cannot be less than 0");
				return VersionData{ m, s.minor, s.patch, s.prerelease_ids, s.build_ids };
			}

			VersionData Modifier::set_minor(const VersionData& s, const int m) const {
				if (m < 0) throw ModificationError("minor version cannot be less than 0");
				return VersionData{ s.major, m, s.patch, s.prerelease_ids, s.build_ids };
			}

			VersionData Modifier::set_patch(const VersionData& s, const int p) const {
				if (p < 0) throw ModificationError("patch version cannot be less than 0");
				return VersionData{ s.major, s.minor, p, s.prerelease_ids, s.build_ids };
			}

			VersionData Modifier::set_prerelease(const VersionData& s, const Prerelease_identifiers& pr) const {
				return VersionData{ s.major, s.minor, s.patch, pr, s.build_ids };
			}

			VersionData Modifier::set_build(const VersionData& s, const Build_identifiers& b) const {
				return VersionData{ s.major, s.minor, s.patch, s.prerelease_ids, b };
			}

			VersionData Modifier::reset_major(const VersionData&, const int m) const {
				if (m < 0) throw ModificationError("major version cannot be less than 0");
				return VersionData{ m, 0, 0, Prerelease_identifiers{}, Build_identifiers{} };
			}

			VersionData Modifier::reset_minor(const VersionData& s, const int m) const {
				if (m < 0) throw ModificationError("minor version cannot be less than 0");
				return VersionData{ s.major, m, 0, Prerelease_identifiers{}, Build_identifiers{} };
			}

			VersionData Modifier::reset_patch(const VersionData& s, const int p) const {
				if (p < 0) throw ModificationError("patch version cannot be less than 0");
				return VersionData{ s.major, s.minor, p, Prerelease_identifiers{}, Build_identifiers{} };
			}

			VersionData Modifier::reset_prerelease(const VersionData& s, const Prerelease_identifiers& pr) const {
				return VersionData{ s.major, s.minor, s.patch, pr, Build_identifiers{} };
			}

			VersionData Modifier::reset_build(const VersionData& s, const Build_identifiers& b) const {
				return VersionData{ s.major, s.minor, s.patch, s.prerelease_ids, b };
			}
		}
	}
}