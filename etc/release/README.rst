================================
Release notes for version 0.46.0
================================

.. contents::

.. _OGLplus: http://oglplus.org/

Overview
========

This version of `OGLplus`_ brings a major reimplementation of several key parts,
listed and described below. Generally the changes were made to fix errors in the
initial design which became obvious in the past few years of use and development
of OGLplus. Unfortunately some of these changes break the previous interfaces.
Some of such cases are listed below together with porting instructions.

Changes
=======

The the individual subsystems which were changed are listed and the reasons
for the updates are described here, including the description of how things
were changed.

Error reporting and handling
----------------------------

Previously, the error reporting from the library side was mostly handled
by a set of macros, which internally checked if an error occured in the previous
GL (or AL, or EGL) function call and allowed to specify some information about
the error.  The number of parameters was fixed which in some cases prevented
to pass some useful information about the error to the thrown exception and
in other cases where the required info was not available it had to be replaced
with nil values.
The information common to all exception types was stored in the ``ErrorInfo``
class and this class was passed to the concrete exception class in its constructor.

The ``Error`` class also had ``properties``; a map of string key and value pairs
that could be added to the exception to provide info which did not fit into
the members of ``Error`` and ``ErrorInfo``. These were however only used for two
things: storing the identifier of an uniform and the GPU program description in
GLSL uniform-related errors.

There are also a few places in the code where another conditions besides
``glGetError() != GL_NO_ERROR`` raises an error and these were handled
in a different way.

From the library user's point of view it was in some situations unnecessarily
complicated to get to the information about the error that occured. The basic
``Error`` exception class provided only limited information and if more info
was necessary (for example the GLSL build log) a derived exception had to be
caught even if the error handling consisted only of printing the error message
and exiting the program.

These problems were solved by the following:

All error reporting is now consistently handled by the ``OGLPLUS_HANDLE_ERROR_IF``
macro and several facade macros simplifying its use. However the information
about the error are not passed through the constructor, but each piece can
be added individually by a set of member functions in ``Error`` and the derived
exception classes. This way all the information that is available at a particular
point in the code can be stored in the exception.

The ``Error`` class now contains all information that was previously stored
in ``ErrorInfo`` and several virtual functions returning additional information
were added. In the basic ``Error`` these functions return nil default values
and are overriden in derived exceptions to return the actual build log in case
of a ``ProgramBuildError``, the object GL name and textual description in case
of ``ObjectError``, etc.

This way applications that just want to print all available information about
the error need to catch just the ``Error`` class. If a more elaborate or specific
error handling is needed the derived exceptions still can be caught and handled.

The exception hierarchy was also updated and new exception classes like
the ``ProgVarError`` or ``ObjectPairError`` were added.

The error handling still can be customized, but in a different way than before.
The ``OGLPLUS_HANDLE_ERROR_IF`` macro now fills-in the ``Error`` exception class
or one of its more suitable descendants and calls the ``oglplus::HandleError(ErrorType)``
template function. This function by default just throws the error class passed
as its only argument, but it can be overloaded by the user to do something else.

Similar changes were also made to the OpenAL and EGL error handling.

The object wrappers
-------------------

Previously all wrappers of GL (and AL) named objects were derived from
the ``Named`` class which stored the ``GLuint`` (or ``ALuint``) object name.
This class however did not distinguish between names of objects of different
types. This was only handled by the derived classes.

Also, all operations on objects of a particular type (like ``Texture`` or ``Buffer``)
were handled by the ``*Ops`` class (``TextureOps`` or ``BufferOps``). There are however
several distinct groups of functions that serve the same purpose. Like the ``glGet*``,
``glDelete*`` or ``glBind*`` functions.
The ``Object`` and its modifiers like ``Optional``, ``Managed`` or ``Array`` templates
were then used to wrap the ``*Ops`` class and provide lifetime management, optional
initialization, managed references, etc.

All this however, did not scale very well and for the direct-state-access (DSA) wrappers
a lot code had to be duplicated. Also the DSA and non-DSA object wrappers did not
play together very well.

In the current release the following changes were made:

Several tag types in the ``oglplus::tag`` namespace, like ``tag::Texture``,
``tag::Program``, ``tag::Shader`` or ``tag::VertexAttrib``, ``tag::Uniform``, etc.
were added to distinguish between different GL objects or GPU program variable kinds.

The ``Named`` class was replaced by the ``ObjectName<Tag>`` template, which still
just stores the ``GLuint`` object name, but the ``Tag`` template parameter now
distinguishes between various GL object types and does not allow them to be
interchanged by mistake. This also allows to avoid having different function overloads
for DSA and non-DSA object wrappers. All OGLplus functions wrapping GL functions
requiring a GL object name now take ``ObjectName<Tag>`` as arguments instead
of the ``*Ops`` or ``DSA*Ops`` classes.

The ``Sequence<ObjectName<Tag>>`` template class was added to represent various
sequences of object names.

The object-related operations which were previously wrapped by the ``*Ops`` classes
are now split into several templates:

