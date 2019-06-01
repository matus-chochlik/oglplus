/**
 *  @file oglplus/shapes/torus.hpp
 *  @brief Torus builder
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_SHAPES_TORUS_1107121519_HPP
#define OGLPLUS_SHAPES_TORUS_1107121519_HPP

#include <oglplus/face_mode.hpp>
#include <oglplus/shapes/draw.hpp>

#include <oglplus/shapes/vert_attr_info.hpp>

#include <oglplus/math/constants.hpp>
#include <oglplus/math/sphere.hpp>

namespace oglplus {
namespace shapes {

/// Class providing vertex attributes and instructions for rendering of a Torus
class Torus
  : public DrawingInstructionWriter
  , public DrawMode {
private:
    double _radius_out, _radius_in;
    unsigned _sections, _rings;

public:
    /// Creates a torus with unit radius centered at the origin
    Torus()
      : _radius_out(1.0)
      , _radius_in(0.5)
      , _sections(36)
      , _rings(24) {}

    /// Creates a torus with unit radius centered at the origin
    Torus(double rad_out, double rad_in, unsigned sects, unsigned rings)
      : _radius_out(rad_out)
      , _radius_in(rad_in)
      , _sections(sects)
      , _rings(rings) {}

    /// Returns the winding direction of faces
    FaceOrientation FaceWinding() const {
        return FaceOrientation::CCW;
    }

    /// Makes vertex coordinates and returns number of values per vertex
    template <typename T>
    GLuint Positions(std::vector<T>& dest) const {
        dest.resize((_rings + 1) * (_sections + 1) * 3);
        unsigned k = 0;
        //
        double r_step = (math::TwoPi()) / double(_rings);
        double s_step = (math::TwoPi()) / double(_sections);
        double r1 = _radius_in;
        double r2 = _radius_out - _radius_in;

        for(unsigned r = 0; r != (_rings + 1); ++r) {
            double vx = std::cos(r * r_step);
            double vz = -std::sin(r * r_step);
            for(unsigned s = 0; s != (_sections + 1); ++s) {
                double vr = std::cos(s * s_step);
                double vy = std::sin(s * s_step);
                dest[k++] = T(vx * (r1 + r2 * (1.0 + vr)));
                dest[k++] = T(vy * r2);
                dest[k++] = T(vz * (r1 + r2 * (1.0 + vr)));
            }
        }
        assert(k == dest.size());
        return 3;
    }

    /// Makes vertex normals and returns number of values per vertex
    template <typename T>
    GLuint Normals(std::vector<T>& dest) const {
        dest.resize((_rings + 1) * (_sections + 1) * 3);
        unsigned k = 0;
        //
        double r_step = (math::TwoPi()) / double(_rings);
        double s_step = (math::TwoPi()) / double(_sections);

        for(unsigned r = 0; r != (_rings + 1); ++r) {
            double nx = std::cos(r * r_step);
            double nz = -std::sin(r * r_step);
            for(unsigned s = 0; s != (_sections + 1); ++s) {
                double nr = std::cos(s * s_step);
                double ny = std::sin(s * s_step);
                dest[k++] = T(nx * nr);
                dest[k++] = T(ny);
                dest[k++] = T(nz * nr);
            }
        }
        assert(k == dest.size());
        return 3;
    }

    /// Makes vertex tangents and returns number of values per vertex
    template <typename T>
    GLuint Tangents(std::vector<T>& dest) const {
        dest.resize((_rings + 1) * (_sections + 1) * 3);
        unsigned k = 0;
        //
        double r_step = (math::TwoPi()) / double(_rings);

        for(unsigned r = 0; r != (_rings + 1); ++r) {
            double tx = -std::sin(r * r_step);
            double tz = -std::cos(r * r_step);
            for(unsigned s = 0; s != (_sections + 1); ++s) {
                dest[k++] = T(tx);
                dest[k++] = T(0);
                dest[k++] = T(tz);
            }
        }
        assert(k == dest.size());
        return 3;
    }

    /// Makes vertex bi-tangents and returns number of values per vertex
    template <typename T>
    GLuint Bitangents(std::vector<T>& dest) const {
        dest.resize((_rings + 1) * (_sections + 1) * 3);
        unsigned k = 0;
        //
        double r_step = (math::TwoPi()) / double(_rings);
        double s_step = (math::TwoPi()) / double(_sections);

        double ty = 0.0;
        for(unsigned r = 0; r != (_rings + 1); ++r) {
            double tx = -std::sin(r * r_step);
            double tz = -std::cos(r * r_step);

            for(unsigned s = 0; s != (_sections + 1); ++s) {
                double ny = std::sin(s * s_step);
                double nr = std::cos(s * s_step);
                double nx = -tz * nr;
                double nz = tx * nr;

                dest[k++] = T(ny * tz - nz * ty);
                dest[k++] = T(nz * tx - nx * tz);
                dest[k++] = T(nx * ty - ny * tx);
            }
        }
        assert(k == dest.size());
        return 3;
    }

    /// Makes texture coordinates and returns number of values per vertex
    template <typename T>
    GLuint TexCoordinates(std::vector<T>& dest) const {
        dest.resize((_rings + 1) * (_sections + 1) * 2);
        unsigned k = 0;
        //
        double r_step = 1.0 / double(_rings);
        double s_step = 1.0 / double(_sections);

        for(unsigned r = 0; r != (_rings + 1); ++r) {
            double u = r * r_step;
            for(unsigned s = 0; s != (_sections + 1); ++s) {
                double v = s * s_step;
                dest[k++] = T(u);
                dest[k++] = T(v);
            }
        }
        assert(k == dest.size());
        return 2;
    }

#if OGLPLUS_DOCUMENTATION_ONLY
    /// Vertex attribute information for this shape builder
    /** Torus provides build functions for the following named
     *  vertex attributes:
     *  - "Position" the vertex positions (Positions)
     *  - "Normal" the vertex normal vectors (Normals)
     *  - "Tangent" the vertex tangent vector (Tangents)
     *  - "Bitangent" the vertex bi-tangent vector (Bitangents)
     *  - "TexCoord" the ST texture coordinates (TexCoordinates)
     */
    using VertexAttribs = VertexAttribsInfo<Torus>;
#else
    using VertexAttribs = VertexAttribsInfo<
      Torus,
      std::tuple<
        VertexPositionsTag,
        VertexNormalsTag,
        VertexTangentsTag,
        VertexBitangentsTag,
        VertexTexCoordinatesTag>>;
#endif

    /// Queries the bounding sphere coordinates and dimensions
    template <typename T>
    void BoundingSphere(oglplus::Sphere<T>& bounding_sphere) const {
        bounding_sphere = oglplus::Sphere<T>(T(0), T(0), T(0), T(_radius_out));
    }

    /// The type of index container returned by Indices()
    using IndexArray = std::vector<GLuint>;

    /// Returns element indices that are used with the drawing instructions
    IndexArray Indices(Default = Default()) const;

    /// Returns element indices that are used with the drawing instructions
    IndexArray Indices(Quads) const;

    /// Returns element indices that are used with the drawing instructions
    IndexArray Indices(WithAdjacency) const;

    /// Returns the instructions for rendering
    DrawingInstructions Instructions(Default = Default()) const;

    /// Returns the instructions for rendering
    DrawingInstructions Instructions(Quads) const;

    /// Returns the instructions for rendering
    DrawingInstructions Instructions(WithAdjacency) const;
};

} // namespace shapes
} // namespace oglplus

#if !OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)
#include <oglplus/shapes/torus.ipp>
#endif // OGLPLUS_LINK_LIBRARY

#endif // include guard
