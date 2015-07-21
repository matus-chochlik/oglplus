================================
Release notes for version 0.64.0
================================

.. _OGLplus: http://oglplus.org/

Overview
========

This release of `OGLplus`_ brings new overloads of the GPU program build functions, which allow deferred handling of errors, updates in the examples and documentation.

Changes
-------

- The ``DeferredHandler`` and the ``Outcome<T>`` classes, which allow to defer and/or cancel calling of error handlers were added.

- New overloads of ``Shader::Compile``, ``Shader::CompileInclude``, ``Program::Link`` and ``Program::Validate`` and ``ProgramPipeline::Validate``, which return ``Outcome<T>`` instead of handling errors eagerly were added.

- Some of the examples were changes to show the usage of the new features.

- Some of the examples were changed to use GLSL 120/130/140/150 in order to support GL implementations which don't implement higher GLSL versions.


