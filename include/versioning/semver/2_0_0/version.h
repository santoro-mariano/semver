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

#pragma once
#ifndef VERSIONING_SEMVER_VERSION_H
#define VERSIONING_SEMVER_VERSION_H

#include <versioning/generic_version.h>
#include "parser.h"
#include "comparator.h"
#include "modifier.h"

namespace vsn { namespace semver {
    /// Concrete version class that binds all semver 2.0.0 functionality together.
    class Version : public vsn::GenericVersion<Parser, Comparator, Modifier> {
    public:
        Version():GenericVersion(){}

        Version(const std::string& v):GenericVersion(v){}

        Version(const VersionData& v):GenericVersion(v){}
    };
}}

#endif //SEMVER_VERSION_H