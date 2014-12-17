/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_vertex_array_common
namespace oglplus {

template <>
class __ObjCommonOps<__tag_VertexArray>
 : public __VertexArrayName
{
public:
	static __VertexArrayName Binding(void); /*<
	Returns the currently bound vertex array.
	See [glfunc Get], [glconst VERTEX_ARRAY_BINDING].
	>*/

	static void Bind(__VertexArrayName vertex_array); /*<
	Binds the specified [^vertex_array] object.
	See [glfunc BindVertexArray].
	>*/
	void Bind(void) const; /*<
	Binds the [^this] vertex array object.
	See [glfunc BindVertexArray].
	>*/
};
//]
//[oglplus_vertex_array_def

typedef __ObjectOps<__tag_ImplicitSel, __tag_VertexArray>
	VertexArrayOps;

typedef __Object<VertexArrayOps> VertexArray;

typedef __ObjectZero<__ObjZeroOps<__tag_ImplicitSel, __tag_VertexArray>>
	NoVertexArray;

} // namespace oglplus
//]

