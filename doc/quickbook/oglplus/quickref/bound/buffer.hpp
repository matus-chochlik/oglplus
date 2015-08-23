
/*
 *  Automatically generated file, do not edit manually!
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
//[oglplus_object_BoundObjOps_Buffer

template <>
class __BoundObjOps<__tag_Buffer>
{
private:
	typedef typename __ObjectOps_Explicit_Buffer<__tag_ExplicitSel, __tag_Buffer> ExplicitOps;
public:
	typedef typename ExplicitOps::Target Target;

	Target target;

	BoundObjOps(void);

	BoundObjOps(Target init_tgt);
	GLint GetIntParam(
		GLenum query
	) const;

	Boolean Mapped(void) const;

	const BoundObjOps& Resize(
		BufferSize size,
		BufferUsage usage = BufferUsage::StaticDraw
	) const;

	const BoundObjOps& Data(
		const BufferData & data,
		BufferUsage usage = BufferUsage::StaticDraw
	) const;

	const BoundObjOps& RawData(
		BufferSize size,
		const GLvoid * data,
		BufferUsage usage = BufferUsage::StaticDraw
	) const;

	template <typename GLtype>
	const BoundObjOps& Data(
		SizeType count,
		const GLtype * data,
		BufferUsage usage = BufferUsage::StaticDraw
	) const;

	const BoundObjOps& SubData(
		BufferSize offset,
		const BufferData & data
	) const;

	template <typename GLtype>
	const BoundObjOps& SubData(
		BufferSize offset,
		SizeType count,
		const GLtype * data
	) const;

#if GL_VERSION_4_3
	template <typename GLtype>
	const BoundObjOps& ClearData(
		PixelDataInternalFormat internal_format,
		PixelDataFormat format,
		const GLtype * data
	) const;
#endif

#if GL_VERSION_4_3
	template <typename GLtype>
	const BoundObjOps& ClearSubData(
		PixelDataInternalFormat internal_format,
		BufferSize offset,
		BufferSize size,
		PixelDataFormat format,
		const GLtype * data
	) const;
#endif

	const BoundObjOps& Storage(
		const BufferData & data,
		Bitfield< BufferStorageBit > flags
	) const;

#if GL_VERSION_4_4 || GL_ARB_buffer_storage
	const BoundObjOps& Storage(
		BufferSize size,
		const void * data,
		Bitfield< BufferStorageBit > flags
	) const;
#endif

#if GL_VERSION_4_4 || GL_ARB_buffer_storage
	Boolean ImmutableStorage(void) const;
#endif

#if GL_VERSION_4_4 || GL_ARB_buffer_storage
	Bitfield< BufferStorageBit > StorageFlags(void) const;
#endif

#if GL_ARB_sparse_buffer
	const BoundObjOps& PageCommitment(
		BufferSize offset,
		BufferSize size,
		Boolean commit
	) const;
#endif

	SizeType Size(void) const;

	BufferUsage Usage(void) const;

	Bitfield< BufferMapAccess > Access(void) const;

#if GL_NV_shader_buffer_load
	const BoundObjOps& MakeResident(
		AccessSpecifier access
	) const;
#endif

#if GL_NV_shader_buffer_load
	const BoundObjOps& MakeNonResident(void) const;
#endif

#if GL_NV_shader_buffer_load
	BufferGPUAddress GPUAddress(void) const;
#endif


};
//]
