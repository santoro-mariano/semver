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

#ifndef VERSIONING_PARSER_H
#define VERSIONING_PARSER_H

#include <map>
#include <functional>
#include <versioning/version_parser.h>

namespace versioning {
    namespace semver {
        namespace v200 {
            using Validator = std::function<void(const std::string&, const char)>;
            using State_transition_hook = std::function<void(std::string&)>;
            /// State transition is described by a character that triggers it, a state to transition to and
            /// optional hook to be invoked on transition.
            enum class ParserState {
                major, minor, patch, prerelease, build
            };
            using Transition = std::tuple<const char, ParserState, State_transition_hook>;
            using Transitions = std::vector<Transition>;
            using State = std::tuple<Transitions, std::string&, Validator>;
            using State_machine = std::map<ParserState, State>;

            class Parser: public VersionParser {
            public:
                VersionData Parse(const std::string &s) const;

            private:

                // Ranges of characters allowed in prerelease and build identifiers.
                const static std::vector<std::pair<char, char>> allowed_prerel_id_chars;

                inline Transition mkx(const char c, ParserState p, State_transition_hook pth) const;

                /// Advance parser state machine by a single step.
                /**
                Perform single step of parser state machine: if character matches one from transition tables -
                trigger transition to next state; otherwise, validate if current token is in legal state
                (throw Parse_error if not) and then add character to current token; State transition includes
                preparing various vars for next state and invoking state transition hook (if specified) which is
                where whole tokens are validated.
                */
                inline void process_char(const char c, ParserState& cstate, ParserState& pstate,
                                          const Transitions& transitions, std::string& target, Validator validate) const;

                /// Validate normal (major, minor, patch) version components.
                inline static void normal_version_validator(const std::string& tgt, const char c);

                /// Validate that prerelease and build version identifiers are comprised of allowed chars only.
                inline static void prerelease_version_validator(const std::string&, const char c);

                /// Validate every individual prerelease identifier, determine it's type and add it to collection.
                inline bool is_identifier_numeric(const std::string& id) const;

                inline bool check_for_leading_0(const std::string& str) const;

                /// Validate every individual prerelease identifier, determine it's type and add it to collection.
                void prerelease_hook_impl(std::string& id, Prerelease_identifiers& prerelease) const;

                /// Validate every individual build identifier and add it to collection.
                void build_hook_impl(std::string& id, ParserState& pstate, Build_identifiers& build,
                                     std::string& prerelease_id, Prerelease_identifiers& prerelease) const;
            };
        }
    }
}

#endif //VERSIONING_PARSER_H
