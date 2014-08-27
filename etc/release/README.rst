================================
Release notes for version 0.51.0
================================

.. _OGLplus: http://oglplus.org/

Overview
========

This release of `OGLplus`_ brings experimental support for several OpenGL 4.5
features and new extensions, most notably wrappers for the direct state access
functions, ``ARB_sparse_buffers``, ``ARB_robustness``, ``ARB_pipeline_statistics_query``
and ``ARB_transform_feedback_overflow_query``. The old DSA object wrappers based
on ``EXT_direct_state_access`` were renamed and moved to a new location. The ``Query``
class has also been updated. Detection of GL 4.5 has been added to the build
system and the Quickbook-based documentation has been updated.

Changes
=======

 - The ``ErrorCode`` enumeration was updated, the ``ContextReset`` value was added.

 - The ``QueryTarget`` enumeration was updated, new values from the ``ARB_pipeline_statistics_query`` and ``ARB_transform_feedback_overflow_query`` extensions were added.

 - The ``LimitQuery`` enumeration was updated.

 - The ``ContextReleaseBehavior``, ``ResetNotificationStrategy`` and ``GraphicsResetStatus`` enumerations from the ``ARB_robustness`` extensions were added.

 - The old DSA wrappers based on ``EXT_direct_state_access`` were renamed.

 - New wrappers for the ``ARB_direct_state_access`` object DSA functions were added.

 - The ``Query`` class was updated:
   
   * The ``ConditionalRenderMode`` enumeration was added.
   * The ``BeginConditionalRender`` and ``EndConditionalRender`` functions were added.
   * The ``ConditionalRender`` class was added.


Breaking changes
================

 - The old DSA object wrappers based on ``EXT_direct_state_access`` which were previously implemented in the ``./oglplus/dsa/*.hpp`` files were moved to the ``./oglplus/dsa/ext/`` subdirectory and renamed from ``DSA{Object}`` to ``DSA{Object}EXT``. The files implementing the new DSA object wrappers are now located in ``./oglplus/dsa/`` but the wrappers have a different interface.
 
