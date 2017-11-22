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

#include <functional>
#include <versioning/version_data.h>
#include "../../exceptions.h"
#include "versioning/semver/2_0_0/parser.h"

#ifdef _MSC_VER
// disable symbol name too long warning
#pragma warning(disable:4503)
#endif

namespace vsn {	namespace semver {
    const std::vector<std::pair<char, char>> Parser::allowed_prerel_id_chars = {
            { '0', '9' },{ 'A','Z' },{ 'a','z' },{ '-','-' }
    };

    inline Transition Parser::mkx(const char c, ParserState p, State_transition_hook pth) const {
        return std::make_tuple(c, p, pth);
    }

    inline void Parser::process_char(const char c, ParserState& cstate, ParserState& pstate,
                             const Transitions& transitions, std::string& target, Validator validate) const {
        for (const auto& transition : transitions) {
            if (c == std::get<0>(transition)) {
                if (std::get<2>(transition)) std::get<2>(transition)(target);
                pstate = cstate;
                cstate = std::get<1>(transition);
                return;
            }
        }
        validate(target, c);
        target.push_back(c);
    }

    inline void Parser::normal_version_validator(const std::string& tgt, const char c) {
        if (c < '0' || c > '9') throw ParseError("invalid character encountered: " + std::string(1, c));
        if (tgt.compare(0, 1, "0") == 0) throw ParseError("leading 0 not allowed");
    }

    inline void Parser::prerelease_version_validator(const std::string&, const char c) {
        bool res = false;
        for (const auto& r : allowed_prerel_id_chars) {
            res |= (c >= r.first && c <= r.second);
        }
        if (!res)
            throw ParseError("invalid character encountered: " + std::string(1, c));
    }

    inline bool Parser::is_identifier_numeric(const std::string& id) const {
        return id.find_first_not_of("0123456789") == std::string::npos;
    }

    inline bool Parser::check_for_leading_0(const std::string& str) const {
        return str.length() > 1 && str[0] == '0';
    }

    void Parser::prerelease_hook_impl(std::string& id, Prerelease_identifiers& prerelease) const {
        if (id.empty()) throw ParseError("version identifier cannot be empty");
        Id_type t = Id_type::alnum;
        if (is_identifier_numeric(id)) {
            t = Id_type::num;
            if (check_for_leading_0(id)) {
                throw ParseError("numeric identifiers cannot have leading 0");
            }
        }
        prerelease.push_back({id, t});
        id.clear();
    }

    void Parser::build_hook_impl(std::string& id, ParserState & pstate, Build_identifiers& build,
                         std::string& prerelease_id, Prerelease_identifiers& prerelease) const {
        // process last token left from parsing prerelease data
        if (pstate == ParserState::prerelease) prerelease_hook_impl(prerelease_id, prerelease);
        if (id.empty()) throw ParseError("version identifier cannot be empty");
        build.push_back(id);
        id.clear();
    }

    /// Parse semver 2.0.0-compatible string to Version_data structure.
    /**
    Version text parser is implemented as a state machine. In each step one successive character from version
    string is consumed and is either added to current token or triggers state transition. Hooks can be
    injected into state transitions for validation/customization purposes.
    */
    VersionData Parser::Parse(const std::string &s) const {
        std::string major;
        std::string minor;
        std::string patch;
        std::string prerelease_id;
        std::string build_id;
        Prerelease_identifiers prerelease;
        Build_identifiers build;
        ParserState cstate{ ParserState::major };
        ParserState pstate;

        auto prerelease_hook = [&](std::string& id) {
            prerelease_hook_impl(id, prerelease);
        };

        auto build_hook = [&](std::string& id) {
            build_hook_impl(id, pstate, build, prerelease_id, prerelease);
        };

        // State transition tables
        auto major_trans = {
                mkx('.', ParserState::minor, {})
        };
        auto minor_trans = {
                mkx('.', ParserState::patch, {})
        };
        auto patch_trans = {
                mkx('-', ParserState::prerelease, {}),
                mkx('+', ParserState::build, {})
        };
        auto prerelease_trans = {
                // When identifier separator (.) is found, stay in the same state but invoke hook
                // in order to process each individual identifier separately.
                mkx('.', ParserState::prerelease, prerelease_hook),
                mkx('+', ParserState::build, {})
        };
        auto build_trans = {
                // Same stay-in-the-same-state-but-invoke-hook trick from above.
                mkx('.', ParserState::build, build_hook)
        };

        State_machine state_machine = {
                {ParserState::major, State{major_trans, major, normal_version_validator}},
                {ParserState::minor, State{minor_trans, minor, normal_version_validator}},
                {ParserState::patch, State{patch_trans, patch, normal_version_validator}},
                {ParserState::prerelease, State{prerelease_trans, prerelease_id, prerelease_version_validator}},
                {ParserState::build, State{build_trans, build_id, prerelease_version_validator}}
        };

        // Main loop.
        for (const auto& c : s) {
            auto state = state_machine.at(cstate);
            process_char(c, cstate, pstate, std::get<0>(state), std::get<1>(state), std::get<2>(state));
        }

        // Trigger appropriate hooks in order to process last token, because no state transition was
        // triggered for it.
        if (cstate == ParserState::prerelease) {
            prerelease_hook(prerelease_id);
        } else if (cstate == ParserState::build) {
            build_hook(build_id);
        }

        try {
            return VersionData{ stoi(major), stoi(minor), stoi(patch), prerelease, build };
        } catch (std::invalid_argument& ex) {
            throw ParseError(ex.what());
        }
    }
}}
