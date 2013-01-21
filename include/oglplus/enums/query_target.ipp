/*
 *  .file oglplus/enums/query_target.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/query_target.txt' instead.
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#if OGLPLUS_DOCUMENTATION_ONLY

/// TIME_ELAPSED: Time elapsed query
TimeElapsed,
/// TIMESTAMP: Current timestamp query
Timestamp,
/// SAMPLES_PASSED: Number of samples passed query
SamplesPassed,
/// ANY_SAMPLES_PASSED
AnySamplesPassed,
/// PRIMITIVES_GENERATED: Number of primitives generated
PrimitivesGenerated,
/// TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN: TFB primitives written
TransformFeedbackPrimitivesWritten

#else // !OGLPLUS_DOCUMENTATION_ONLY

# if !OGLPLUS_NO_SCOPED_ENUMS
// native scoped enums
# include <oglplus/enums/query_target_nse.ipp>
# else
// emulated scoped enums
# include <oglplus/enums/query_target_ese.ipp>
# endif

#endif
