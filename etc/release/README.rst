================================
Release notes for version 0.57.0
================================

.. _OGLplus: http://oglplus.org/

Overview
========

This is mostly a bugfix release of `OGLPLUS`_, but it also brings changes in the setting stack functionality of ``ClientContext``, updates in the enumeration definitions and updated Quickbook docs.

Changes
=======
 - The ``oglplus::ClientContext`` class was updated, the setting stack was reimplemented not to use dynamically allocated containers to store the pushed values.

 - The script for auto-generating of the enumeration headers was updated, now almost everything related to the enumerations is automatically generated.

 - A bug in the definition of the overloads of ``EnumValueRange`` was fixed.
 
 - Minor problems in the GLSL shaders in the examples were fixed.

 - The Quickbook documentation was updated.

 - Noexcept specifiers were added to some functions.


