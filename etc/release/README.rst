================================
Release notes for version 0.47.0
================================

.. _OGLplus: http://oglplus.org/

Overview
========

This version of `OGLplus`_ finishes the overhaul from the previous release,
but also brings some new features and examples. Similar changes that were
made to OGLplus were now made to OALplus and EGLplus.

Changes
=======

* The ``ObjectName``, ``Sequence``, ``Array``, ``Reference`` and ``Object``
  classes and related functionality were further refactored and reused in OpenAL.

* The ``Group`` class and related functionality was added.

* The OALplus AL function wrapper macros were reimplemented.

* The ``HardwiredProgram`` template class that was deprecated in the previous
  release was removed.

* The ``QuickProgram`` template class was reimplemented and its interface
  changed slightly.

* Support for GLM vector and matrix uniforms was re-added, typechecking
  of GLM uniforms was added.

* Changes to exceptions:
  * The Value and Limit virtual member functions were added to oglplus::Error.
  * The common error handling in the oglplus examples was updated.

* The implementation of some functions was moved to the ``implement/`` directory.

* Changes to OGLplus examples:
  * Two new examples were added, one showing simple SSAO implementation
    and the other a voronoi cell shader.
  * One of the older examples was removed.
  * The example showing GLM interoperability was re-added.

* The Voronoi/Worley cell image generators were added.

* Changes to the build system and compile-time configuration:
  * Detection for the ``KHR_debug`` OpenGL extension was added
    to the build system.
  * The compile-time configuration-related headers were split into several
    separate files.
  * The ``BOOST_NO_CXX11_*`` macros were added to the now deprecated
    ``BOOST_NO_*`` macros.

Known issues
============

* As with the previous release still no support for MSVC 2010.
* The doxygen documentation is incomplete.


