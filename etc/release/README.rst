================================
Release notes for version 0.49.0
================================

.. _OGLplus: http://oglplus.org/
.. _ARB_shading_language_include: http://www.opengl.org/registry/specs/ARB/shading_language_include.txt

Overview
========

This release of `OGLplus`_ brings changes to the functions for specifying Buffer
data and sub-data, new types representing buffer data and its size, new classes
for specifying GLSL shader source strings, support for ``#include`` directives
in GLSL, changes in the shape loader/generator framework, several bugfixes,
minor updates to the documentation, etc. 

Changes
=======

 - Buffer data specification

   * The ``BufferSize`` and ``BufferData`` classes used for specifying GPU buffer size and data were added.
   * The ``Buffer::Data``, ``Buffer::SubData`` and some other functions were changed to used the new classes.
   * In case of ``Buffer::SubData`` an interface-breaking change was made -- the offset is now specified in bytes.
   * The ``Buffer::Resize`` function for resizing of a GPU buffer without specifying the data was added.
   * The ``Buffer::RawData`` function for specifying untyped buffer data was added.
   * Similar changes were also made to the ``DSABuffer`` class.

 - Shader source specification

   * The new ``GLSLString`` and ``GLSLStrings`` classes which serve as adapters for specifying GLSL shader source strings were added.
   * The constructors and some member functions of the ``GLSLSource`` class were updated.
   * The ``Shader::Source`` function and the constructors of ``ShaderProgram`` were updated to use the new classes.

 - New functions for building of GPU programs were added

   * The ``Program::Build`` function checks all shaders attached to a ``Program`` and compiles those which are not yet compiled, befor linking the program.

 - Wrapper for the `ARB_shading_language_include`_ extension was added

   * The ``NamedStringType`` enumeration and the ``NamedString`` class were added.
   * The ``Shader::CompileInclude`` and ``Program::BuildInclude`` functions were added which allow to compile shaders with ``#include`` directives.

 - Some of the existing examples were updated to show the usage of the new features.

 - Fixed bugs

   * Negative indices are now supported by the ``ObjMesh`` shape loader.
   * Several problems in the build-system were fixed.
   * Some bugs in the OGLplus examples were fixed.

Breaking changes
================

 - As mentioned above the offset parameter of ``Buffer::SubData`` is now specified in bytes (by using the ``BufferSize`` class) instead of units of the uploaded data type.
