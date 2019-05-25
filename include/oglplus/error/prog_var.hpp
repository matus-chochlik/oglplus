/**
 *  @file oglplus/error/prog_var.hpp
 *  @brief Declaration of OGLplus program-variable-related error
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_ERROR_PROG_VAR_1107121317_HPP
#define OGLPLUS_ERROR_PROG_VAR_1107121317_HPP

#include <oglplus/error/basic.hpp>
#include <oglplus/object/name.hpp>

namespace oglplus {

/// Exception class for GL program-variable-related errors
class ProgVarError : public Error {
private:
#if !OGLPLUS_ERROR_NO_PROG_NAME
    GLuint _prog_name;
#endif
#if !OGLPLUS_ERROR_NO_IDENTIFIER
    String _identifier;
#endif
public:
    ProgVarError(const char* message);

    ProgVarError(const ProgVarError&) = default;
    ProgVarError(ProgVarError&&) = default;

    ~ProgVarError() noexcept {
    }

    ProgVarError& Program(ProgramName program) {
#if !OGLPLUS_ERROR_NO_PROG_NAME
        _prog_name = GetGLName(program);
#endif
        OGLPLUS_FAKE_USE(program);
        return *this;
    }

    /// Returns the program
    ProgramName Program() const;

    ProgVarError& Identifier(StrCRef identifier) {
#if !OGLPLUS_ERROR_NO_IDENTIFIER
        _identifier.assign(identifier.begin(), identifier.end());
#endif
        OGLPLUS_FAKE_USE(identifier);
        return *this;
    }

    const char* ObjectTypeName() const override {
        return "PROGRAM";
    }

    /// Returns the GL program name
    GLint ObjectName() const override {
        return GLint(_prog_name);
    }

    /// Returns the program variable identifer
    const char* Identifier() const override;
};

} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/error/prog_var.ipp>
#endif

#endif // include guard
