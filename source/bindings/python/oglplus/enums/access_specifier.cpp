/*
 *  .file oglplus/enums/access_specifier.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oglplus/access_specifier.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/access_specifier.hpp>

#include <boost/python.hpp>

#include "../range.hpp"

void oglplus_py_access_specifier(void)
{
	boost::python::enum_<oglplus::AccessSpecifier>("AccessSpecifier")
#if defined GL_READ_ONLY
# if defined ReadOnly
#  pragma push_macro("ReadOnly")
#  undef ReadOnly
	.value("ReadOnly", oglplus::AccessSpecifier::ReadOnly)
#  pragma pop_macro("ReadOnly")
# else
	.value("ReadOnly", oglplus::AccessSpecifier::ReadOnly)
# endif
#endif
#if defined GL_WRITE_ONLY
# if defined WriteOnly
#  pragma push_macro("WriteOnly")
#  undef WriteOnly
	.value("WriteOnly", oglplus::AccessSpecifier::WriteOnly)
#  pragma pop_macro("WriteOnly")
# else
	.value("WriteOnly", oglplus::AccessSpecifier::WriteOnly)
# endif
#endif
#if defined GL_READ_WRITE
# if defined ReadWrite
#  pragma push_macro("ReadWrite")
#  undef ReadWrite
	.value("ReadWrite", oglplus::AccessSpecifier::ReadWrite)
#  pragma pop_macro("ReadWrite")
# else
	.value("ReadWrite", oglplus::AccessSpecifier::ReadWrite)
# endif
#endif
	;

	oglplus::StrLit (*PEnumValueName)(oglplus::AccessSpecifier) =
		&oglplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oglplus_py_export_range<
		oglplus::aux::CastIterRange<
			const GLenum*,
			oglplus::AccessSpecifier
		>
	>("aux_CastIterRange_AccessSpecifier");

	oglplus::aux::CastIterRange<
		const GLenum*,
		oglplus::AccessSpecifier
	> (*PEnumValueRange)(oglplus::AccessSpecifier) =
		&oglplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
