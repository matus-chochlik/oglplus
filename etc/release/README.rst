================================
Release notes for version 0.48.0
================================

.. _OGLplus: http://oglplus.org/

Overview
========

This release of `OGLplus`_ brings some changes to oglplus, oalplus and
eglplus exception classes, updates in the BezierCurves class, new wrappers
for GL extensions, refactored oalplus::Device class, updated docs, etc.
Several bugs were fixed and one of the older examples was removed.

Changes
=======

 - Changes to ``oglplus::Error``

   * ``Error::GLLib`` function was added.
   * ``Error::GLFuncName`` function was renamed to ``GLFunc``.

 - Changes to ``oalplus::Error``

   * ``Error::ALLibName`` function was renamed to ``ALLib``.
   * ``Error::ALFuncName`` function was renamed to ``ALFunc``.

 - Changes to ``oalplus::ALCError``

   * ``ALCError::Device`` function was added.

 - Changes to ``eglplus::Error``

   * ``Error::EGLFuncName`` function was renamed to ``EGLFunc``.

 - Changes to ``oalplus::Device``

   * The capture functionality was refactored into the separate ``CaptureDevice`` class.
   * The ``Specifier``, ``CaptureSpecifier`` and ``Extensions`` functions were added.

 - Changes to ``oglplus::BezierCurves``

   * New constructors were added.
   * Support for non-connected sequences of bezier curve segments was added.
   * The ``Derivative`` function was added.

 - New wrappers for GL extensions

   * ``GL_ARB_copy_image``
   * ``GLX_NV_copy_image``
   * ``GL_NV_copy_image``

 - Fixed bugs

   * Fixed problems with support of Pango/Cairo in build system and sources.
   * Added an ``#ifdef`` to Texture fixing problems with older versions of GL API headers.

 - Moved the auto-generated configuration files:

   * ``oglplus/fix_gl_version.hpp`` to ``oglplus/config/fix_gl_version.hpp``
   * ``oglplus/site_config.hpp`` to ``oglplus/config/site.hpp``

 - Quickbook-based documentation was started.

Known issues
============

* Only partial support for MSVC 2010. Support for this compiler will be dropped in the next release.
* The doxygen documentation is incomplete.


