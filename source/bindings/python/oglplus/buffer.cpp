/*
 *  .file oglplus/buffer.cpp
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/gl.hpp>
#include <oglplus/buffer.hpp>

#include <boost/python.hpp>

template <typename T>
struct oglplus_py_BufferOps_TypedMap_wrapper
{
	static T At(const oglplus::BufferOps::TypedMap<T>& typed_map, GLuint index)
	{
		return typed_map.At(index);
	}

	static void Set(const oglplus::BufferOps::TypedMap<T>& typed_map, GLuint index, T value)
	{
		typed_map.At(index) = value;
	}
};

template <typename T>
void oglplus_py_export_BufferOps_TypedMap(oglplus::BufferOps::TypedMap<T>*, const char* name)
{
	namespace bpy = ::boost::python;
	using namespace oglplus;

	bpy::class_<
		BufferOps::TypedMap<T>,
		boost::noncopyable
	>(name, bpy::no_init)
		.def(bpy::init<BufferTarget, BufferMapAccess>())
		.def(bpy::init<BufferTarget, GLintptr, GLsizeiptr, BufferMapAccess>())
		.def("Size", &BufferOps::TypedMap<T>::Size)
		.def("Count", &BufferOps::TypedMap<T>::Count)
		.def("At", &oglplus_py_BufferOps_TypedMap_wrapper<T>::At)
		.def("Set", &oglplus_py_BufferOps_TypedMap_wrapper<T>::Set)
	;
}

void oglplus_py_Buffer(void)
{
	namespace bpy = ::boost::python;
	using namespace oglplus;

	oglplus_py_export_BufferOps_TypedMap((BufferOps::Map*)0, "Buffer::Map");
	oglplus_py_export_BufferOps_TypedMap((BufferOps::TypedMap<GLfloat>*)0, "Buffer::FloatMap");
	oglplus_py_export_BufferOps_TypedMap((BufferOps::TypedMap<GLuint>*)0, "Buffer::UIntMap");
	oglplus_py_export_BufferOps_TypedMap((BufferOps::TypedMap<GLint>*)0, "Buffer::IntMap");

	bpy::class_<BufferOps>("BufferOps", bpy::no_init)
		.def("Mapped", &BufferOps::Mapped)
		.def("Bind", &BufferOps::Bind)
		.def("Unbind", &BufferOps::Unbind).staticmethod("Unbind")
		.def("BindBase", &BufferOps::BindBase)
		.def("UnbindBase", &BufferOps::BindBase).staticmethod("UnbindBase")
		.def("BindRange", &BufferOps::BindRange)
		.def("Data", (void (*)(
			BufferTarget,
			GLsizei,
			const GLfloat*,
			BufferUsage
		))&BufferOps::Data)
		.def("Data", (void (*)(
			BufferTarget,
			GLsizei,
			const GLuint*,
			BufferUsage
		))&BufferOps::Data)
		.def("Data", (void (*)(
			BufferTarget,
			GLsizei,
			const GLint*,
			BufferUsage
		))&BufferOps::Data)
		.staticmethod("Data")
		.def("Data", (void (*)(
			BufferTarget,
			const std::vector<GLfloat>&,
			BufferUsage
		))&BufferOps::Data)
		.def("Data", (void (*)(
			BufferTarget,
			const std::vector<GLuint>&,
			BufferUsage
		))&BufferOps::Data)
		.def("Data", (void (*)(
			BufferTarget,
			const std::vector<GLint>&,
			BufferUsage
		))&BufferOps::Data)
		.staticmethod("Data")
		.def("SubData", (void (*)(
			BufferTarget,
			GLintptr,
			GLsizei,
			const GLfloat*
		))&BufferOps::SubData)
		.def("SubData", (void (*)(
			BufferTarget,
			GLintptr,
			GLsizei,
			const GLuint*
		))&BufferOps::SubData)
		.def("SubData", (void (*)(
			BufferTarget,
			GLintptr,
			GLsizei,
			const GLint*
		))&BufferOps::SubData)
		.def("SubData", (void (*)(
			BufferTarget,
			GLintptr,
			const std::vector<GLfloat>&
		))&BufferOps::SubData)
		.def("SubData", (void (*)(
			BufferTarget,
			GLintptr,
			const std::vector<GLuint>&
		))&BufferOps::SubData)
		.def("SubData", (void (*)(
			BufferTarget,
			GLintptr,
			const std::vector<GLint>&
		))&BufferOps::SubData)
		.staticmethod("SubData")
		.def("Size", &BufferOps::Size).staticmethod("Size")
		.def("Usage", &BufferOps::Usage).staticmethod("Usage")
		.def("Access", &BufferOps::Access).staticmethod("Access")
	;

	bpy::class_<
		Buffer,
		bpy::bases<BufferOps>,
		boost::noncopyable
	>("Buffer", bpy::init<>())
	;
}

