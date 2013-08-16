/**
 *  @example standalone/000_test.cpp
 *  @brief Devel/test of the mesh analyzer tool
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */
#include <cassert>
#include <iostream>

#include <GL/glew.h>
#include <GL/glut.h>

#include <iostream>

#include <oglplus/shapes/analyzer.hpp>

#include <oglplus/shapes/cube.hpp>
#include <oglplus/shapes/plane.hpp>
#include <oglplus/shapes/screen.hpp>
#include <oglplus/shapes/sphere.hpp>
#include <oglplus/shapes/icosahedron.hpp>
#include <oglplus/shapes/twisted_torus.hpp>
#include <oglplus/shapes/obj_mesh.hpp>

#include <oglplus/opt/resources.hpp>
#include <oglplus/opt/list_init.hpp>

#include <oglplus/matrix.hpp>

namespace oglplus {
namespace shapes {


} // namespace shapes
} // namespace oglplus

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100,100);
	glutCreateWindow("OGLplus+GLUT+GLEW");

	if(glewInit() == GLEW_OK) try
	{
		glGetError();

		using namespace oglplus;

		//shapes::Cube s;
		shapes::Plane s(3, 3);
		//shapes::Screen s;
		//shapes::Sphere s;
		//shapes::Icosahedron s;
		//shapes::TwistedTorus s;
/*
		ResourceFile input("models", "arrow_z", ".obj");
		shapes::ObjMesh s(
			input,
			shapes::ObjMesh::LoadingOptions(false).Normals().Materials()
		);
*/
		shapes::ShapeAnalyzer a(s);

		std::cout << "graph Shape {" << std::endl;

		std::cout << "\tsplines=true;" << std::endl;
		std::cout << "\tnode [shape=box];" << std::endl;

		auto tm = CamMatrixd::PerspectiveX(Angle<double>::Degrees(80), 1, 1, 20)*
			CamMatrixd::LookingAt(Vec3d(0, 10, 10), Vec3d());

		for(GLuint f=0; f!=a.FaceCount(); ++f)
		{
			auto face = a.Face(f);
			Vec4d v0 = face.Vert(0).MainAttrib();
			Vec4d v1 = face.Vert(1).MainAttrib();
			Vec4d v2 = face.Vert(2).MainAttrib();

			Vec4d v = (v0+v1+v2)/3.0;
			std::cout
				<< "\tf" << f
				<< " [label=\"" << f
				<< "\", pos=\""
				<< v.x()*8 << "," << v.z()*8
				<< "\", pin=true]"
				<< ";" << std::endl;
		}

		std::cout
			<< "\tnode ["
			<< "shape=circle,"
			<< "style=filled,"
			<< "fillcolor=\"#00FF00\""
			<< "];" << std::endl;
		for(GLuint f=0; f!=a.FaceCount(); ++f)
		{
			auto face = a.Face(f);
			for(GLuint e=0; e!=face.Arity(); ++e)
			{
				std::cout
					<< "\tf" << f
					<< "e" << e
					<< " [label=\"" << e
					<< "\"];" << std::endl;
				std::cout
					<< "\tf" << f
					<< " -- "
					<< "f" << f
					<< "e" << e
					<< ";" << std::endl;
			}
		}

		for(GLuint f=0; f!=a.FaceCount(); ++f)
		{
			auto face = a.Face(f);
			for(GLuint e=0; e!=face.Arity(); ++e)
			{
				auto edge = face.Edge(e);
				if(edge.HasAdjacentEdge())
				{
					auto adje = edge.AdjacentEdge();
					GLuint ae = adje.Index();
					GLuint af = adje.Face().Index();

					if(f < af)
					{
						std::cout
							<< "\tf" << f
							<< "e" << e
							<< " -- f" << af
							<< "e" << ae
							<< std::endl;
					}
				}
			}
		}
		std::cout << "\toverlap=false;" << std::endl;
		std::cout << "}" << std::endl;

		return 0;
	}
	catch(oglplus::Error& err)
	{
		std::cerr <<
			"Error (in " << err.GLSymbol() << ", " <<
			err.ClassName() << ": '" <<
			err.ObjectDescription() << "'): " <<
			err.what() <<
			" [" << err.File() << ":" << err.Line() << "] ";
		std::cerr << std::endl;
		err.Cleanup();
	}
	return 1;
}
