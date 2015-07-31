/**
 *  @file oglplus/texgen/constant_output.hpp
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_TEXGEN_CONSTANT_OUTPUT_HPP
#define OGLPLUS_TEXGEN_CONSTANT_OUTPUT_HPP

#include <oglplus/texgen/delegate_output.hpp>
#include <oglplus/texgen/base_output.hpp>
#include <oglplus/utils/type_tag.hpp>
#include <oglplus/math/vector.hpp>
#include <sstream>

namespace oglplus {
namespace texgen {

class BaseConstantOutputSlot
 : public BaseOutputSlot
{
protected:
	static SlotDataType _t(TypeTag<GLfloat>);
	static SlotDataType _t(TypeTag<Vec2f>);
	static SlotDataType _t(TypeTag<Vec3f>);
	static SlotDataType _t(TypeTag<Vec4f>);

	void _format_head(std::ostream& os, const char* type);
	static void _format_tail(std::ostream& os);

	static void _format(std::ostream& os, GLfloat v);
	static void _format(std::ostream& os, const Vec2f& v);
	static void _format(std::ostream& os, const Vec3f& v);
	static void _format(std::ostream& os, const Vec4f& v);
public:
	const char* TypeName(void)
	OGLPLUS_OVERRIDE;

	static
	bool SupportsValueType(SlotDataType type);

	static
	std::unique_ptr<OutputSlot> MakeNew(SlotDataType type);
};

template <typename T>
class ConstantOutputSlot
 : public BaseConstantOutputSlot
{
private:
	T _v;
public:
	ConstantOutputSlot(T v)
	 : _v(v)
	{ }

	void SetValue(T v)
	{
		_v = v;
	}

	SlotDataType ValueType(void)
	OGLPLUS_OVERRIDE
	{
		return _t(TypeTag<T>());
	}

	String Definitions(unsigned)
	OGLPLUS_OVERRIDE
	{
		std::stringstream ss;
		_format_head(ss, DataTypeName(ValueType()));
		_format(ss, _v);
		_format_tail(ss);
		return ss.str();
	}
};

} // namespace texgen
} // namespace oglplus

//#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/texgen/constant_output.ipp>
//#endif

#endif // include guard
