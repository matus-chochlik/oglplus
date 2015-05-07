================================
Release notes for version 0.61.0
================================

.. _OGLplus: http://oglplus.org/

Overview
========

This release of `OGLplus`_ brings updates to GL version detection and other minor changes in the build system, error code enumerations and updated exceptions in OALplus, wrappers for GL ARB_clip_control, updated Quickbook documentation.

Changes
-------

- The ``SizeType`` and ``BigSizeType`` classes were added and some occurences of ``GLsizei`` and ``GLsizeiptr`` were replaced.

- Wrappers for the ``ARB_clip_control`` extension were added.

- The ``ALErrorCode``, ``ALCErrorCode`` and ``ALUTErrorCode`` enumerations were added to OALplus.

- The ``ErrorAL`` exception class was added to OALplus.

- The GL version detection in the build system and the GLUT example harness were updated.

- Some compiler warnings were silenced.

- The Quickbook documentation was updated.

