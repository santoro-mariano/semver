//
// Created by mariano on 11/19/17.
//

#ifndef VERSIONING_EXCEPTIONS_H
#define VERSIONING_EXCEPTIONS_H

#include <stdexcept>

namespace versioning {
    /// Any error in parsing or validation of version string will result in Parse_error exception being thrown.
    class ParseError : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };

    /// Any error in manipulating version data will result in Modification_error exception being thrown.
    class ModificationError : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };
}

#endif //VERSIONING_EXCEPTIONS_H
