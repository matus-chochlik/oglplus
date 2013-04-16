==============
OGLplus README
==============

:Author: Matúš Chochlík <chochlik@gmail.com>

.. contents::

.. _OpenGL: http://opengl.org/
.. _OGLplus: http://oglplus.org/
.. _CMake: http://www.cmake.org/
.. _Doxygen: http://www.doxygen.org/
.. _Inkscape: http://inkscape.org/
.. _libPNG: http://www.libpng.org/
.. _GLEW: http://glew.sourceforge.net/
.. _GLFW: http://www.glfw.org/
.. _FreeGLUT: http://freeglut.sourceforge.net/
.. _SDL: www.libsdl.org/
.. _wxGL: www.wxwidgets.org/

Introduction to OGLplus
=======================

`OGLplus`_ is a open-source header-only library which implements a thin
object-oriented facade over the `OpenGL`_  (version 3 and higher) C-language API.
It provides wrappers which automate resource and object management and make
the use of OpenGL in C++ safer and easier.



Building and Installation
=========================

For the impatient:
------------------

::

 # linux and similar *nix systems
 $> ./configure.sh
 # or
 $> ./configure.sh --prefix=/path/to/install

 $> cd _build
 $> make
 $> make install

 # windows
 $> .\configure.bat
 # open the generated MSVC solution in the _build directory
 # or use some variant of make if available

 # On platforms with python
 $> python configure.py --build

For the busy:
-------------

::

 # linux and similar *nix systems
 $> ./configure.sh [--prefix=/path/to/install] [--no-docs] --no-examples --build-and-install

Overview
--------

OGLplus uses a CMake-based build/configuration system. The library itself
is header only, which means that applications using it do not need to link
to a compiled library, but need just to include the header files.

The build system handles several important tasks:

 * Detects if the necessary things are installed and makes a site-configuration
   header file

 * Detects the support for several C++11 features and builds a config header

 * Builds several additional, automatically generated headers

 * Installs all header files to a directory specified by the install prefix

 * Builds the examples and textures used by the examples (optional)

 * Builds and installs the documentation (optional)


