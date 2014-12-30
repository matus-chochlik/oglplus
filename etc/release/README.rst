================================
Release notes for version 0.56.0
================================

.. _OGLplus: http://oglplus.org/

Overview
========

This release of `OGLplus`_ brings updates to the ``ClientContext`` class, which maintains the GL state and allows to push/pop individual state variables or efficiently query or change their values, adds many new getter/setter functions to ``Context``, updates to GLM interoperability, updates to the Quickbook documentation and in the build system.

Changes
=======
 - The ``oglplus::ClientContext`` class was updated, wrappers for new state variables and functions were added..

 - The ``EnumAssocType`` and ``EnumAssocGLType`` templates and their specializations were added.

 - Many new getter/setter functions were added to ``oglplus::Context``.

 - The Quickbook documentation was updated.

 - Minor changes in the error reporting in the low-profile mode were made.

 - A problem with the wxGL harness on Windows was fixed.

 - The tools for auto-generating of the enumeration headers were updated and the headers were re-generated.

 - Several minor changes were made to the enumerations types.

 - New options were added to the configure.bat script.

 - Detection of support for strongly-typed enum template parameters was added.

