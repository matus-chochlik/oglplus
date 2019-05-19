/*
 *  .file oglplus/math/vector_swizzle.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'tools/make_vec_swiz_header.sh' instead.
 *
 *  Copyright 2010-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

template <typename T, std::size_t N>
class Swizzled_xyzw;

template <typename T>
class Swizzled_xyzw<T, 1> : public Vector<T, 1> {
public:
    Swizzled_xyzw(Vector<T, 1> v)
      : Vector<T, 1>(v) {}

    T x() const {
        return this->At(0);
    }
};

template <typename T>
class Swizzled_xyzw<T, 2> : public Vector<T, 2> {
public:
    Swizzled_xyzw(Vector<T, 2> v)
      : Vector<T, 2>(v) {}

    T x() const {
        return this->At(0);
    }
    T y() const {
        return this->At(1);
    }

    Vector<T, 2> xx() const {
        return Vector<T, 2>(x(), x());
    }
    Vector<T, 2> xy() const {
        return Vector<T, 2>(x(), y());
    }
    Vector<T, 2> yx() const {
        return Vector<T, 2>(y(), x());
    }
    Vector<T, 2> yy() const {
        return Vector<T, 2>(y(), y());
    }
};

template <typename T>
class Swizzled_xyzw<T, 3> : public Vector<T, 3> {
public:
    Swizzled_xyzw(Vector<T, 3> v)
      : Vector<T, 3>(v) {}

    T x() const {
        return this->At(0);
    }
    T y() const {
        return this->At(1);
    }
    T z() const {
        return this->At(2);
    }

    Vector<T, 2> xx() const {
        return Vector<T, 2>(x(), x());
    }
    Vector<T, 2> xy() const {
        return Vector<T, 2>(x(), y());
    }
    Vector<T, 2> xz() const {
        return Vector<T, 2>(x(), z());
    }
    Vector<T, 2> yx() const {
        return Vector<T, 2>(y(), x());
    }
    Vector<T, 2> yy() const {
        return Vector<T, 2>(y(), y());
    }
    Vector<T, 2> yz() const {
        return Vector<T, 2>(y(), z());
    }
    Vector<T, 2> zx() const {
        return Vector<T, 2>(z(), x());
    }
    Vector<T, 2> zy() const {
        return Vector<T, 2>(z(), y());
    }
    Vector<T, 2> zz() const {
        return Vector<T, 2>(z(), z());
    }

    Vector<T, 3> xxx() const {
        return Vector<T, 3>(x(), x(), x());
    }
    Vector<T, 3> xxy() const {
        return Vector<T, 3>(x(), x(), y());
    }
    Vector<T, 3> xxz() const {
        return Vector<T, 3>(x(), x(), z());
    }
    Vector<T, 3> xyx() const {
        return Vector<T, 3>(x(), y(), x());
    }
    Vector<T, 3> xyy() const {
        return Vector<T, 3>(x(), y(), y());
    }
    Vector<T, 3> xyz() const {
        return Vector<T, 3>(x(), y(), z());
    }
    Vector<T, 3> xzx() const {
        return Vector<T, 3>(x(), z(), x());
    }
    Vector<T, 3> xzy() const {
        return Vector<T, 3>(x(), z(), y());
    }
    Vector<T, 3> xzz() const {
        return Vector<T, 3>(x(), z(), z());
    }
    Vector<T, 3> yxx() const {
        return Vector<T, 3>(y(), x(), x());
    }
    Vector<T, 3> yxy() const {
        return Vector<T, 3>(y(), x(), y());
    }
    Vector<T, 3> yxz() const {
        return Vector<T, 3>(y(), x(), z());
    }
    Vector<T, 3> yyx() const {
        return Vector<T, 3>(y(), y(), x());
    }
    Vector<T, 3> yyy() const {
        return Vector<T, 3>(y(), y(), y());
    }
    Vector<T, 3> yyz() const {
        return Vector<T, 3>(y(), y(), z());
    }
    Vector<T, 3> yzx() const {
        return Vector<T, 3>(y(), z(), x());
    }
    Vector<T, 3> yzy() const {
        return Vector<T, 3>(y(), z(), y());
    }
    Vector<T, 3> yzz() const {
        return Vector<T, 3>(y(), z(), z());
    }
    Vector<T, 3> zxx() const {
        return Vector<T, 3>(z(), x(), x());
    }
    Vector<T, 3> zxy() const {
        return Vector<T, 3>(z(), x(), y());
    }
    Vector<T, 3> zxz() const {
        return Vector<T, 3>(z(), x(), z());
    }
    Vector<T, 3> zyx() const {
        return Vector<T, 3>(z(), y(), x());
    }
    Vector<T, 3> zyy() const {
        return Vector<T, 3>(z(), y(), y());
    }
    Vector<T, 3> zyz() const {
        return Vector<T, 3>(z(), y(), z());
    }
    Vector<T, 3> zzx() const {
        return Vector<T, 3>(z(), z(), x());
    }
    Vector<T, 3> zzy() const {
        return Vector<T, 3>(z(), z(), y());
    }
    Vector<T, 3> zzz() const {
        return Vector<T, 3>(z(), z(), z());
    }
};

template <typename T>
class Swizzled_xyzw<T, 4> : public Vector<T, 4> {
public:
    Swizzled_xyzw(Vector<T, 4> v)
      : Vector<T, 4>(v) {}

    T x() const {
        return this->At(0);
    }
    T y() const {
        return this->At(1);
    }
    T z() const {
        return this->At(2);
    }
    T w() const {
        return this->At(3);
    }

    Vector<T, 2> xx() const {
        return Vector<T, 2>(x(), x());
    }
    Vector<T, 2> xy() const {
        return Vector<T, 2>(x(), y());
    }
    Vector<T, 2> xz() const {
        return Vector<T, 2>(x(), z());
    }
    Vector<T, 2> xw() const {
        return Vector<T, 2>(x(), w());
    }
    Vector<T, 2> yx() const {
        return Vector<T, 2>(y(), x());
    }
    Vector<T, 2> yy() const {
        return Vector<T, 2>(y(), y());
    }
    Vector<T, 2> yz() const {
        return Vector<T, 2>(y(), z());
    }
    Vector<T, 2> yw() const {
        return Vector<T, 2>(y(), w());
    }
    Vector<T, 2> zx() const {
        return Vector<T, 2>(z(), x());
    }
    Vector<T, 2> zy() const {
        return Vector<T, 2>(z(), y());
    }
    Vector<T, 2> zz() const {
        return Vector<T, 2>(z(), z());
    }
    Vector<T, 2> zw() const {
        return Vector<T, 2>(z(), w());
    }
    Vector<T, 2> wx() const {
        return Vector<T, 2>(w(), x());
    }
    Vector<T, 2> wy() const {
        return Vector<T, 2>(w(), y());
    }
    Vector<T, 2> wz() const {
        return Vector<T, 2>(w(), z());
    }
    Vector<T, 2> ww() const {
        return Vector<T, 2>(w(), w());
    }

    Vector<T, 3> xxx() const {
        return Vector<T, 3>(x(), x(), x());
    }
    Vector<T, 3> xxy() const {
        return Vector<T, 3>(x(), x(), y());
    }
    Vector<T, 3> xxz() const {
        return Vector<T, 3>(x(), x(), z());
    }
    Vector<T, 3> xxw() const {
        return Vector<T, 3>(x(), x(), w());
    }
    Vector<T, 3> xyx() const {
        return Vector<T, 3>(x(), y(), x());
    }
    Vector<T, 3> xyy() const {
        return Vector<T, 3>(x(), y(), y());
    }
    Vector<T, 3> xyz() const {
        return Vector<T, 3>(x(), y(), z());
    }
    Vector<T, 3> xyw() const {
        return Vector<T, 3>(x(), y(), w());
    }
    Vector<T, 3> xzx() const {
        return Vector<T, 3>(x(), z(), x());
    }
    Vector<T, 3> xzy() const {
        return Vector<T, 3>(x(), z(), y());
    }
    Vector<T, 3> xzz() const {
        return Vector<T, 3>(x(), z(), z());
    }
    Vector<T, 3> xzw() const {
        return Vector<T, 3>(x(), z(), w());
    }
    Vector<T, 3> xwx() const {
        return Vector<T, 3>(x(), w(), x());
    }
    Vector<T, 3> xwy() const {
        return Vector<T, 3>(x(), w(), y());
    }
    Vector<T, 3> xwz() const {
        return Vector<T, 3>(x(), w(), z());
    }
    Vector<T, 3> xww() const {
        return Vector<T, 3>(x(), w(), w());
    }
    Vector<T, 3> yxx() const {
        return Vector<T, 3>(y(), x(), x());
    }
    Vector<T, 3> yxy() const {
        return Vector<T, 3>(y(), x(), y());
    }
    Vector<T, 3> yxz() const {
        return Vector<T, 3>(y(), x(), z());
    }
    Vector<T, 3> yxw() const {
        return Vector<T, 3>(y(), x(), w());
    }
    Vector<T, 3> yyx() const {
        return Vector<T, 3>(y(), y(), x());
    }
    Vector<T, 3> yyy() const {
        return Vector<T, 3>(y(), y(), y());
    }
    Vector<T, 3> yyz() const {
        return Vector<T, 3>(y(), y(), z());
    }
    Vector<T, 3> yyw() const {
        return Vector<T, 3>(y(), y(), w());
    }
    Vector<T, 3> yzx() const {
        return Vector<T, 3>(y(), z(), x());
    }
    Vector<T, 3> yzy() const {
        return Vector<T, 3>(y(), z(), y());
    }
    Vector<T, 3> yzz() const {
        return Vector<T, 3>(y(), z(), z());
    }
    Vector<T, 3> yzw() const {
        return Vector<T, 3>(y(), z(), w());
    }
    Vector<T, 3> ywx() const {
        return Vector<T, 3>(y(), w(), x());
    }
    Vector<T, 3> ywy() const {
        return Vector<T, 3>(y(), w(), y());
    }
    Vector<T, 3> ywz() const {
        return Vector<T, 3>(y(), w(), z());
    }
    Vector<T, 3> yww() const {
        return Vector<T, 3>(y(), w(), w());
    }
    Vector<T, 3> zxx() const {
        return Vector<T, 3>(z(), x(), x());
    }
    Vector<T, 3> zxy() const {
        return Vector<T, 3>(z(), x(), y());
    }
    Vector<T, 3> zxz() const {
        return Vector<T, 3>(z(), x(), z());
    }
    Vector<T, 3> zxw() const {
        return Vector<T, 3>(z(), x(), w());
    }
    Vector<T, 3> zyx() const {
        return Vector<T, 3>(z(), y(), x());
    }
    Vector<T, 3> zyy() const {
        return Vector<T, 3>(z(), y(), y());
    }
    Vector<T, 3> zyz() const {
        return Vector<T, 3>(z(), y(), z());
    }
    Vector<T, 3> zyw() const {
        return Vector<T, 3>(z(), y(), w());
    }
    Vector<T, 3> zzx() const {
        return Vector<T, 3>(z(), z(), x());
    }
    Vector<T, 3> zzy() const {
        return Vector<T, 3>(z(), z(), y());
    }
    Vector<T, 3> zzz() const {
        return Vector<T, 3>(z(), z(), z());
    }
    Vector<T, 3> zzw() const {
        return Vector<T, 3>(z(), z(), w());
    }
    Vector<T, 3> zwx() const {
        return Vector<T, 3>(z(), w(), x());
    }
    Vector<T, 3> zwy() const {
        return Vector<T, 3>(z(), w(), y());
    }
    Vector<T, 3> zwz() const {
        return Vector<T, 3>(z(), w(), z());
    }
    Vector<T, 3> zww() const {
        return Vector<T, 3>(z(), w(), w());
    }
    Vector<T, 3> wxx() const {
        return Vector<T, 3>(w(), x(), x());
    }
    Vector<T, 3> wxy() const {
        return Vector<T, 3>(w(), x(), y());
    }
    Vector<T, 3> wxz() const {
        return Vector<T, 3>(w(), x(), z());
    }
    Vector<T, 3> wxw() const {
        return Vector<T, 3>(w(), x(), w());
    }
    Vector<T, 3> wyx() const {
        return Vector<T, 3>(w(), y(), x());
    }
    Vector<T, 3> wyy() const {
        return Vector<T, 3>(w(), y(), y());
    }
    Vector<T, 3> wyz() const {
        return Vector<T, 3>(w(), y(), z());
    }
    Vector<T, 3> wyw() const {
        return Vector<T, 3>(w(), y(), w());
    }
    Vector<T, 3> wzx() const {
        return Vector<T, 3>(w(), z(), x());
    }
    Vector<T, 3> wzy() const {
        return Vector<T, 3>(w(), z(), y());
    }
    Vector<T, 3> wzz() const {
        return Vector<T, 3>(w(), z(), z());
    }
    Vector<T, 3> wzw() const {
        return Vector<T, 3>(w(), z(), w());
    }
    Vector<T, 3> wwx() const {
        return Vector<T, 3>(w(), w(), x());
    }
    Vector<T, 3> wwy() const {
        return Vector<T, 3>(w(), w(), y());
    }
    Vector<T, 3> wwz() const {
        return Vector<T, 3>(w(), w(), z());
    }
    Vector<T, 3> www() const {
        return Vector<T, 3>(w(), w(), w());
    }

    Vector<T, 4> xxxx() const {
        return Vector<T, 4>(x(), x(), x(), x());
    }
    Vector<T, 4> xxxy() const {
        return Vector<T, 4>(x(), x(), x(), y());
    }
    Vector<T, 4> xxxz() const {
        return Vector<T, 4>(x(), x(), x(), z());
    }
    Vector<T, 4> xxxw() const {
        return Vector<T, 4>(x(), x(), x(), w());
    }
    Vector<T, 4> xxyx() const {
        return Vector<T, 4>(x(), x(), y(), x());
    }
    Vector<T, 4> xxyy() const {
        return Vector<T, 4>(x(), x(), y(), y());
    }
    Vector<T, 4> xxyz() const {
        return Vector<T, 4>(x(), x(), y(), z());
    }
    Vector<T, 4> xxyw() const {
        return Vector<T, 4>(x(), x(), y(), w());
    }
    Vector<T, 4> xxzx() const {
        return Vector<T, 4>(x(), x(), z(), x());
    }
    Vector<T, 4> xxzy() const {
        return Vector<T, 4>(x(), x(), z(), y());
    }
    Vector<T, 4> xxzz() const {
        return Vector<T, 4>(x(), x(), z(), z());
    }
    Vector<T, 4> xxzw() const {
        return Vector<T, 4>(x(), x(), z(), w());
    }
    Vector<T, 4> xxwx() const {
        return Vector<T, 4>(x(), x(), w(), x());
    }
    Vector<T, 4> xxwy() const {
        return Vector<T, 4>(x(), x(), w(), y());
    }
    Vector<T, 4> xxwz() const {
        return Vector<T, 4>(x(), x(), w(), z());
    }
    Vector<T, 4> xxww() const {
        return Vector<T, 4>(x(), x(), w(), w());
    }
    Vector<T, 4> xyxx() const {
        return Vector<T, 4>(x(), y(), x(), x());
    }
    Vector<T, 4> xyxy() const {
        return Vector<T, 4>(x(), y(), x(), y());
    }
    Vector<T, 4> xyxz() const {
        return Vector<T, 4>(x(), y(), x(), z());
    }
    Vector<T, 4> xyxw() const {
        return Vector<T, 4>(x(), y(), x(), w());
    }
    Vector<T, 4> xyyx() const {
        return Vector<T, 4>(x(), y(), y(), x());
    }
    Vector<T, 4> xyyy() const {
        return Vector<T, 4>(x(), y(), y(), y());
    }
    Vector<T, 4> xyyz() const {
        return Vector<T, 4>(x(), y(), y(), z());
    }
    Vector<T, 4> xyyw() const {
        return Vector<T, 4>(x(), y(), y(), w());
    }
    Vector<T, 4> xyzx() const {
        return Vector<T, 4>(x(), y(), z(), x());
    }
    Vector<T, 4> xyzy() const {
        return Vector<T, 4>(x(), y(), z(), y());
    }
    Vector<T, 4> xyzz() const {
        return Vector<T, 4>(x(), y(), z(), z());
    }
    Vector<T, 4> xyzw() const {
        return Vector<T, 4>(x(), y(), z(), w());
    }
    Vector<T, 4> xywx() const {
        return Vector<T, 4>(x(), y(), w(), x());
    }
    Vector<T, 4> xywy() const {
        return Vector<T, 4>(x(), y(), w(), y());
    }
    Vector<T, 4> xywz() const {
        return Vector<T, 4>(x(), y(), w(), z());
    }
    Vector<T, 4> xyww() const {
        return Vector<T, 4>(x(), y(), w(), w());
    }
    Vector<T, 4> xzxx() const {
        return Vector<T, 4>(x(), z(), x(), x());
    }
    Vector<T, 4> xzxy() const {
        return Vector<T, 4>(x(), z(), x(), y());
    }
    Vector<T, 4> xzxz() const {
        return Vector<T, 4>(x(), z(), x(), z());
    }
    Vector<T, 4> xzxw() const {
        return Vector<T, 4>(x(), z(), x(), w());
    }
    Vector<T, 4> xzyx() const {
        return Vector<T, 4>(x(), z(), y(), x());
    }
    Vector<T, 4> xzyy() const {
        return Vector<T, 4>(x(), z(), y(), y());
    }
    Vector<T, 4> xzyz() const {
        return Vector<T, 4>(x(), z(), y(), z());
    }
    Vector<T, 4> xzyw() const {
        return Vector<T, 4>(x(), z(), y(), w());
    }
    Vector<T, 4> xzzx() const {
        return Vector<T, 4>(x(), z(), z(), x());
    }
    Vector<T, 4> xzzy() const {
        return Vector<T, 4>(x(), z(), z(), y());
    }
    Vector<T, 4> xzzz() const {
        return Vector<T, 4>(x(), z(), z(), z());
    }
    Vector<T, 4> xzzw() const {
        return Vector<T, 4>(x(), z(), z(), w());
    }
    Vector<T, 4> xzwx() const {
        return Vector<T, 4>(x(), z(), w(), x());
    }
    Vector<T, 4> xzwy() const {
        return Vector<T, 4>(x(), z(), w(), y());
    }
    Vector<T, 4> xzwz() const {
        return Vector<T, 4>(x(), z(), w(), z());
    }
    Vector<T, 4> xzww() const {
        return Vector<T, 4>(x(), z(), w(), w());
    }
    Vector<T, 4> xwxx() const {
        return Vector<T, 4>(x(), w(), x(), x());
    }
    Vector<T, 4> xwxy() const {
        return Vector<T, 4>(x(), w(), x(), y());
    }
    Vector<T, 4> xwxz() const {
        return Vector<T, 4>(x(), w(), x(), z());
    }
    Vector<T, 4> xwxw() const {
        return Vector<T, 4>(x(), w(), x(), w());
    }
    Vector<T, 4> xwyx() const {
        return Vector<T, 4>(x(), w(), y(), x());
    }
    Vector<T, 4> xwyy() const {
        return Vector<T, 4>(x(), w(), y(), y());
    }
    Vector<T, 4> xwyz() const {
        return Vector<T, 4>(x(), w(), y(), z());
    }
    Vector<T, 4> xwyw() const {
        return Vector<T, 4>(x(), w(), y(), w());
    }
    Vector<T, 4> xwzx() const {
        return Vector<T, 4>(x(), w(), z(), x());
    }
    Vector<T, 4> xwzy() const {
        return Vector<T, 4>(x(), w(), z(), y());
    }
    Vector<T, 4> xwzz() const {
        return Vector<T, 4>(x(), w(), z(), z());
    }
    Vector<T, 4> xwzw() const {
        return Vector<T, 4>(x(), w(), z(), w());
    }
    Vector<T, 4> xwwx() const {
        return Vector<T, 4>(x(), w(), w(), x());
    }
    Vector<T, 4> xwwy() const {
        return Vector<T, 4>(x(), w(), w(), y());
    }
    Vector<T, 4> xwwz() const {
        return Vector<T, 4>(x(), w(), w(), z());
    }
    Vector<T, 4> xwww() const {
        return Vector<T, 4>(x(), w(), w(), w());
    }
    Vector<T, 4> yxxx() const {
        return Vector<T, 4>(y(), x(), x(), x());
    }
    Vector<T, 4> yxxy() const {
        return Vector<T, 4>(y(), x(), x(), y());
    }
    Vector<T, 4> yxxz() const {
        return Vector<T, 4>(y(), x(), x(), z());
    }
    Vector<T, 4> yxxw() const {
        return Vector<T, 4>(y(), x(), x(), w());
    }
    Vector<T, 4> yxyx() const {
        return Vector<T, 4>(y(), x(), y(), x());
    }
    Vector<T, 4> yxyy() const {
        return Vector<T, 4>(y(), x(), y(), y());
    }
    Vector<T, 4> yxyz() const {
        return Vector<T, 4>(y(), x(), y(), z());
    }
    Vector<T, 4> yxyw() const {
        return Vector<T, 4>(y(), x(), y(), w());
    }
    Vector<T, 4> yxzx() const {
        return Vector<T, 4>(y(), x(), z(), x());
    }
    Vector<T, 4> yxzy() const {
        return Vector<T, 4>(y(), x(), z(), y());
    }
    Vector<T, 4> yxzz() const {
        return Vector<T, 4>(y(), x(), z(), z());
    }
    Vector<T, 4> yxzw() const {
        return Vector<T, 4>(y(), x(), z(), w());
    }
    Vector<T, 4> yxwx() const {
        return Vector<T, 4>(y(), x(), w(), x());
    }
    Vector<T, 4> yxwy() const {
        return Vector<T, 4>(y(), x(), w(), y());
    }
    Vector<T, 4> yxwz() const {
        return Vector<T, 4>(y(), x(), w(), z());
    }
    Vector<T, 4> yxww() const {
        return Vector<T, 4>(y(), x(), w(), w());
    }
    Vector<T, 4> yyxx() const {
        return Vector<T, 4>(y(), y(), x(), x());
    }
    Vector<T, 4> yyxy() const {
        return Vector<T, 4>(y(), y(), x(), y());
    }
    Vector<T, 4> yyxz() const {
        return Vector<T, 4>(y(), y(), x(), z());
    }
    Vector<T, 4> yyxw() const {
        return Vector<T, 4>(y(), y(), x(), w());
    }
    Vector<T, 4> yyyx() const {
        return Vector<T, 4>(y(), y(), y(), x());
    }
    Vector<T, 4> yyyy() const {
        return Vector<T, 4>(y(), y(), y(), y());
    }
    Vector<T, 4> yyyz() const {
        return Vector<T, 4>(y(), y(), y(), z());
    }
    Vector<T, 4> yyyw() const {
        return Vector<T, 4>(y(), y(), y(), w());
    }
    Vector<T, 4> yyzx() const {
        return Vector<T, 4>(y(), y(), z(), x());
    }
    Vector<T, 4> yyzy() const {
        return Vector<T, 4>(y(), y(), z(), y());
    }
    Vector<T, 4> yyzz() const {
        return Vector<T, 4>(y(), y(), z(), z());
    }
    Vector<T, 4> yyzw() const {
        return Vector<T, 4>(y(), y(), z(), w());
    }
    Vector<T, 4> yywx() const {
        return Vector<T, 4>(y(), y(), w(), x());
    }
    Vector<T, 4> yywy() const {
        return Vector<T, 4>(y(), y(), w(), y());
    }
    Vector<T, 4> yywz() const {
        return Vector<T, 4>(y(), y(), w(), z());
    }
    Vector<T, 4> yyww() const {
        return Vector<T, 4>(y(), y(), w(), w());
    }
    Vector<T, 4> yzxx() const {
        return Vector<T, 4>(y(), z(), x(), x());
    }
    Vector<T, 4> yzxy() const {
        return Vector<T, 4>(y(), z(), x(), y());
    }
    Vector<T, 4> yzxz() const {
        return Vector<T, 4>(y(), z(), x(), z());
    }
    Vector<T, 4> yzxw() const {
        return Vector<T, 4>(y(), z(), x(), w());
    }
    Vector<T, 4> yzyx() const {
        return Vector<T, 4>(y(), z(), y(), x());
    }
    Vector<T, 4> yzyy() const {
        return Vector<T, 4>(y(), z(), y(), y());
    }
    Vector<T, 4> yzyz() const {
        return Vector<T, 4>(y(), z(), y(), z());
    }
    Vector<T, 4> yzyw() const {
        return Vector<T, 4>(y(), z(), y(), w());
    }
    Vector<T, 4> yzzx() const {
        return Vector<T, 4>(y(), z(), z(), x());
    }
    Vector<T, 4> yzzy() const {
        return Vector<T, 4>(y(), z(), z(), y());
    }
    Vector<T, 4> yzzz() const {
        return Vector<T, 4>(y(), z(), z(), z());
    }
    Vector<T, 4> yzzw() const {
        return Vector<T, 4>(y(), z(), z(), w());
    }
    Vector<T, 4> yzwx() const {
        return Vector<T, 4>(y(), z(), w(), x());
    }
    Vector<T, 4> yzwy() const {
        return Vector<T, 4>(y(), z(), w(), y());
    }
    Vector<T, 4> yzwz() const {
        return Vector<T, 4>(y(), z(), w(), z());
    }
    Vector<T, 4> yzww() const {
        return Vector<T, 4>(y(), z(), w(), w());
    }
    Vector<T, 4> ywxx() const {
        return Vector<T, 4>(y(), w(), x(), x());
    }
    Vector<T, 4> ywxy() const {
        return Vector<T, 4>(y(), w(), x(), y());
    }
    Vector<T, 4> ywxz() const {
        return Vector<T, 4>(y(), w(), x(), z());
    }
    Vector<T, 4> ywxw() const {
        return Vector<T, 4>(y(), w(), x(), w());
    }
    Vector<T, 4> ywyx() const {
        return Vector<T, 4>(y(), w(), y(), x());
    }
    Vector<T, 4> ywyy() const {
        return Vector<T, 4>(y(), w(), y(), y());
    }
    Vector<T, 4> ywyz() const {
        return Vector<T, 4>(y(), w(), y(), z());
    }
    Vector<T, 4> ywyw() const {
        return Vector<T, 4>(y(), w(), y(), w());
    }
    Vector<T, 4> ywzx() const {
        return Vector<T, 4>(y(), w(), z(), x());
    }
    Vector<T, 4> ywzy() const {
        return Vector<T, 4>(y(), w(), z(), y());
    }
    Vector<T, 4> ywzz() const {
        return Vector<T, 4>(y(), w(), z(), z());
    }
    Vector<T, 4> ywzw() const {
        return Vector<T, 4>(y(), w(), z(), w());
    }
    Vector<T, 4> ywwx() const {
        return Vector<T, 4>(y(), w(), w(), x());
    }
    Vector<T, 4> ywwy() const {
        return Vector<T, 4>(y(), w(), w(), y());
    }
    Vector<T, 4> ywwz() const {
        return Vector<T, 4>(y(), w(), w(), z());
    }
    Vector<T, 4> ywww() const {
        return Vector<T, 4>(y(), w(), w(), w());
    }
    Vector<T, 4> zxxx() const {
        return Vector<T, 4>(z(), x(), x(), x());
    }
    Vector<T, 4> zxxy() const {
        return Vector<T, 4>(z(), x(), x(), y());
    }
    Vector<T, 4> zxxz() const {
        return Vector<T, 4>(z(), x(), x(), z());
    }
    Vector<T, 4> zxxw() const {
        return Vector<T, 4>(z(), x(), x(), w());
    }
    Vector<T, 4> zxyx() const {
        return Vector<T, 4>(z(), x(), y(), x());
    }
    Vector<T, 4> zxyy() const {
        return Vector<T, 4>(z(), x(), y(), y());
    }
    Vector<T, 4> zxyz() const {
        return Vector<T, 4>(z(), x(), y(), z());
    }
    Vector<T, 4> zxyw() const {
        return Vector<T, 4>(z(), x(), y(), w());
    }
    Vector<T, 4> zxzx() const {
        return Vector<T, 4>(z(), x(), z(), x());
    }
    Vector<T, 4> zxzy() const {
        return Vector<T, 4>(z(), x(), z(), y());
    }
    Vector<T, 4> zxzz() const {
        return Vector<T, 4>(z(), x(), z(), z());
    }
    Vector<T, 4> zxzw() const {
        return Vector<T, 4>(z(), x(), z(), w());
    }
    Vector<T, 4> zxwx() const {
        return Vector<T, 4>(z(), x(), w(), x());
    }
    Vector<T, 4> zxwy() const {
        return Vector<T, 4>(z(), x(), w(), y());
    }
    Vector<T, 4> zxwz() const {
        return Vector<T, 4>(z(), x(), w(), z());
    }
    Vector<T, 4> zxww() const {
        return Vector<T, 4>(z(), x(), w(), w());
    }
    Vector<T, 4> zyxx() const {
        return Vector<T, 4>(z(), y(), x(), x());
    }
    Vector<T, 4> zyxy() const {
        return Vector<T, 4>(z(), y(), x(), y());
    }
    Vector<T, 4> zyxz() const {
        return Vector<T, 4>(z(), y(), x(), z());
    }
    Vector<T, 4> zyxw() const {
        return Vector<T, 4>(z(), y(), x(), w());
    }
    Vector<T, 4> zyyx() const {
        return Vector<T, 4>(z(), y(), y(), x());
    }
    Vector<T, 4> zyyy() const {
        return Vector<T, 4>(z(), y(), y(), y());
    }
    Vector<T, 4> zyyz() const {
        return Vector<T, 4>(z(), y(), y(), z());
    }
    Vector<T, 4> zyyw() const {
        return Vector<T, 4>(z(), y(), y(), w());
    }
    Vector<T, 4> zyzx() const {
        return Vector<T, 4>(z(), y(), z(), x());
    }
    Vector<T, 4> zyzy() const {
        return Vector<T, 4>(z(), y(), z(), y());
    }
    Vector<T, 4> zyzz() const {
        return Vector<T, 4>(z(), y(), z(), z());
    }
    Vector<T, 4> zyzw() const {
        return Vector<T, 4>(z(), y(), z(), w());
    }
    Vector<T, 4> zywx() const {
        return Vector<T, 4>(z(), y(), w(), x());
    }
    Vector<T, 4> zywy() const {
        return Vector<T, 4>(z(), y(), w(), y());
    }
    Vector<T, 4> zywz() const {
        return Vector<T, 4>(z(), y(), w(), z());
    }
    Vector<T, 4> zyww() const {
        return Vector<T, 4>(z(), y(), w(), w());
    }
    Vector<T, 4> zzxx() const {
        return Vector<T, 4>(z(), z(), x(), x());
    }
    Vector<T, 4> zzxy() const {
        return Vector<T, 4>(z(), z(), x(), y());
    }
    Vector<T, 4> zzxz() const {
        return Vector<T, 4>(z(), z(), x(), z());
    }
    Vector<T, 4> zzxw() const {
        return Vector<T, 4>(z(), z(), x(), w());
    }
    Vector<T, 4> zzyx() const {
        return Vector<T, 4>(z(), z(), y(), x());
    }
    Vector<T, 4> zzyy() const {
        return Vector<T, 4>(z(), z(), y(), y());
    }
    Vector<T, 4> zzyz() const {
        return Vector<T, 4>(z(), z(), y(), z());
    }
    Vector<T, 4> zzyw() const {
        return Vector<T, 4>(z(), z(), y(), w());
    }
    Vector<T, 4> zzzx() const {
        return Vector<T, 4>(z(), z(), z(), x());
    }
    Vector<T, 4> zzzy() const {
        return Vector<T, 4>(z(), z(), z(), y());
    }
    Vector<T, 4> zzzz() const {
        return Vector<T, 4>(z(), z(), z(), z());
    }
    Vector<T, 4> zzzw() const {
        return Vector<T, 4>(z(), z(), z(), w());
    }
    Vector<T, 4> zzwx() const {
        return Vector<T, 4>(z(), z(), w(), x());
    }
    Vector<T, 4> zzwy() const {
        return Vector<T, 4>(z(), z(), w(), y());
    }
    Vector<T, 4> zzwz() const {
        return Vector<T, 4>(z(), z(), w(), z());
    }
    Vector<T, 4> zzww() const {
        return Vector<T, 4>(z(), z(), w(), w());
    }
    Vector<T, 4> zwxx() const {
        return Vector<T, 4>(z(), w(), x(), x());
    }
    Vector<T, 4> zwxy() const {
        return Vector<T, 4>(z(), w(), x(), y());
    }
    Vector<T, 4> zwxz() const {
        return Vector<T, 4>(z(), w(), x(), z());
    }
    Vector<T, 4> zwxw() const {
        return Vector<T, 4>(z(), w(), x(), w());
    }
    Vector<T, 4> zwyx() const {
        return Vector<T, 4>(z(), w(), y(), x());
    }
    Vector<T, 4> zwyy() const {
        return Vector<T, 4>(z(), w(), y(), y());
    }
    Vector<T, 4> zwyz() const {
        return Vector<T, 4>(z(), w(), y(), z());
    }
    Vector<T, 4> zwyw() const {
        return Vector<T, 4>(z(), w(), y(), w());
    }
    Vector<T, 4> zwzx() const {
        return Vector<T, 4>(z(), w(), z(), x());
    }
    Vector<T, 4> zwzy() const {
        return Vector<T, 4>(z(), w(), z(), y());
    }
    Vector<T, 4> zwzz() const {
        return Vector<T, 4>(z(), w(), z(), z());
    }
    Vector<T, 4> zwzw() const {
        return Vector<T, 4>(z(), w(), z(), w());
    }
    Vector<T, 4> zwwx() const {
        return Vector<T, 4>(z(), w(), w(), x());
    }
    Vector<T, 4> zwwy() const {
        return Vector<T, 4>(z(), w(), w(), y());
    }
    Vector<T, 4> zwwz() const {
        return Vector<T, 4>(z(), w(), w(), z());
    }
    Vector<T, 4> zwww() const {
        return Vector<T, 4>(z(), w(), w(), w());
    }
    Vector<T, 4> wxxx() const {
        return Vector<T, 4>(w(), x(), x(), x());
    }
    Vector<T, 4> wxxy() const {
        return Vector<T, 4>(w(), x(), x(), y());
    }
    Vector<T, 4> wxxz() const {
        return Vector<T, 4>(w(), x(), x(), z());
    }
    Vector<T, 4> wxxw() const {
        return Vector<T, 4>(w(), x(), x(), w());
    }
    Vector<T, 4> wxyx() const {
        return Vector<T, 4>(w(), x(), y(), x());
    }
    Vector<T, 4> wxyy() const {
        return Vector<T, 4>(w(), x(), y(), y());
    }
    Vector<T, 4> wxyz() const {
        return Vector<T, 4>(w(), x(), y(), z());
    }
    Vector<T, 4> wxyw() const {
        return Vector<T, 4>(w(), x(), y(), w());
    }
    Vector<T, 4> wxzx() const {
        return Vector<T, 4>(w(), x(), z(), x());
    }
    Vector<T, 4> wxzy() const {
        return Vector<T, 4>(w(), x(), z(), y());
    }
    Vector<T, 4> wxzz() const {
        return Vector<T, 4>(w(), x(), z(), z());
    }
    Vector<T, 4> wxzw() const {
        return Vector<T, 4>(w(), x(), z(), w());
    }
    Vector<T, 4> wxwx() const {
        return Vector<T, 4>(w(), x(), w(), x());
    }
    Vector<T, 4> wxwy() const {
        return Vector<T, 4>(w(), x(), w(), y());
    }
    Vector<T, 4> wxwz() const {
        return Vector<T, 4>(w(), x(), w(), z());
    }
    Vector<T, 4> wxww() const {
        return Vector<T, 4>(w(), x(), w(), w());
    }
    Vector<T, 4> wyxx() const {
        return Vector<T, 4>(w(), y(), x(), x());
    }
    Vector<T, 4> wyxy() const {
        return Vector<T, 4>(w(), y(), x(), y());
    }
    Vector<T, 4> wyxz() const {
        return Vector<T, 4>(w(), y(), x(), z());
    }
    Vector<T, 4> wyxw() const {
        return Vector<T, 4>(w(), y(), x(), w());
    }
    Vector<T, 4> wyyx() const {
        return Vector<T, 4>(w(), y(), y(), x());
    }
    Vector<T, 4> wyyy() const {
        return Vector<T, 4>(w(), y(), y(), y());
    }
    Vector<T, 4> wyyz() const {
        return Vector<T, 4>(w(), y(), y(), z());
    }
    Vector<T, 4> wyyw() const {
        return Vector<T, 4>(w(), y(), y(), w());
    }
    Vector<T, 4> wyzx() const {
        return Vector<T, 4>(w(), y(), z(), x());
    }
    Vector<T, 4> wyzy() const {
        return Vector<T, 4>(w(), y(), z(), y());
    }
    Vector<T, 4> wyzz() const {
        return Vector<T, 4>(w(), y(), z(), z());
    }
    Vector<T, 4> wyzw() const {
        return Vector<T, 4>(w(), y(), z(), w());
    }
    Vector<T, 4> wywx() const {
        return Vector<T, 4>(w(), y(), w(), x());
    }
    Vector<T, 4> wywy() const {
        return Vector<T, 4>(w(), y(), w(), y());
    }
    Vector<T, 4> wywz() const {
        return Vector<T, 4>(w(), y(), w(), z());
    }
    Vector<T, 4> wyww() const {
        return Vector<T, 4>(w(), y(), w(), w());
    }
    Vector<T, 4> wzxx() const {
        return Vector<T, 4>(w(), z(), x(), x());
    }
    Vector<T, 4> wzxy() const {
        return Vector<T, 4>(w(), z(), x(), y());
    }
    Vector<T, 4> wzxz() const {
        return Vector<T, 4>(w(), z(), x(), z());
    }
    Vector<T, 4> wzxw() const {
        return Vector<T, 4>(w(), z(), x(), w());
    }
    Vector<T, 4> wzyx() const {
        return Vector<T, 4>(w(), z(), y(), x());
    }
    Vector<T, 4> wzyy() const {
        return Vector<T, 4>(w(), z(), y(), y());
    }
    Vector<T, 4> wzyz() const {
        return Vector<T, 4>(w(), z(), y(), z());
    }
    Vector<T, 4> wzyw() const {
        return Vector<T, 4>(w(), z(), y(), w());
    }
    Vector<T, 4> wzzx() const {
        return Vector<T, 4>(w(), z(), z(), x());
    }
    Vector<T, 4> wzzy() const {
        return Vector<T, 4>(w(), z(), z(), y());
    }
    Vector<T, 4> wzzz() const {
        return Vector<T, 4>(w(), z(), z(), z());
    }
    Vector<T, 4> wzzw() const {
        return Vector<T, 4>(w(), z(), z(), w());
    }
    Vector<T, 4> wzwx() const {
        return Vector<T, 4>(w(), z(), w(), x());
    }
    Vector<T, 4> wzwy() const {
        return Vector<T, 4>(w(), z(), w(), y());
    }
    Vector<T, 4> wzwz() const {
        return Vector<T, 4>(w(), z(), w(), z());
    }
    Vector<T, 4> wzww() const {
        return Vector<T, 4>(w(), z(), w(), w());
    }
    Vector<T, 4> wwxx() const {
        return Vector<T, 4>(w(), w(), x(), x());
    }
    Vector<T, 4> wwxy() const {
        return Vector<T, 4>(w(), w(), x(), y());
    }
    Vector<T, 4> wwxz() const {
        return Vector<T, 4>(w(), w(), x(), z());
    }
    Vector<T, 4> wwxw() const {
        return Vector<T, 4>(w(), w(), x(), w());
    }
    Vector<T, 4> wwyx() const {
        return Vector<T, 4>(w(), w(), y(), x());
    }
    Vector<T, 4> wwyy() const {
        return Vector<T, 4>(w(), w(), y(), y());
    }
    Vector<T, 4> wwyz() const {
        return Vector<T, 4>(w(), w(), y(), z());
    }
    Vector<T, 4> wwyw() const {
        return Vector<T, 4>(w(), w(), y(), w());
    }
    Vector<T, 4> wwzx() const {
        return Vector<T, 4>(w(), w(), z(), x());
    }
    Vector<T, 4> wwzy() const {
        return Vector<T, 4>(w(), w(), z(), y());
    }
    Vector<T, 4> wwzz() const {
        return Vector<T, 4>(w(), w(), z(), z());
    }
    Vector<T, 4> wwzw() const {
        return Vector<T, 4>(w(), w(), z(), w());
    }
    Vector<T, 4> wwwx() const {
        return Vector<T, 4>(w(), w(), w(), x());
    }
    Vector<T, 4> wwwy() const {
        return Vector<T, 4>(w(), w(), w(), y());
    }
    Vector<T, 4> wwwz() const {
        return Vector<T, 4>(w(), w(), w(), z());
    }
    Vector<T, 4> wwww() const {
        return Vector<T, 4>(w(), w(), w(), w());
    }
};

template <typename T, std::size_t N>
inline Swizzled_xyzw<T, N> Swizzle_xyzw(Vector<T, N> v) {
    return Swizzled_xyzw<T, N>(v);
}

template <typename T, std::size_t N>
inline Swizzled_xyzw<T, N> Swizzle(Vector<T, N> v) {
    return Swizzled_xyzw<T, N>(v);
}
