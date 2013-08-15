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
#include <oglplus/shapes/twisted_torus.hpp>
#include <oglplus/shapes/obj_mesh.hpp>

#include <oglplus/opt/resources.hpp>
#include <oglplus/opt/list_init.hpp>

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

		//oglplus::shapes::Cube s;
		//oglplus::shapes::Plane s(3, 3);
		//oglplus::shapes::Screen s;
		//oglplus::shapes::Sphere s;
		//oglplus::shapes::TwistedTorus s;
		oglplus::ResourceFile input("models", "arrow_z", ".obj");
		oglplus::shapes::ObjMesh s(
			input,
			oglplus::shapes::ObjMesh::LoadingOptions(false).Normals().Materials()
		);
		oglplus::shapes::ShapeAnalyzer a(s);

		std::cout << "graph Shape {" << std::endl;

		std::cout << "\tnode [shape=box];" << std::endl;
		for(GLuint f=0; f!=a.FaceCount(); ++f)
		{
			std::cout
				<< "\tf" << f
				<< " [label=\"" << f << "\"]"
				<< ";" << std::endl;
		}

		std::cout
			<< "\tnode ["
			<< "shape=circle,"
			<< "fixedsize=true,"
			<< "width=0.3,"
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
