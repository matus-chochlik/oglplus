/*
 *  Copyright 2014-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_program_resource

class ProgramResource {
public:
    GLint GetIntParam(__ProgramResourceProperty property) const;      /*<
         Gets the value of a single property (as a GLint).
         See [glfunc GetProgramResource].
         >*/
    __Boolean GetBoolParam(__ProgramResourceProperty property) const; /*<
    Gets the value of a single property (as a boolean value).
    >*/

    bool Has(__ProgramResourceProperty property) const; /*<
    Checks if this resource has the specified property.
    >*/

    __ProgramInterface Interface() const; /*<
    Returns the interface of the resource.
    >*/

    const __String& Name() const; /*<
    Returns the name of the resource.
    See [glfunc GetProgramResourceName].
    >*/

    GLuint Index() const; /*<
    Returns the index of the resource.
    >*/

    bool HasType() const; /*<
    Returns true if the resource has a type.
    >*/

    __SLDataType Type() const; /*<
    Returns the data type of the resource (if applicable).
    See [glfunc GetProgramResource], [glconst TYPE].
    >*/

    GLint Location() const; /*<
    Returns the program resource location (if applicable).
    See [glfunc GetProgramResource], [glconst LOCATION].
    >*/

    GLint LocationIndex() const; /*<
    Returns the program resource location index (if applicable).
    See [glfunc GetProgramResource], [glconst LOCATION_INDEX].
    >*/

    GLint ArraySize() const; /*<
    Returns the array size of the resource (if applicable).
    See [glfunc GetProgramResource], [glconst ARRAY_SIZE].
    >*/

    Boolean IsPerPatch() const; /*<
    Returns true if the resource is per-patch (if applicable).
    See [glfunc GetProgramResource], [glconst IS_PER_PATCH].
    >*/

    Boolean ReferencedBy(__ShaderType shader_type) const; /*<
    Returns true if the resource is referenced by shader
    of the specified type (if applicable).
    >*/
};

//]
