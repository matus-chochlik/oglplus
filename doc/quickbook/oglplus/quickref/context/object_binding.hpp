/*
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_context_ObjectBinding
namespace context {

class ObjectBinding
{
public:
	template <typename Object>
	static
	void Bind(typename Object::Target target, const Object& object); /*<
	Binds the specified [^object] to the specified [^target].
	Equivalent to [^object.Bind(target)].
	>*/

	template <typename Object>
	static
	void Bind(
		typename Object::IndexedTarget target,
		GLuint index,
		const Object& object
	); /*<
	Binds the specified [^object] to the specified indexed [^target].
	Equivalent to [^object.Bind(target, index)].
	>*/

	template <typename Object>
	static
	void Bind(const Object& object); /*<
	Binds the specified object to the appropriate binding point.
	Equivalent to [^object.Bind()].
	>*/

	template <typename Object>
	static
	void Use(const Object& object); /*<
	Uses (makes current) the specified [^object] (for example a __Program).
	Equivalent to [^object.Use()].
	>*/


	// TODO
};

} // namespace context
//]

