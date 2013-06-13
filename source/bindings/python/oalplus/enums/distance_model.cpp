/*
 *  .file oalplus/enums/distance_model.cpp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/oalplus/distance_model.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oalplus/al.hpp>
#include <oalplus/distance_model.hpp>

#include <boost/python.hpp>

#include "../range.hpp"

void oalplus_py_distance_model(void)
{
	boost::python::enum_<oalplus::DistanceModel>("DistanceModel")
#if defined AL_NONE
# if defined None
#  pragma push_macro("None")
#  undef None
	.value("None", oalplus::DistanceModel::None)
#  pragma pop_macro("None")
# else
	.value("None", oalplus::DistanceModel::None)
# endif
#endif
#if defined AL_INVERSE_DISTANCE
# if defined InverseDistance
#  pragma push_macro("InverseDistance")
#  undef InverseDistance
	.value("InverseDistance", oalplus::DistanceModel::InverseDistance)
#  pragma pop_macro("InverseDistance")
# else
	.value("InverseDistance", oalplus::DistanceModel::InverseDistance)
# endif
#endif
#if defined AL_INVERSE_DISTANCE_CLAMPED
# if defined InverseDistanceClamped
#  pragma push_macro("InverseDistanceClamped")
#  undef InverseDistanceClamped
	.value("InverseDistanceClamped", oalplus::DistanceModel::InverseDistanceClamped)
#  pragma pop_macro("InverseDistanceClamped")
# else
	.value("InverseDistanceClamped", oalplus::DistanceModel::InverseDistanceClamped)
# endif
#endif
#if defined AL_LINEAR_DISTANCE
# if defined LinearDistance
#  pragma push_macro("LinearDistance")
#  undef LinearDistance
	.value("LinearDistance", oalplus::DistanceModel::LinearDistance)
#  pragma pop_macro("LinearDistance")
# else
	.value("LinearDistance", oalplus::DistanceModel::LinearDistance)
# endif
#endif
#if defined AL_LINEAR_DISTANCE_CLAMPED
# if defined LinearDistanceClamped
#  pragma push_macro("LinearDistanceClamped")
#  undef LinearDistanceClamped
	.value("LinearDistanceClamped", oalplus::DistanceModel::LinearDistanceClamped)
#  pragma pop_macro("LinearDistanceClamped")
# else
	.value("LinearDistanceClamped", oalplus::DistanceModel::LinearDistanceClamped)
# endif
#endif
#if defined AL_EXPONENT_DISTANCE
# if defined ExponentDistance
#  pragma push_macro("ExponentDistance")
#  undef ExponentDistance
	.value("ExponentDistance", oalplus::DistanceModel::ExponentDistance)
#  pragma pop_macro("ExponentDistance")
# else
	.value("ExponentDistance", oalplus::DistanceModel::ExponentDistance)
# endif
#endif
#if defined AL_EXPONENT_DISTANCE_CLAMPED
# if defined ExponentDistanceClamped
#  pragma push_macro("ExponentDistanceClamped")
#  undef ExponentDistanceClamped
	.value("ExponentDistanceClamped", oalplus::DistanceModel::ExponentDistanceClamped)
#  pragma pop_macro("ExponentDistanceClamped")
# else
	.value("ExponentDistanceClamped", oalplus::DistanceModel::ExponentDistanceClamped)
# endif
#endif
	;

	oalplus::StrLit (*PEnumValueName)(oalplus::DistanceModel) =
		&oalplus::EnumValueName;
	boost::python::def("EnumValueName", PEnumValueName);

	oalplus_py_export_range<
		oalplus::aux::CastIterRange<
			const ALenum*,
			oalplus::DistanceModel
		>
	>("aux_CastIterRange_DistanceModel");

	oalplus::aux::CastIterRange<
		const ALenum*,
		oalplus::DistanceModel
	> (*PEnumValueRange)(oalplus::DistanceModel) =
		&oalplus::EnumValueRange;
	boost::python::def("EnumValueRange", PEnumValueRange);

}
