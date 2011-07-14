/**
 *  @file oglplus/object.hpp
 *  @brief Generic OpenGL object wrapper
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_OBJECT_1107121519_HPP
#define OGLPLUS_OBJECT_1107121519_HPP

namespace oglplus {

template <class Object>
class Array;

template <class ObjectOps>
class Object : public ObjectOps
{
private:
	GLuint _release(void)
	{
		GLuint res = this->_name;
		this->_name = 0;
		return res;
	}

	static inline void _do_init(GLsizei _c, GLuint& _n)
	{
		ObjectOps::_init(_c, _n);
	}

	static inline void _do_cleanup(GLsizei _c, GLuint& _n)
	{
		ObjectOps::_cleanup(_c, _n);
	}

	friend class Array<Object>;
public:
	inline Object(void)
	{
		_do_init(1, this->_name);
		assert(this->_name != 0);
	}

	Object(const Object&) = delete;

	inline Object(Object&& temp)
	 : ObjectOps(temp._release())
	{
		assert(this->_name != 0);
	}

	inline ~Object(void)
	{
		_do_cleanup(1, this->_name);
	}
};

} // namespace oglplus

#endif // include guard
