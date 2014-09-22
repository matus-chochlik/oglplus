================================
Release notes for version 0.52.0
================================

.. _OGLplus: http://oglplus.org/

Overview
========

This is mostly a bugfix release of `OGLplus`_, but it also brings wrappers for ``KHR_blend_equation_advanced``, new non-throwing constructor in ``ProgVar``, the ``ObjHandle`` template and documentation updates.

Changes
=======

 - Runtime bugs in the bitmap-glyph-based text rendering utilities were fixed.

 - Regressions in the GLES v3 and Android support were fixed.

 - The ``Object`` template was refactored and ``ObjHandle`` was added.

 - The ``OutputData`` class was added and is used in ``Texture`` operations.

 - The ``BlendEquationAdvanced`` enumeration was added and blending-related ``Context`` functions were updated to use it. The ``BlendBarrier`` function was also added.

 - The Quickbook documentation was updated.

