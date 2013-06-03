/**
 *  .file oglplus/auxiliary/vector_swizzle.ipp
 *  .brief Implementation of the Swizzled template
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

template <typename T, std::size_t N>
class Swizzled
 : public Vector<T, N>
{
public:
	Swizzled(Vector<T, N> v)
	 : Vector<T, N>(v)
	{ }

#define OGLPLUS_AUX_IMPLEMENT_VEC_SWIZZLE_1(I, U0, U1, U2, C0) \
	T C0(void) const \
	{ \
		return this->template At(I); \
	}

#define OGLPLUS_AUX_IMPLEMENT_VEC_SWIZZLE_2(I, U1, U2, C0, C1) \
	Vector<T, 2> C0 ## C1(void) const \
	{ \
		return Vector<T, 2>(C0(), C1()); \
	}

#define OGLPLUS_AUX_IMPLEMENT_VEC_SWIZZLE_3(I, U1, C0, C1, C2) \
	Vector<T, 3> C0 ## C1 ## C2(void) const \
	{ \
		return Vector<T, 3>(C0(), C1(), C2()); \
	}

#define OGLPLUS_AUX_IMPLEMENT_VEC_SWIZZLE_4(I, C0, C1, C2, C3) \
	Vector<T, 4> C0 ## C1 ## C2 ## C3(void) const \
	{ \
		return Vector<T, 4>(C0(), C1(), C2(), C3()); \
	}

#define OGLPLUS_AUX_CALL_IMPLEMENT_VEC_SWIZZLE_1d(N, X0, X1, X2, U0) \
	OGLPLUS_AUX_IMPLEMENT_VEC_SWIZZLE_ ## N(0, X0, X1, X2, x) \
	OGLPLUS_AUX_IMPLEMENT_VEC_SWIZZLE_ ## N(1, X0, X1, X2, y) \
	OGLPLUS_AUX_IMPLEMENT_VEC_SWIZZLE_ ## N(2, X0, X1, X2, z) \
	OGLPLUS_AUX_IMPLEMENT_VEC_SWIZZLE_ ## N(3, X0, X1, X2, w)

#define OGLPLUS_AUX_CALL_IMPLEMENT_VEC_SWIZZLE_2d(N, X0, X1, U0, U1) \
	OGLPLUS_AUX_CALL_IMPLEMENT_VEC_SWIZZLE_1d(N, X0, X1, x, U0) \
	OGLPLUS_AUX_CALL_IMPLEMENT_VEC_SWIZZLE_1d(N, X0, X1, y, U0) \
	OGLPLUS_AUX_CALL_IMPLEMENT_VEC_SWIZZLE_1d(N, X0, X1, z, U0) \
	OGLPLUS_AUX_CALL_IMPLEMENT_VEC_SWIZZLE_1d(N, X0, X1, w, U0)

#define OGLPLUS_AUX_CALL_IMPLEMENT_VEC_SWIZZLE_3d(N, X0, U0, U1, U2) \
	OGLPLUS_AUX_CALL_IMPLEMENT_VEC_SWIZZLE_2d(N, X0, x, U0, U1) \
	OGLPLUS_AUX_CALL_IMPLEMENT_VEC_SWIZZLE_2d(N, X0, y, U0, U1) \
	OGLPLUS_AUX_CALL_IMPLEMENT_VEC_SWIZZLE_2d(N, X0, z, U0, U1) \
	OGLPLUS_AUX_CALL_IMPLEMENT_VEC_SWIZZLE_2d(N, X0, w, U0, U1)

#define OGLPLUS_AUX_CALL_IMPLEMENT_VEC_SWIZZLE_4d(N, U0, U1, U2, U3) \
	OGLPLUS_AUX_CALL_IMPLEMENT_VEC_SWIZZLE_3d(N, x, U0, U1, U2) \
	OGLPLUS_AUX_CALL_IMPLEMENT_VEC_SWIZZLE_3d(N, y, U0, U1, U2) \
	OGLPLUS_AUX_CALL_IMPLEMENT_VEC_SWIZZLE_3d(N, z, U0, U1, U2) \
	OGLPLUS_AUX_CALL_IMPLEMENT_VEC_SWIZZLE_3d(N, w, U0, U1, U2)

#define OGLPLUS_AUX_CALL_IMPLEMENT_VEC_SWIZZLE(N) \
	OGLPLUS_AUX_CALL_IMPLEMENT_VEC_SWIZZLE_ ## N ## d(N, _, _, _, _)

	OGLPLUS_AUX_CALL_IMPLEMENT_VEC_SWIZZLE(1) 
	OGLPLUS_AUX_CALL_IMPLEMENT_VEC_SWIZZLE(2) 
	OGLPLUS_AUX_CALL_IMPLEMENT_VEC_SWIZZLE(3) 
	OGLPLUS_AUX_CALL_IMPLEMENT_VEC_SWIZZLE(4) 

#undef OGLPLUS_AUX_CALL_IMPLEMENT_VEC_SWIZZLE

#undef OGLPLUS_AUX_CALL_IMPLEMENT_VEC_SWIZZLE_4x
#undef OGLPLUS_AUX_CALL_IMPLEMENT_VEC_SWIZZLE_3x
#undef OGLPLUS_AUX_CALL_IMPLEMENT_VEC_SWIZZLE_2x
#undef OGLPLUS_AUX_CALL_IMPLEMENT_VEC_SWIZZLE_1x

#undef OGLPLUS_AUX_IMPLEMENT_VEC_SWIZZLE_4
#undef OGLPLUS_AUX_IMPLEMENT_VEC_SWIZZLE_3
#undef OGLPLUS_AUX_IMPLEMENT_VEC_SWIZZLE_2
#undef OGLPLUS_AUX_IMPLEMENT_VEC_SWIZZLE_1
};

template <typename T, std::size_t N>
inline Swizzled<T, N> Swizzle(Vector<T, N> v)
{
	return Swizzled<T, N>(v);
}


