================================
Release notes for version 0.53.0
================================

.. _OGLplus: http://oglplus.org/

Overview
========

This is mostly a bugfix release of `OGLplus`_, but it also brings updates to the GL version detection in the build system, minor updates to ``ObjHandle`` and updated documentation.

Changes
=======

 - The GL version detection algorithm now also checks for the presence of (nearly) all required GL constants.

 - A bug in the setting array of ``Vector<T,N>`` uniform values was fixed.

 - An unused constructor was removed from ``ObjHandle``.

 - The Quickbook documentation was updated.

