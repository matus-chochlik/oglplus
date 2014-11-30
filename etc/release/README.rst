================================
Release notes for version 0.54.0
================================

.. _OGLplus: http://oglplus.org/

Overview
========

This is mostly a bugfix release of `OGLplus`_, but it also brings updates to the quickbook documentation, minor updates to the build system, refactoring in the transform feedback helper classes and backporting to platforms not supporting primitive restart indices.

Changes
=======
 - The ``TransformFeedback::Activator`` and ``TranformFeedback::Pauser`` classes were reimplemented at the namespace level.

 - A new overload of ``Context::ClearColor`` was added.

 - A bug in multiplication of Matrix by a scalar was fixed.

 - The shape builders were updated to work on platforms not supporting GL primitive restart.

 - Some MSVC and Clang++ warnings were removed.

 - The C++ strongly typed enumerations are now a required feature.

 - The Quickbook documentation was updated.

