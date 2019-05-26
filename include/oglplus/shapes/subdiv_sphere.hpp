/**
 *  @file oglplus/shapes/subdiv_sphere.hpp
 *  @brief SubdivSphere builder
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_SHAPES_SUBDIV_SPHERE_1309171555_HPP
#define OGLPLUS_SHAPES_SUBDIV_SPHERE_1309171555_HPP

#include <oglplus/face_mode.hpp>
#include <oglplus/shapes/draw.hpp>

#include <oglplus/math/sphere.hpp>
#include <oglplus/math/vector.hpp>
#include <oglplus/shapes/vert_attr_info.hpp>

#include <map>

namespace oglplus {
namespace shapes {

OGLPLUS_ENUM_CLASS_BEGIN(SubdivSphereInitialShape, GLuint)
OGLPLUS_ENUM_CLASS_VALUE(Icosahedron, 0)
OGLPLUS_ENUM_CLASS_COMMA
OGLPLUS_ENUM_CLASS_VALUE(Octohedron, 1)
OGLPLUS_ENUM_CLASS_COMMA
OGLPLUS_ENUM_CLASS_VALUE(Tetrahedron, 2)
OGLPLUS_ENUM_CLASS_END(SubdivSphereInitialShape)

/// Class providing vertex attributes and instructions for drawing of a sphere
class SimpleSubdivSphere
  : public DrawingInstructionWriter
  , public DrawMode {
private:
    GLuint _subdivs;
    std::vector<double> _positions;
    std::vector<GLuint> _indices;

    using _edge = std::pair<GLuint, GLuint>;
    std::map<_edge, GLuint> _midpoints;

    GLuint _midpoint(GLuint ia, GLuint ib);
    void _subdivide(GLuint ia, GLuint ib, GLuint ic, GLuint levels);
    void _make_face(GLuint ia, GLuint ib, GLuint ic, GLuint levels);

    void _init_icosah();
    void _init_tetrah();
    void _init_octoh();

public:
    using InitialShape = SubdivSphereInitialShape;

    SimpleSubdivSphere()
      : _subdivs(2) {
        _init_icosah();
    }

    SimpleSubdivSphere(GLuint subdivs)
      : _subdivs(subdivs) {
        _init_icosah();
    }

    SimpleSubdivSphere(GLuint subdivs, InitialShape init_shape);

    /// Returns the winding direction of faces
    FaceOrientation FaceWinding() const {
        return FaceOrientation::CCW;
    }

    using VertexAttribFunc =
      GLuint (SimpleSubdivSphere::*)(std::vector<GLfloat>&) const;

    /// Makes the positions and returns the number of values per vertex
    template <typename T>
    GLuint Positions(std::vector<T>& dest) const {
        dest.assign(_positions.begin(), _positions.end());
        return 3;
    }

#if OGLPLUS_DOCUMENTATION_ONLY
    /// Vertex attribute information for this shape builder
    /** SubdivSphere provides build functions for the following named
     *  vertex attributes:
     *  - "Position" the vertex positions (Positions)
     */
    using VertexAttribs = VertexAttribsInfo<SubdivSphere>;
#else
    using VertexAttribs =
      VertexAttribsInfo<SimpleSubdivSphere, std::tuple<VertexPositionsTag>>;
#endif

    /// Queries the bounding sphere coordinates and dimensions
    template <typename T>
    void BoundingSphere(oglplus::Sphere<T>& bounding_sphere) const {
        bounding_sphere = oglplus::Sphere<T>(T(0), T(0), T(0), T(1));
    }

    /// The type of the index container returned by Indices()
    using IndexArray = std::vector<GLuint>;

    /// Returns element indices that are used with the drawing instructions
    IndexArray Indices(Default = Default()) const {
        return IndexArray(_indices.begin(), _indices.end());
    }

    DrawingInstructions Instructions(PrimitiveType mode) const;

    /// Returns the instructions for rendering of faces
    DrawingInstructions Instructions(Default = Default()) const {
        return Instructions(PrimitiveType::Triangles);
    }
};

} // namespace shapes
} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/shapes/subdiv_sphere.ipp>
#endif // OGLPLUS_LINK_LIBRARY

#endif // include guard
