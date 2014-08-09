/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_opt_ranges_ex_for_cat_tfm
using namespace oglplus::ranges;

ForEach(
	Concatenate<__StrCRef>(
		Transform(__EnumValueRange<__ObjectType>(), __EnumValueName<ObjectType>),
		Transform(__EnumValueRange<__ShaderType>(), __EnumValueName<ShaderType>)
	),
	[](__StrCRef str)
	{
		std::cout << str << std::endl;
	}
);
//]
