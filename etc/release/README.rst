=============
Release notes
=============

Version 0.45.0
--------------

* The new object Binding interface introduced in the previous release was updated
  and the ``DefaultTexture``, ``NoBuffer``, ``NoVertexArray``, ``NoRenderbuffer``,
  ``NoProgram``, ``NoProgramPipeline`` and ``NoSampler`` classes were added. These
  classes together with the existing ``DefaultTransformFeedback`` and
  ``DefaultFramebuffer`` can be used to bind the default object (in case of the
  ``DefaultXXX`` classes or break the current binding in case of the ``NoXXX``
  classes).

* The ``Context::Direct(object)`` function was added, which returns the direct
  state access wrapper for the specified ``object`` (if ``EXT_direct_state_access``
  is available). Such wrapper allows to manipulate objects like ``Texture`` or
  ``Buffer`` without binding them first to a binding point. In order for this
  to work the ``include/oglplus/XXX_dsa.hpp`` headers must be included.

* The ``ExposeGLName(object)`` function replacing the ``Expose(object).Name()``
  expression which was removed in the previous release was added.

* The ``BeginPoints``, ``BeginLines``, ``BeginTriangles`` convenience functions
  were added to ``TransformFeedback``.

* The ``images::SortNWMap`` image generator was added. This generator generates
  an 2D image encoding a bitonic sorting network that can be used to perform
  parallel sorting on the GPU. A new example showing the usage of the sorting
  network, used for Z-sorting of particles was added.

* New wrappers for the ``NV_shader_buffer_load`` and ``NV_texture_barrier``
  GL extensions were added.

* The existing wrappers for ``EXT_direct_state_access`` and ``ARB_robustness``
  were updated. ``The DSABufferEXT::TypedMap`` nested class was refactored into
  the ``DSABufferRawMapEXT`` and ``DSABufferTypedMapEXT`` classes similar to the
  existing ``BufferRawMap`` and ``BufferTypedMap`` classes. In ``ARB_robustness``
  new enumerations and functions were added.

* The ``oglplus::native`` namespace containing wrappers for native (GLX and WGL)
  GL contexts and drawing surfaces was added. These will be later used in wrappers
  for extensions like ``NV_copy_image``, etc.

* Sources and cmake scripts for building the OGLplus, OALplus and EGLplus link
  libraries were added to the ``source/lib`` directory. These are still
  work-in-progress, but are already usable. OGLplus, OALplus and EGLplus are
  still header-only, but linking with the binary libraries and defining
  the ``XXX_LINK_LIBRARY`` preprocessor symbols when compiling can be used
  to improve the build times of larger applications.

