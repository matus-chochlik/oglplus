/**
 *  @file oglplus/shapes/vert_attr_info.hpp
 *  @brief Classes providing additional information about the shape builders
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_SHAPES_VERT_ATTR_INFO_1107121519_HPP
#define OGLPLUS_SHAPES_VERT_ATTR_INFO_1107121519_HPP

#include <oglplus/string.hpp>

namespace oglplus {
namespace shapes {

template <class ShapeBuilder, class VertexAttributeTag>
struct VertexAttribInfo;

#define OGLPLUS_SHAPES_HLPR_MAKE_VERT_ATTR_INFO(ATTR_NAME, GETTER_NAME) \
struct Vertex ## GETTER_NAME ## Tag { }; \
 \
template <class ShapeBuilder> \
struct VertexAttribInfo<ShapeBuilder, Vertex ## GETTER_NAME ## Tag> \
{ \
	static const GLchar* _name(void) \
	{ \
		return #ATTR_NAME; \
	} \
 \
	template <typename T> \
	static GLuint _getter_proc( \
		const ShapeBuilder& make, \
		std::vector<T>& dest \
	) \
	{ \
		return make.GETTER_NAME(dest); \
	} \
 \
	template <typename T> \
	static decltype(&VertexAttribInfo::_getter_proc<T>) _getter(T*) \
	{ \
		return &VertexAttribInfo::_getter_proc<T>; \
	} \
};

OGLPLUS_SHAPES_HLPR_MAKE_VERT_ATTR_INFO(Position, Positions)
OGLPLUS_SHAPES_HLPR_MAKE_VERT_ATTR_INFO(Normal, Normals)
OGLPLUS_SHAPES_HLPR_MAKE_VERT_ATTR_INFO(Tangent, Tangents)
OGLPLUS_SHAPES_HLPR_MAKE_VERT_ATTR_INFO(Binormal, Binormals)
OGLPLUS_SHAPES_HLPR_MAKE_VERT_ATTR_INFO(TexCoord, TexCoordinates)

#undef OGLPLUS_SHAPES_HLPR_MAKE_VERT_ATTR_INFO

#if OGLPLUS_DOCUMENTATION_ONLY
/// Informations about a vertex attribute getter function of a @c ShapeBuilder
/**
 */
class VertexAttribsInfo<ShapeBuiler>
{
public:
	/// Returns true if @c ShapeBuilder makes vertex attributes with @a name
	bool MakesVertexAttrib(const String& name) const;

	/// Returns the vertex attribute getter function by its @a name
	/** This functions tries to find a vertex attribute getter function
	 *  by the name of the vertex attribute. Returns a pointer to this
	 *  function if the @c ShapeBuilder provides one, returns a null pointer
	 *  otherwise.
	 *
	 *  The returned getter function has the following signature:
	 *  @code
	 *  GLuint GetterFunction(const ShapeBuilder&, std::vector<T>&);
	 *  @endcode
	 */
	template <typename T>
	static GetterFunction VertexAttribGetter(const String& name);
};
#else
template <class ShapeBuilder, typename ... VertexAttribTags>
class VertexAttribsInfo
 : protected VertexAttribInfo<ShapeBuilder, VertexAttribTags>...
{
private:

	template <typename Tag>
	const VertexAttribInfo<ShapeBuilder, Tag>& _info(Tag*) const
	{
		return *this;
	}

	static bool _has_vertex_attrib(const String&)
	{
		return false;
	}

	template <typename Tag, typename ... Tags>
	static bool _has_vertex_attrib(
		const String& name,
		const VertexAttribInfo<ShapeBuilder, Tag>& info,
		const VertexAttribInfo<ShapeBuilder, Tags>& ...infos
	)
	{
		if(name == info._name()) return true;
		else return _has_vertex_attrib(name, infos...);
	}

	template <typename T>
	static GLuint _getter_proc(const ShapeBuilder&, std::vector<T>&);

	template <typename T>
	static decltype(&VertexAttribsInfo::_getter_proc<T>)
	_find_getter(T*, const String&)
	{
		return nullptr;
	}

	template <typename T, typename Tag, typename ... Tags>
	static decltype(&VertexAttribsInfo::_getter_proc<T>) _find_getter(
		T* sel,
		const String& name,
		const VertexAttribInfo<ShapeBuilder, Tag>& info,
		const VertexAttribInfo<ShapeBuilder, Tags>& ...infos
	)
	{
		if(name == info._name()) return info._getter((T*)0);
		else return _find_getter(sel, name, infos...);
	}

public:
	bool MakesVertexAttrib(const String& name) const
	{
		return _has_vertex_attrib(name, _info((VertexAttribTags*)0)...);
	}

	template <typename T>
	decltype(&VertexAttribsInfo::_getter_proc<T>) VertexAttribGetter(
		const std::vector<T>& selector,
		const String& name
	) const
	{
		return _find_getter((T*)0, name, _info((VertexAttribTags*)0)...);
	}
};
#endif

} // shapes
} // oglplus

#endif // include guard