* ``ObjGenDelOps<Tag>`` wraps the ``glGen*``, ``glDelete*`` and ``glIs*`` functions
  for objects of different types (also distinguished by the ``Tag`` template parameter).

* ``ObjBindingOps<Tag>`` wraps the object binding and current binding-query operations.

* ``ObjCommonOps<Tag>`` wraps other common object operations.

* ``ObjZeroOps<OpsTag, ObjTag>`` wraps operations that are applicable to object with name
  zero (0), like the default texture, default framebuffer, etc. The ``OpsTag`` parameter
  distinguishes for example between the non-DSA and DSA function wrappers.

* ``ObjectOps<OpsTag, ObjTag>`` wraps operations applicable to named GL objects.

This way the type of the template also conveys information about the GL type that
is wrapped and also about the kind of operations (non-DSA vs DSA, etc.)

The ``Object`` template was updated accordingly as were the ``Array`` and ``Optional``
modifiers. The ``Managed<Object>`` template was replaced by the ``Reference<Object>``
template, which serves the same purpose.
Typedefs like ``Texture``, ``Framebuffer``, ``Renderbuffer``, etc. for the non-DSA
object wrappers or ``DSATexture``, ``DSAFramebuffer``, ``DSARenderbuffer``, etc.
for the DSA wrappers are defined.

Similar changes were also made to the OpenAL object wrappers.

The GPU program variable wrappers
---------------------------------

In a similar fashion to the object wrappers, the GPU program variable wrappers
(uniforms, uniform blocks, subroutines, vertex attributes, etc.) were also changed.
The ``ProgVarLoc<Tag>`` template now wraps the name of the program object and the
location of the program variable of the kind specified by the ``Tag`` template parameter.

The operations were also split into several templates:

* ``ProgVarLocOps<Tag>`` wraps operations related to getting the location of the
  program variable of the type specified by ``Tag``.

* ``ProgVarTypeOps<Tag>`` wraps type-related operations where applicable.

* ``ProgVarCommonOps<Tag>`` wraps common operations.

* ``ProgVarSetSetOps<OpsTag, VarTag, T>`` currently handle the assignment of value of
  the program variable where applicable.

Finally the ``ProgVar`` template (and in some cases its descendants) are used to
define the ``Uniform``, ``ProgramUniform``, ``UniformBlock``, etc. types used
by the library users.

One other notable change in program variable wrappers is the initialization.
Previously the default uniforms, etc. could not be constructed uninitialized.
If an identifier of an inactive program variable was passed to the constructor
then an exception was raised. Now the ``ProgVar`` types have multiple different
constructors which allow construction from different parameters and ``ProgVar``
also supports late initialization.

The ``Lazy(Program)Uniform`` and ``Optional(Program)Uniform``, etc. classes
that previously provided lazy and optional initialization are now replaced by
the ``Lazy<ProgVar>`` and ``Optional<ProgVar>`` modifiers, so for example instead
of ``LazyProgramUniform`` the ``Lazy<ProgramUniform>`` type should be used.

Controlled access to private members
------------------------------------

Previously the ``FriendOf`` template was used to provide access to certain private
members of OGLplus, OALplus and EGLplus classes (for example the GL or AL object
names, GPU buffer or texture handles, etc.).
The usage of ``FriendOf`` was unnecassarily complicated and it was replaced by
the ``GetGLName``, ``GetALName``, ``GetEGLHandle``, etc. functions, which are more
convenient to use.

Changes to the directory hierarchy
----------------------------------

The source directory hierarchy was reorganized and related files were grouped
into subdirectories.

General changes in all libraries:

* the error-related things were put into the ``error/`` subdirectories.

* the ``auxiliary/`` directory was renamed to ``detail/``.

In ``oglplus/`` the following changes were made:

* the math utilities and classes like ``Vector``, ``Matrix``, ``Angle``, etc.
  were put into the ``math/`` subdirectory,

* the string-related things are in the ``string/`` subdirectory,

* the object wrappers were put into ``object/``,

* the GPU program variable wrappers are now in ``prog_var/``,

* the direct-state-access object wrappers are in the ``dsa/`` subdirectory.

In ``oalplus/`` the following has changed:

* the math utilities and classes are now in the ``math/`` subdirectory,

* the object-related things were put into ``object/``.

Known issues
============

In order to avoid having a too long period between releases, some less important
things were left to be finished in the next releases:

* The ``Optional`` and ``Array`` wrappers for OALplus objects are temporarily disabled.

* The GLM vector and matrix adaptors are temporarily disabled.

* Support for MSVC 2010: This release is known not to work with MSVC 2010.
  This compiler lacks proper support for most of the required C++11 features
  and a part of the clutter removed from the source in this release were various
  workarounds for MSVC10. We are still considering if the support for this compiler
  should be dropped or re-implemented in the next release.

* The documentation is still incomplete. We are considering some alternatives to doxygen.

Deprecated classes and functions
================================

* The ``HardwiredProgram`` template is deprecated and will be removed in one
  of the upcoming releases.

* The ``QuickProgram`` template will be either removed or reimplemented in
  the following releases.