Requirements
------------

 - Compiler supporting required C++11 features [#req_cxx11_feats]_.
   Currently supported compilers:

   * ``g++`` (at least version 4.5, 4.6 and higher is recommended)

   * ``clang++`` (at least version 3.0) - possibly with some limitations
     due to the lack of support for some C++11 features

   * ``MSVC 2010`` - with some limitations due to the lack of support for
     some C++11 features

   * ``MSVC 2012`` - with some limitations due to the lack of support for
     some C++11 features


 - `CMake`_ (required)

 - `Doxygen`_ (optional) is required to build the documentation. This can be disabled
   with the ``--no-docs`` command line option of the ``configure`` script (see below).

 - `Inkscape`_ (optional) is used to convert textures for the examples from SVG to PNG.
   This is required only if the textures are not pre-built (typically
   when checked out from the repository, packaged releases are shipped with
   pre-built textures). Building of the textures is optional, they are not
   necessary when the building of examples is disabled.

 - A libary defining the OpenGL API (required) -- the ``GL/glcorearb.h`` or ``GL3/gl3.h``
   headers or `GLEW`_ .  OGLplus does not define the OpenGL symbols
   (types, constants, functions, etc.), therfore applications using
   it need to define them themselves (before including OGLplus). The examples
   currently need GLEW (at least version 1.9) or the ``GL/glcorearb.h`` header
   (available for download from www.opengl.org/registry/api/glcorearb.h) and
   a GL binary library exporting the OpenGL (3 or higher) functions.
   The build system detects the presence of GLEW or ``GL/glcorearb.h`` and configures
   compilation and linking of the examples accordingly.
   The library to be used can be explicitly specified with the ``--use-gl-header-lib``
   option of the ``configure`` script (see below).

 - A library initializing the default rendering context (required) -- Currently 
   the examples can be built if at least one of the following libraries is
   installed on the system: X11+GLX, `FreeGLUT`_, `GLFW`_, `SDL`_ or `wxGL`_.
   The build system detects the presence these libraries and configures
   compilation and linking of the examples accordingly.
   The library to be used can be explicitly specified with the ``--use-gl-header-lib``
   option of the ``configure`` script (see below).
   

 - `libPNG`_ (optional) -- Some examples and some classes provided by OGLplus use libPNG to load
   PNG files. These are however not required for the general use of OGLplus,
   applications may use other means to load binary image files. The build system
   tries to detect the availability of libPNG and if not found the examples
   using it are not built.


On Linux distributions with the ``apt`` package manager, the following should
be enough to install the most of the dependencies:

::

 sudo apt-get install doxygen cmake g++ libglew1.9-dev freeglut3-dev libpng12-dev


Of course other combinations of the 'GL-API' and 'GL-Context' libraries
are supported and may be used as explained above.


CMake-based build configuration
-------------------------------

The CMake script defines and uses several variables to modify the build
configuration, which can be specified on the command-line when invoking
cmake (with the -D option. see cmake manual for details):

 * ``HEADER_SEARCH_PATHS`` *<empty>*: (semicolon-separated) list of paths
   to additional directories to search when looking for 3rd-party headers
   like GL/glew.h, GL3/gl3.h, etc.

 * ``LIBRARY_SEARCH_PATHS`` *<empty>*: (semicolon-separated) list of paths
   to additional directories to search when looking for 3rd-party compiled
   libraries like GL, GLEW, GL3W, GLFW, glut, png, etc.

 * ``OGLPLUS_NO_EXAMPLES`` *Off*: Do not build the examples and the textures.

 * ``OGLPLUS_NO_DOCS`` *Off*: Do not build and install the documentation.


User-friendly configuration script
----------------------------------

The configuration script comes in three flawors:

1. ``configure.sh`` -- For platforms with bash.
2. ``configure.bat`` -- For windows.
3. ``configure.py`` -- For platforms with python (recommended).
                       This version of the script is the most portable
                       and supports most features.

The ``configure`` script is a more user-friendly way to invoke cmake and to specify
additional parameters for the configuration process.

Some of the more important command-line options are described below:

--help  Display the help screen.

--prefix PATH       Specifies the installation prefix path for cmake (sets
                    the value of the CMAKE_INSTALL_PREFIX variable).
                    If this option is not specified, cmake's default prefix is used.

--include-dir PATH    This options allows to specify additional directiories
                      to search when looking for header files. It may be used multiple
                      times to specify multiple directories.

--library-dir PATH    This options allows to specify additional directiories
                      to search when looking for compiled libraries. It may be used
                      multiple times to specify multiple directories.

--no-docs  Do not build the documentation.

See the ``--help`` option for the full description and detailed info on the usage
of this script. Bash users can also do ``source config/configure.bash_complete``
to install a bash completion extension that allows to TAB-complete the command
line arguments for the ``configure-oglplus`` configuration script that invokes
``configure.py``.


Other build environments
========================

Microsoft Visual Studio 2010 and 2012
----------------------------------------------

OGLplus contains two solution files and a set of project files for building
some of the examples in MSVC 2010 and 2012.
The solutions are located at the following paths:

- ``$(OGLplusRoot)/etc/msvc10/OGLplus/OGLplus.sln``
- ``$(OGLplusRoot)/etc/msvc11/OGLplus/OGLplus.sln``

To build properly, it requires GLEW (1.9 or higher) and FreeGLUT libraries
to be installed and added to the list of header/library search paths
in the solution. This can be achieved by setting the following variables
visible to MSVC:

* ``OGLPLUS_DEP_INCLUDE_DIRS`` - list of (semicolon-separated) paths pointing
  to the directories where GLUT's and GLEW's header files are located.

* ``OGLPLUS_DEP_LIBRARY_DIRS`` - list of (semicolon-separated) paths pointing
  to the directories where GLUT's and GLEW's .lib files are located.

* ``OGLPLUS_DEP_LIBS`` - list of (semicolon-separated) .lib files to be linked
  to the examples. Typically ``glew32.lib;freeglut.lib`` for dynamic linking
  or ``glew32s.lib;freeglut_static.lib`` for static linking.

* ``OGLPLUS_PP_DEFS`` - list of (semicolon-separated) preprocessor symbols
  that should be defined. Typically ``GLEW_STATIC;FREEGLUT_STATIC`` are
  required for static linking of GLEW and FreeGLUT.

These variables can be set either as system or user environment variables
or the ``OGLplus-site.props`` property sheet file (located in the solution's
directory) can be used. Either edit the file in a text editor or use MSVC's
*Property Manager* and set the variables listed above as appropriate
on your system. Note, that the ``OGLplus-site.props`` file already
defines variables like the above, but with appended underscore
(for example ``OGLPLUS_DEP_INCLUDE_DIRS_``, etc.). To set the variables
you can open the file in a text editor, remove the underscores and set
the values to match your system configuration.

Also note that when building the examples via the MSVC solutions
the ``$(OGLplusRoot)/_prebuilt/`` directory is required. This directory
contains automatically generated textures and other files that are
not in the source repository. This directory is included in the release
packages. If you are building from sources from the Git repository
also download a recent package and copy the ``_prebuilt/`` directory
into to the directory where you have cloned the repo or use the cmake
build system and build them that way.



Acknowledgements
================

- *Tolga Dalman* for helping to get started with CMake.
- *Timo Keller* for contributing one of the examples.
- *Denis Ovod* for constructive critique and suggestions.
- *Per Nordlöw* for useful suggestions.


.. [#req_cxx11_feats] OGLplus requires the following C++11 features:
   The ``type_traits`` and ``tuple`` librares, variadic preprocessor macros, r-value
   references and move-constructors.
   OGLplus also uses (but has workarounds for or disables certain components
   and/or functions if the features are not available):
   Strongly typed enumerations, variadic templates, initializer lists, lambdas,
   defaulted and deleted functions, function template default arguments,
   constexpr, noexcept, nullptr, explicit conversion operators.

