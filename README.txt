
 INTRODUCTION TO OGLplus
=========================

OGLplus is a open-source header-only library which implements a thin
object-oriented facade over the OpenGL® (version 3 and higher) C-language API.
It provides wrappers which automate resource and object management and make
the use of OpenGL in C++ safer and easier.



 BUILDING AND INSTALLATION
===========================

 For the impatient:
 ------------------

# linux and similar *nix systems
$> ./configure.sh
# or
$> ./configure.sh --prefix=/path/to/install

$> cd _build
$> make
$> make install

 For the busy:
 -------------

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

 * Builds several additional, automatically generated headers

 * Installs all header files to a directory specified by the install prefix

 * Builds the examples and textures used by the examples (optional)

 * Builds and installs the documentation (optional)


 Requirements
 ------------

 * C++11 compatible compiler.
   Currently supported compilers:
   - g++ (at least version 4.5, 4.6 and higher is recommended)

 * CMake.

 * Doxygen + XSLTproc is required to generate additional header files.
   This is required only if the headers are not pre-built (typically
   when checked out from the repository, packaged releases are shipped with
   pre-built headers)

 * Doxygen is also required to build the documentation.

 * Inkscape is required to convert textures used in examples from SVG to PNG.
   This is required only if the textures are not pre-built (typically
   when checked out from the repository, packaged releases are shipped with
   pre-built textures). Building of the textures is optional, they are not
   necessary when the building of examples is disabled.

 * The GL3/gl3.h header or GLEW. OGLplus does not define the OpenGL symbols
   (types, constants, functions, etc.) itself and therfore applications using
   it need to define them themselves (before including OGLplus). The examples
   currently need GLEW (at least version 1.6) or the GL3/gl3.h header (available
   for download from http://www.opengl.org/registry/api/gl3.h) and a GL binary
   library exporting the OpenGL (3 or higher) functions.
   The build system detects the presence of GLEW or gl3.h and configures
   compilation and linking of the examples accordingly. If both are installed
   and the user does not specify otherwise GLEW is used.

*  libPNG. Some examples and some classes provided by OGLplus use libPNG to load
   PNG files. These are however not required for the general use of OGLplus,
   applications may use other means to load binary image files.


 CMake-based build configuration
 -------------------------------

The CMake script defines and uses several variables to modify the build
configuration, which can be specified on the command-line when invoking
cmake (with the -D option. see cmake manual for details):

 * HEADER_SEARCH_PATHS [<empty>]: (semicolon-separated) list of paths
   to additional directories to search when looking for 3rd-party headers
   like GL/glew.h, GL3/gl3.h, etc.

 * OGLPLUS_WITHOUT_GLEW [Off]: Do not use GLEW even if it is available,
   this requires GL3/gl3.h to be installed.

 * OGLPLUS_NO_EXAMPLES [Off]: Do not build the examples and the textures.

 * OGLPLUS_NO_DOCS [Off]: Do not build and install the documentation.


 User-friendly configuration script
 ----------------------------------

(Currently available only for platforms with bash - 'configure.sh')
The 'configure' script is a more user-friendly way to invoke cmake and specify
additional parameters for the configuration process.

Some of the more important command-line options are described below:

 --prefix PATH: Specifies the installation prefix path for cmake (sets
   the value of the CMAKE_INSTALL_PREFIX variable). If this option is not
   specified, cmake's default prefix is used.

 --include-dir PATH: This options allows to specify additional directiories
   to search when looking for header files. It may be used multiple times
   to specify multiple directories.

 --without-glew: Do not use GLEW even if it is available.

See the --help option for the full description and detailed info on the usage
of this script.


 ACKNOWLEDGEMENTS
==================

Tolga Dalman for helping to get started with CMake.
