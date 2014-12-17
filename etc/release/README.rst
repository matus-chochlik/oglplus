================================
Release notes for version 0.55.0
================================

.. _OGLplus: http://oglplus.org/

Overview
========

This release of `OGLplus`_ adds the ``ClientContext`` class, which maintains (at the moment only partially) the GL state and allows to push/pop individual state variables or efficiently query or change their values and also brings updated quickbook docs, backporting for platforms not supporting primitive restart indices and several bugfixes.

Changes
=======
 - The ``oglplus::ClientContext`` class was added.

 - The ``EnumToClass`` template and its specializations were added.

 - A new getter/setter functions were added to ``oglplus::Context``.

 - A bug in ``Texture::Active`` was fixed.

 - Some of the shape builders were ported to platforms not supporting GL primitive restart.

 - The Quickbook documentation was updated.

 - Minor changes were made in the compiler configuration header.

 - One of the examples was updated to show the new features.

