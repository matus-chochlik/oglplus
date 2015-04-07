================================
Release notes for version 0.60.0
================================

.. _OGLplus: http://oglplus.org/

Overview
========

This release of `OGLplus`_ brings several minor changes, updates and bugfixes. The Quickbook documentation has also been updated.

Changes
-------

- The ``Boolean`` wrapper class was updated, the ``operator ~`` was added.

- The ``HasInstance`` function was added to the ``Object`` wrapper.

- The native GL context wrappers were updated.

- The DSA ``Texture``, ``Buffer`` and ``Framebuffer`` wrappers were partially refactored and simplified.

- The ``SingleFace`` enumeration was added.

- The ``FragmentData`` and ``FragmentDataSlot`` typedefs were added.

- A new standalone example was added.

- The ``oalplus::CurrentContext`` class was renamed to ``ContextMadeCurrent``.

- Missing ``#ifdefs`` were added around specializations of ``EnumAssocType``.

- The Quickbook documentation was updated.

