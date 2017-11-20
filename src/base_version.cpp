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
    BaseVersion::BaseVersion(std::shared_ptr<VersionParser> p, std::shared_ptr<VersionComparator> c, std::shared_ptr<VersionModifier> m)
            : parser_(std::move(p)), comparator_(std::move(c)), modifier_(std::move(m)), ver_(parser_->Parse("0.0.0")) {}

    BaseVersion::BaseVersion(const std::string& v, std::shared_ptr<VersionParser> p, std::shared_ptr<VersionComparator> c, std::shared_ptr<VersionModifier> m)
            : parser_(std::move(p)), comparator_(std::move(c)), modifier_(std::move(m)), ver_(parser_->Parse(v)) {}

    BaseVersion::BaseVersion(const VersionData& v, std::shared_ptr<VersionParser> p, std::shared_ptr<VersionComparator> c, std::shared_ptr<VersionModifier> m)
            : parser_(std::move(p)), comparator_(std::move(c)), modifier_(std::move(m)), ver_(v) {}

    int BaseVersion::Major() const {
        return ver_.major;
    }

    int BaseVersion::Minor() const {
        return ver_.minor;
    }

    int BaseVersion::Patch() const {
        return ver_.patch;
    }

    const std::string BaseVersion::PreRelease() const {
        std::stringstream ss;
        splice(ss, ver_.prerelease_ids, ".", [](const auto& id) { return id.first;});
        return ss.str();
    }

    const std::string BaseVersion::Build() const {
        std::stringstream ss;
        splice(ss, ver_.build_ids, ".", [](const auto& id) { return id;});
        return ss.str();
    }

    BaseVersion BaseVersion::SetMajor(const int m) const {
        return BaseVersion(modifier_->SetMajor(ver_, m), parser_, comparator_, modifier_);
    }

    BaseVersion BaseVersion::SetMinor(const int m) const {
        return BaseVersion(modifier_->set_minor(ver_, m), parser_, comparator_, modifier_);
    }

    BaseVersion BaseVersion::SetPatch(const int p) const {
        return BaseVersion(modifier_->set_patch(ver_, p), parser_, comparator_, modifier_);
    }

    BaseVersion BaseVersion::SetPreRelease(
        const std::string &pr) const {
        auto vd = parser_->Parse("0.0.0-" + pr);
        return BaseVersion(modifier_->set_prerelease(ver_, vd.prerelease_ids), parser_, comparator_, modifier_);
    }
    
    BaseVersion BaseVersion::SetBuild(const std::string &b) const {
        auto vd = parser_->Parse("0.0.0+" + b);
        return BaseVersion(modifier_->set_build(ver_, vd.build_ids), parser_, comparator_, modifier_);
    }
    
    BaseVersion BaseVersion::ResetMajor(const int m) const {
        return BaseVersion(modifier_->reset_major(ver_, m), parser_, comparator_, modifier_);
    }
    
    BaseVersion BaseVersion::ResetMinor(const int m) const {
        return BaseVersion(modifier_->reset_minor(ver_, m), parser_, comparator_, modifier_);
    }
    
    BaseVersion BaseVersion::ResetPatch(const int p) const {
        return BaseVersion(modifier_->reset_patch(ver_, p), parser_, comparator_, modifier_);
    }
    
    BaseVersion BaseVersion::ResetPreRelease(
            const std::string &pr) const {
        std::string ver = "0.0.0-" + pr;
        auto vd = parser_->Parse(ver);
        return BaseVersion(modifier_->reset_prerelease(ver_, vd.prerelease_ids), parser_, comparator_, modifier_);
    }
    
    BaseVersion BaseVersion::ResetBuild(
            const std::string &b) const {
        std::string ver = "0.0.0+" + b;
        auto vd = parser_->Parse(ver);
        return BaseVersion(modifier_->reset_build(ver_, vd.build_ids), parser_, comparator_, modifier_);
    }
    
    BaseVersion BaseVersion::IncMajor(const int i) const {
        return ResetMajor(ver_.major + i);
    }
    
    BaseVersion BaseVersion::IncMinor(const int i) const {
        return ResetMinor(ver_.minor + i);
    }
    
    BaseVersion BaseVersion::IncPatch(const int i) const {
        return ResetPatch(ver_.patch + i);
    }

    bool operator<(const BaseVersion& l, const BaseVersion& r) {
        return l.comparator_->Compare(l.ver_, r.ver_) == -1;
    }

    bool operator==(const BaseVersion& l, const BaseVersion& r) {
        return l.comparator_->Compare(l.ver_, r.ver_) == 0;
    }

    std::ostream& operator<<(std::ostream& os, const BaseVersion& v) {
        os << v.ver_.major << "." << v.ver_.minor << "." << v.ver_.patch;
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