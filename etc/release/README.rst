================================
Release notes for version 0.65.0
================================

.. _OGLplus: http://oglplus.org/

Overview
========

This release of `OGLplus`_ adds support for multisampling in the GLX and EGL example harnesses, brings minor changes to ``Context`` and ``ClientContext``, bugfixes, updates to the build system and updated Quickbook documentation.

Changes
-------

- The GLX and EGL-based example harnesses were refactored and updated to use multisampling with the specified number of samples when the ``--samples`` option is specified.

- The ``FillRectangle`` value has been added to the ``PolygonMode`` enumeration.

- Most of the examples now use GLSL 120/130/140/150 where possible in order to support GL implementations which don't implement higher GLSL versions (for example Mesa3D).

- The ``ViewportIndex`` and ``DrawBufferIndex`` types were added.

- The ``Context`` and ``ClientContext`` classes were updated to use the new types, additional value checks were added to ``ClientContext``.

- A wrapper for ``NV_fragment_coverage_to_color`` extension has been added.

- The build system was updated to detect the availability of C++ the ``override`` specifier and it was added where appropriate to the source code.

- The Quickbook documentation has been updated.

