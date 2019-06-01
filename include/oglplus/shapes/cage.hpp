/**
 *  @file oglplus/shapes/cage.hpp
 *  @brief Cage builder
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_SHAPES_CAGE_1107121519_HPP
#define OGLPLUS_SHAPES_CAGE_1107121519_HPP

#include <oglplus/face_mode.hpp>
#include <oglplus/shapes/draw.hpp>

#include <oglplus/math/matrix.hpp>
#include <oglplus/math/sphere.hpp>
#include <oglplus/shapes/vert_attr_info.hpp>

namespace oglplus {
namespace shapes {

/// Class providing vertex attributes and instructions for rendering of a cage
class Cage
  : public DrawingInstructionWriter
  , public DrawMode {
private:
    Vector<double, 3> _size;
    Vector<double, 3> _barw;
    Vector<double, 3> _divs;

    static const Matrix<double, 3, 3>& _face_mat(GLuint face);

    double _face_size(GLuint face, GLuint axis) const {
        return std::fabs(Dot(_face_mat(face).Row(axis), _size));
    }

    double _face_barw(GLuint face, GLuint axis) const {
        return std::fabs(Dot(_face_mat(face).Row(axis), _barw));
    }

    GLuint _face_divs(GLuint face, GLuint axis) const {
        return GLuint(std::fabs(Dot(_face_mat(face).Row(axis), _divs)));
    }

    static const Vector<double, 3> _face_vec(
      GLuint face, const Vector<double, 3> vec) {
        return _face_mat(face) * vec;
    }

    template <typename Iter>
    static Iter _write(Iter iter, const Vector<double, 3>& vec) {
        *iter++ = GLfloat(vec.x());
        *iter++ = GLfloat(vec.y());
        *iter++ = GLfloat(vec.z());
        return iter;
    }

    GLuint _vert_count() const;

    // primitive-restart-index
    GLuint _pri() const {
        return _vert_count();
    }

    GLuint _index_count() const;

public:
    /// Constructs a unit cage centered at the origin
    Cage()
      : _size(1, 1, 1)
      , _barw(0.15, 0.15, 0.15)
      , _divs(4, 4, 4) {}

    /// Constructs a cage with width, height, depth
    Cage(
      double xs,
      double ys,
      double zs,
      double xb,
      double yb,
      double zb,
      GLuint xd,
      GLuint yd,
      GLuint zd)
      : _size(xs, ys, zs)
      , _barw(xb, yb, zb)
      , _divs(xd, yd, zd) {
        assert(xs > 0.0);
        assert(ys > 0.0);
        assert(zs > 0.0);

        assert(xd > 0);
        assert(yd > 0);
        assert(zd > 0);

        assert(xs > xb * (xd - 1));
        assert(ys > yb * (yd - 1));
        assert(zs > zb * (zd - 1));
    }

    /// Returns the winding direction of faces
    FaceOrientation FaceWinding() const {
        return FaceOrientation::CW;
    }

    using VertexAttribFunc = GLuint (Cage::*)(std::vector<GLfloat>&) const;

    std::vector<GLfloat> _positions() const;

    GLuint Positions(std::vector<GLfloat>& dest) const {
        dest = _positions();
        return 3;
    }

    /// Makes the vertices and returns the number of values per vertex
    template <typename T>
    GLuint Positions(std::vector<T>& dest) const {
        auto p = _positions();
        dest.assign(p.begin(), p.end());
        return 3;
    }

    std::vector<GLfloat> _normals() const;

    GLuint Normals(std::vector<GLfloat>& dest) const {
        dest = _normals();
        return 3;
    }

    /// Makes the normals and returns the number of values per vertex
    template <typename T>
    GLuint Normals(std::vector<T>& dest) const {
        auto n = _normals();
        dest.assign(n.begin(), n.end());
        return 3;
    }

    std::vector<GLfloat> _tangents() const;

    GLuint Tangents(std::vector<GLfloat>& dest) const {
        dest = _tangents();
        return 3;
    }

    /// Makes the tangents and returns the number of values per vertex
    template <typename T>
    GLuint Tangents(std::vector<T>& dest) const {
        auto t = _tangents();
        dest.assign(t.begin(), t.end());
        return 3;
    }

    std::vector<GLfloat> _tex_coords() const;

    GLuint TexCoordinates(std::vector<GLfloat>& dest) const {
        dest = _tex_coords();
        return 3;
    }

    /// Makes the texture coordinates and returns the number of values per
    /// vertex
    template <typename T>
    GLuint TexCoordinates(std::vector<T>& dest) const {
        auto t = _tex_coords();
        dest.assign(t.begin(), t.end());
        return 3;
    }

#if OGLPLUS_DOCUMENTATION_ONLY
    /// Vertex attribute information for this shape builder
    /** Cage provides build functions for the following named
     *  vertex attributes:
     *  - "Position" the vertex positions (Positions)
     *  - "Normal" the vertex normal vectors (Normals)
     *  - "Tangent" the vertex tangent vector (Tangents)
     *  - "TexCoord" the ST texture coordinates (TexCoordinates)
     */
    using VertexAttribs = VertexAttribsInfo<Cage>;
#else
    using VertexAttribs = VertexAttribsInfo<
      Cage,
      std::tuple<
        VertexPositionsTag,
        VertexNormalsTag,
        VertexTangentsTag,
        VertexTexCoordinatesTag>>;
#endif

    /// Queries the bounding sphere coordinates and dimensions
    template <typename T>
    void BoundingSphere(oglplus::Sphere<T>& bounding_sphere) const {
        bounding_sphere =
          oglplus::Sphere<T>(T(0), T(0), T(0), T(Length(_size)));
    }

    /// The type of the index container returned by Indices()
    using IndexArray = std::vector<GLuint>;

    /// Returns element indices that are used with the drawing instructions
    IndexArray Indices(Default = Default()) const;

    /// Returns the instructions for rendering of faces
    DrawingInstructions Instructions(Default = Default()) const;
};

} // namespace shapes
} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/shapes/cage.ipp>
#endif

#endif // include guard
