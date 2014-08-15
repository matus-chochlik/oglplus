================================
Release notes for version 0.50.0
================================

.. _OGLplus: http://oglplus.org/

Overview
========

This release of `OGLplus`_ several smaller changes to various parts of the library,
some new features like the smart-enum-values or the ``FragData`` class, updated
build system, minor changes to the examples to show the new features and major
updates to the Quickbook-based documentation.

Changes
=======

 - The ``Capability`` enumeration was updated.

 - The implementation of the ``Vector`` class template was refactored and cleaned up.

 - Updates to GPU program variables:

    * Minor changes were made to the ``ProgVar`` class template.
    * The ``FragData`` program variable wrapper for fragment data outputs was added.
    * The ``Set`` member function was removed from ``UniformBlock``.

 - Updates to ``StrCRef``:

    * New constructors for ``std::vector<Char>``, ``std::array<Char>``, etc. were added.
    * Equality comparison operators were added.
    * ``StrCRef`` now replaces the ``StrLit`` C-string literal wrappers.

 - New syntax-sugar operators were added for ``Sampler`` operations.

 - The ``oglplus::Error::Code`` function returning values of ``ErrorCode`` type was added.

 - Updates to the build system:

    * Detection of GL version 4.5 was added.

 - Updates to the Range utilities:

   * The ``Contains`` and ``Has`` functions were added.
   * The ``CountIf`` function was added.

 - The implementation of the 'smart-enumerations' was updated and the 'smart-enum-values' were added.

 - Fixed problems:

    * A bug in the 3D worley cell image generator was fixed.
    * A minor bug was fixed in one of the standalone examples.
    * The missing ``Size`` member function was added to ``StrQueryRange``.

Breaking changes
================

 - The ``StrLit`` class has been completely replaced by ``StrCRef`` and its definition was removed.
 
 - The ``MultiplyBy`` and ``DivideBy`` functions of ``Vector`` were replaced by ``Multiply`` and ``Divide``.
