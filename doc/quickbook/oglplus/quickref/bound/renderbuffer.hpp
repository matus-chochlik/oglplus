
/*
 *  Automatically generated file, do not edit manually!
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
//[oglplus_object_BoundObjOps_Renderbuffer

template <>
class __BoundObjOps<__tag_Renderbuffer>
{
private:
	typedef typename __ObjectOps_Explicit_Renderbuffer<__tag_ExplicitSel, __tag_Renderbuffer> ExplicitOps;
public:
	typedef typename ExplicitOps::Target Target;

	Target target;

	BoundObjOps(void);

	BoundObjOps(Target init_tgt);
	GLint GetIntParam(
		GLenum query
	) const;

	const BoundObjOps& Storage(
		PixelDataInternalFormat internalformat,
		SizeType width,
		SizeType height
	) const;

	const BoundObjOps& Storage(
		const images::ImageSpec & image_spec
	) const;

	const BoundObjOps& StorageMultisample(
		SizeType samples,
		PixelDataInternalFormat internalformat,
		SizeType width,
		SizeType height
	) const;

	SizeType Width(void) const;

	SizeType Height(void) const;

	SizeType RedSize(void) const;

	SizeType GreenSize(void) const;

	SizeType BlueSize(void) const;

	SizeType AlphaSize(void) const;

	SizeType DepthSize(void) const;

	SizeType StencilSize(void) const;

	SizeType Samples(void) const;

	PixelDataInternalFormat InternalFormat(void) const;


};
//]
