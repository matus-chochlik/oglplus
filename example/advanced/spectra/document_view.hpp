/*
 *  .file advanced/spectra/document_view.hpp
 *  .brief Declares the document view class.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_EXAMPLE_SPECTRA_DOCUMENT_VIEW_HPP
#define OGLPLUS_EXAMPLE_SPECTRA_DOCUMENT_VIEW_HPP

#include <oglplus/gl.hpp>
#include <oglplus/matrix.hpp>
#include <oglplus/vector.hpp>
#include <oglplus/angle.hpp>

struct SpectraDocumentView
{
private:
	GLuint width;
	GLuint height;
	GLfloat camera_distance;
	GLfloat target_x, target_z;
	oglplus::Anglef camera_azimuth;
	oglplus::Anglef camera_elevation;
	oglplus::Anglef camera_xfov;

	oglplus::CamMatrixf camera_matrix;
	oglplus::Mat4f projection_matrix;
	oglplus::Mat4f view_matrix, inv_view_matrix;

	void RecalcProjection(void);
	void RecalcCamera(void);
public:
	SpectraDocumentView(void);

	GLuint Width(void) const { return width; }
	GLuint Height(void) const { return height; }

	void Reshape(GLuint w, GLuint h);

	oglplus::Vec3f PickOnGround(GLint x, GLint y);

	void Slide(GLint new_x, GLint new_y, GLint old_x, GLint old_y);
	void Orbit(GLint new_x, GLint new_y, GLint old_x, GLint old_y);

	const oglplus::Mat4f& ProjectionMatrix(void) const;

	const oglplus::CamMatrixf& CameraMatrix(void) const;
};

#endif // include guard
