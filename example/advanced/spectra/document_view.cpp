/*
 *  .file advanced/spectra/document_view.cpp
 *  .brief Implements the document view class.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "document_view.hpp"

#include <cmath>

SpectraDocumentView::SpectraDocumentView(void)
 : width(64)
 , height(64)
 , camera_distance(5.0f)
 , target_x(0.0f)
 , target_z(0.0f)
 , camera_azimuth(oglplus::Degrees(35))
 , camera_elevation(oglplus::Degrees(35))
 , camera_xfov(oglplus::Degrees(70))
{
	RecalcProjection();
	RecalcCamera();
}

void SpectraDocumentView::Reshape(GLuint w, GLuint h)
{
	width = w;
	height = h;
	RecalcProjection();
}

oglplus::Vec3f SpectraDocumentView::PickOnGround(GLint x, GLint y)
{
	GLfloat u = -1.0f+GLfloat(2*x)/GLfloat(width);
	GLfloat v = +1.0f-GLfloat(2*y)/GLfloat(height);
	GLfloat w = 1.0f;

	oglplus::Vec4f ndc(u, v, w, 1.0f);

	oglplus::Vec4f wsc = inv_view_matrix * ndc;

	oglplus::Vec3f cam = camera_matrix.Position();
	oglplus::Vec3f ray = Normalized(wsc.xyz()/wsc.w() - cam);

	if(ray.y() != 0)
	{
		GLfloat t = -cam.y()/ray.y();
		return cam + ray * t;
	}
	return ray * camera_distance;
}

void SpectraDocumentView::Slide(GLint new_x, GLint new_y, GLint old_x, GLint old_y)
{
	oglplus::Vec3f dir = PickOnGround(new_x, new_y)-PickOnGround(old_x, old_y);
	target_x -= dir.x();
	if(target_x < -1) target_x = -1;
	if(target_x > 10) target_x = 10;
	target_z -= dir.z();
	if(target_z < -1) target_z = -1;
	if(target_z >  1) target_z =  1;
	RecalcCamera();
}

void SpectraDocumentView::Orbit(GLint new_x, GLint new_y, GLint old_x, GLint old_y)
{
	GLfloat dx = (new_x-old_x)/GLfloat(width);
	GLfloat dy = (new_y-old_y)/GLfloat(height);

	oglplus::Anglef fc = oglplus::FullCircle();
	oglplus::Anglef ra = oglplus::RightAngle();
	camera_elevation += 2*dy*ra;

	if(camera_elevation > ra)
		camera_elevation = ra;
	if(camera_elevation <-ra)
		camera_elevation =-ra;

	if(dx != 0)
	{
		oglplus::Vec3f ng = Normalized(PickOnGround(new_x, new_y));
		oglplus::Vec3f og = Normalized(PickOnGround(old_x, old_y));

		camera_azimuth -= oglplus::Radians(
			std::atan2(-ng.z(), ng.x())-
			std::atan2(-og.z(), og.x())
		);
		while(camera_azimuth > fc)
			camera_azimuth -= fc;
		while(camera_azimuth < -fc)
			camera_azimuth += fc;
	}

	RecalcCamera();
}

void SpectraDocumentView::RecalcProjection(void)
{
	projection_matrix = oglplus::CamMatrixf::PerspectiveX(
		camera_xfov,
		double(width)/height,
		1.0f,
		100.0f
	);
	view_matrix = projection_matrix * camera_matrix;
	inv_view_matrix = Inverse(view_matrix);
}

void SpectraDocumentView::RecalcCamera(void)
{
	camera_matrix = oglplus::CamMatrixf::Orbiting(
		oglplus::Vec3f(target_x, 0.0f, target_z),
		camera_distance,
		camera_azimuth,
		camera_elevation
	);
	view_matrix = projection_matrix * camera_matrix;
	inv_view_matrix = Inverse(view_matrix);
}

const oglplus::Mat4f& SpectraDocumentView::ProjectionMatrix(void) const
{
	return projection_matrix;
}

const oglplus::CamMatrixf& SpectraDocumentView::CameraMatrix(void) const
{
	return camera_matrix;
}

