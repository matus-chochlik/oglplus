/**
 *  @file oglplus/ext/NV_path_rendering.hpp
 *  @brief Wrapper for the NV_path_rendering extension
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_EXT_NV_PATH_RENDERING_1203031902_HPP
#define OGLPLUS_EXT_NV_PATH_RENDERING_1203031902_HPP

#include <oglplus/extension.hpp>
#include <oglplus/object.hpp>

namespace oglplus {

#if OGLPLUS_DOCUMENTNVON_ONLY || GL_NV_path_rendering

class PathNVOps
 : public Named
{
protected:
	static void _init(GLsizei count, GLuint* _name)
	{
		assert(_name != nullptr);
		*_name = OGLPLUS_GLFUNC(GenPathsNV)(count);
		HandleIfError(OGLPLUS_ERROR_INFO(GenTextures));
	}

	static void _cleanup(GLsizei count, GLuint* _name)
	{
		assert(_name != nullptr);
		assert(*_name != 0);
		OGLPLUS_GLFUNC(DeletePathsNV)(count, *_name);
	}

	static GLboolean _is_x(GLuint _name)
	{
		assert(_name != 0);
		return OGLPLUS_GLFUNC(IsPathNV)(_name);
	}

	friend class FriendOf<PathNVOps>;
public:
};

#if OGLPLUS_DOCUMENTATION_ONLY
/// An @ref oglplus_object encapsulating the nVidia path functionality
/**
 *  @ingroup objects
 */
class PathNV
 : public PathNVOps
{ };
#else
typedef Object<PathNVOps, false> PathNV;
#endif


/// Wrapper for the NV_path_rendering extension
/**
 *  @glsymbols
 *  @glextref{NV,path_rendering}
 *
 *  @ingroup extensions
 */
class NV_path_rendering
{
public:
	OGLPLUS_EXTENSION_CLASS(NV, path_rendering)
};
#endif

} // namespace oglplus

#endif // include guard
