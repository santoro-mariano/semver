
/*
The MIT License (MIT)

Copyright (c) 2017 Marko Zivanovic

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

#define BOOST_TEST_MODULE semver200_modifier_tests

#include <climits>
#include <boost/test/unit_test.hpp>
#include <versioning/semver/2_0_0/version.h>
#include "../../../src/exceptions.h"

namespace vsn { namespace semver {
    Comparator c;
    Parser p;
    Modifier m;

    #define CHECK_SRC { \
    BOOST_CHECK(v.Major() == 1); \
    BOOST_CHECK(v.Minor() == 2); \
    BOOST_CHECK(v.Patch() == 3); \
    BOOST_CHECK(v.PreRelease() == "pre.rel.0"); \
    BOOST_CHECK(v.Build() == "build.no.321"); \
    }

    BOOST_AUTO_TEST_CASE(set_major) {
        Version v("1.2.3-pre.rel.0+build.no.321");
        auto v2 = v.SetMajor(2);

        // Check if setter works as expected
        BOOST_CHECK(v2.Major() == 2);
        BOOST_CHECK(v2.Minor() == 2);
        BOOST_CHECK(v2.Patch() == 3);
        BOOST_CHECK(v2.PreRelease() == "pre.rel.0");
        BOOST_CHECK(v2.Build() == "build.no.321");

        // Check invalid values
        BOOST_CHECK_THROW(v.SetMajor(-1), vsn::ModificationError);

        // Check source version is unaffected
        CHECK_SRC
    }

    BOOST_AUTO_TEST_CASE(set_minor) {
        Version v("1.2.3-pre.rel.0+build.no.321");
        auto v2 = v.SetMinor(3);

        // Check if setter works as expected
        BOOST_CHECK(v2.Major() == 1);
        BOOST_CHECK(v2.Minor() == 3);
        BOOST_CHECK(v2.Patch() == 3);
        BOOST_CHECK(v2.PreRelease() == "pre.rel.0");
        BOOST_CHECK(v2.Build() == "build.no.321");

        // Check invalid values
        BOOST_CHECK_THROW(v.SetMinor(-1), vsn::ModificationError);

        // Check source version is unaffected
        CHECK_SRC
    }

    BOOST_AUTO_TEST_CASE(set_patch) {
        Version v("1.2.3-pre.rel.0+build.no.321");
        auto v2 = v.SetPatch(4);

        // Check if setter works as expected
        BOOST_CHECK(v2.Major() == 1);
        BOOST_CHECK(v2.Minor() == 2);
        BOOST_CHECK(v2.Patch() == 4);
        BOOST_CHECK(v2.PreRelease() == "pre.rel.0");
        BOOST_CHECK(v2.Build() == "build.no.321");

        // Check invalid values
        BOOST_CHECK_THROW(v.SetPatch(-1), vsn::ModificationError);

        // Check source version is unaffected
        CHECK_SRC
    }

    BOOST_AUTO_TEST_CASE(set_prerelease) {
        Version v("1.2.3-pre.rel.0+build.no.321");
        auto v2 = v.SetPreRelease("alpha.1");

        // Check if setter works as expected
        BOOST_CHECK(v2.Major() == 1);
        BOOST_CHECK(v2.Minor() == 2);
        BOOST_CHECK(v2.Patch() == 3);
        BOOST_CHECK(v2.PreRelease() == "alpha.1");
        BOOST_CHECK(v2.Build() == "build.no.321");

        // Check source version is unaffected
        CHECK_SRC
    }

    BOOST_AUTO_TEST_CASE(set_build) {
        Version v("1.2.3-pre.rel.0+build.no.321");
        auto v2 = v.SetBuild("b123");

        // Check if setter works as expected
        BOOST_CHECK(v2.Major() == 1);
        BOOST_CHECK(v2.Minor() == 2);
        BOOST_CHECK(v2.Patch() == 3);
        BOOST_CHECK(v2.PreRelease() == "pre.rel.0");
        BOOST_CHECK(v2.Build() == "b123");

        // Check source version is unaffected
        CHECK_SRC
    }

    BOOST_AUTO_TEST_CASE(reset_major) {
        Version v("1.2.3-pre.rel.0+build.no.321");
        auto v2 = v.ResetMajor(2);

        // Check if setter works as expected
        BOOST_CHECK(v2.Major() == 2);
        BOOST_CHECK(v2.Minor() == 0);
        BOOST_CHECK(v2.Patch() == 0);
        BOOST_CHECK(v2.PreRelease() == "");
        BOOST_CHECK(v2.Build() == "");

        // Check invalid values
        BOOST_CHECK_THROW(v.ResetMajor(-1), vsn::ModificationError);

        // Check source version is unaffected
        CHECK_SRC
    }

    BOOST_AUTO_TEST_CASE(reset_minor) {
        Version v("1.2.3-pre.rel.0+build.no.321");
        auto v2 = v.ResetMinor(3);

        // Check if setter works as expected
        BOOST_CHECK(v2.Major() == 1);
        BOOST_CHECK(v2.Minor() == 3);
        BOOST_CHECK(v2.Patch() == 0);
        BOOST_CHECK(v2.PreRelease() == "");
        BOOST_CHECK(v2.Build() == "");

        // Check invalid values
        BOOST_CHECK_THROW(v.ResetMinor(-1), vsn::ModificationError);

        // Check source version is unaffected
        CHECK_SRC
    }

    BOOST_AUTO_TEST_CASE(reset_patch) {
        Version v("1.2.3-pre.rel.0+build.no.321");
        auto v2 = v.ResetPatch(4);

        // Check if setter works as expected
        BOOST_CHECK(v2.Major() == 1);
        BOOST_CHECK(v2.Minor() == 2);
        BOOST_CHECK(v2.Patch() == 4);
        BOOST_CHECK(v2.PreRelease() == "");
        BOOST_CHECK(v2.Build() == "");

        // Check invalid values
        BOOST_CHECK_THROW(v.ResetPatch(-1), vsn::ModificationError);

        // Check source version is unaffected
        CHECK_SRC
    }

    BOOST_AUTO_TEST_CASE(reset_prerelease) {
        Version v("1.2.3-pre.rel.0+build.no.321");
        auto v2 = v.ResetPreRelease("alpha.1");

        // Check if setter works as expected
        BOOST_CHECK(v2.Major() == 1);
        BOOST_CHECK(v2.Minor() == 2);
        BOOST_CHECK(v2.Patch() == 3);
        BOOST_CHECK(v2.PreRelease() == "alpha.1");
        BOOST_CHECK(v2.Build() == "");

        // Check source version is unaffected
        CHECK_SRC
    }

    BOOST_AUTO_TEST_CASE(reset_build) {
        Version v("1.2.3-pre.rel.0+build.no.321");
        auto v2 = v.ResetBuild("b123");

        // Check if setter works as expected
        BOOST_CHECK(v2.Major() == 1);
        BOOST_CHECK(v2.Minor() == 2);
        BOOST_CHECK(v2.Patch() == 3);
        BOOST_CHECK(v2.PreRelease() == "pre.rel.0");
        BOOST_CHECK(v2.Build() == "b123");

        // Check source version is unaffected
        CHECK_SRC
    }

    BOOST_AUTO_TEST_CASE(inc_major) {
        Version v("1.2.3-pre.rel.0+build.no.321");

        // Check default increment
        auto v2 = v.IncMajor();
        BOOST_CHECK(v2.Major() == 2);
        BOOST_CHECK(v2.Minor() == 0);
        BOOST_CHECK(v2.Patch() == 0);
        BOOST_CHECK(v2.PreRelease() == "");
        BOOST_CHECK(v2.Build() == "");

        // Check non-default increment
        v2 = v.IncMajor(3);
        BOOST_CHECK(v2.Major() == 4);
        BOOST_CHECK(v2.Minor() == 0);
        BOOST_CHECK(v2.Patch() == 0);
        BOOST_CHECK(v2.PreRelease() == "");
        BOOST_CHECK(v2.Build() == "");

        // Check negative increment
        v2 = v.IncMajor(-1);
        BOOST_CHECK(v2.Major() == 0);
        BOOST_CHECK(v2.Minor() == 0);
        BOOST_CHECK(v2.Patch() == 0);
        BOOST_CHECK(v2.PreRelease() == "");
        BOOST_CHECK(v2.Build() == "");

        // Check too negative increment
        BOOST_CHECK_THROW(v.IncMajor(-2), vsn::ModificationError);

        // Check source version is unaffected
        CHECK_SRC
    }

    BOOST_AUTO_TEST_CASE(inc_minor) {
        Version v("1.2.3-pre.rel.0+build.no.321");

        // Check default increment
        auto v2 = v.IncMinor();
        BOOST_CHECK(v2.Major() == 1);
        BOOST_CHECK(v2.Minor() == 3);
        BOOST_CHECK(v2.Patch() == 0);
        BOOST_CHECK(v2.PreRelease() == "");
        BOOST_CHECK(v2.Build() == "");

        // Check non-default increment
        v2 = v.IncMinor(3);
        BOOST_CHECK(v2.Major() == 1);
        BOOST_CHECK(v2.Minor() == 5);
        BOOST_CHECK(v2.Patch() == 0);
        BOOST_CHECK(v2.PreRelease() == "");
        BOOST_CHECK(v2.Build() == "");

        // Check negative increment
        v2 = v.IncMinor(-1);
        BOOST_CHECK(v2.Major() == 1);
        BOOST_CHECK(v2.Minor() == 1);
        BOOST_CHECK(v2.Patch() == 0);
        BOOST_CHECK(v2.PreRelease() == "");
        BOOST_CHECK(v2.Build() == "");

        // Check too negative increment
        BOOST_CHECK_THROW(v.IncMinor(-3), vsn::ModificationError);

        // Check source version is unaffected
        CHECK_SRC
    }

    BOOST_AUTO_TEST_CASE(inc_patch) {
        Version v("1.2.3-pre.rel.0+build.no.321");

        // Check default increment
        auto v2 = v.IncPatch();
        BOOST_CHECK(v2.Major() == 1);
        BOOST_CHECK(v2.Minor() == 2);
        BOOST_CHECK(v2.Patch() == 4);
        BOOST_CHECK(v2.PreRelease() == "");
        BOOST_CHECK(v2.Build() == "");

        // Check default increment
        v2 = v.IncPatch(3);
        BOOST_CHECK(v2.Major() == 1);
        BOOST_CHECK(v2.Minor() == 2);
        BOOST_CHECK(v2.Patch() == 6);
        BOOST_CHECK(v2.PreRelease() == "");
        BOOST_CHECK(v2.Build() == "");

        // Check negative increment
        v2 = v.IncPatch(-1);
        BOOST_CHECK(v2.Major() == 1);
        BOOST_CHECK(v2.Minor() == 2);
        BOOST_CHECK(v2.Patch() == 2);
        BOOST_CHECK(v2.PreRelease() == "");
        BOOST_CHECK(v2.Build() == "");

        // Check too negative increment
        BOOST_CHECK_THROW(v.IncPatch(-4), vsn::ModificationError);

        // Check source version is unaffected
        CHECK_SRC
    }
}}
