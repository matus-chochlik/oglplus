/*
 *  Automatically generated file, do not edit manually!
 *
 *  Copyright 2010-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
//[oglplus_object_BoundObjOps_Renderbuffer

template <>
class __BoundObjOps<__tag_Renderbuffer> {
private:
    using ExplicitOps = typename __ObjectOps_Explicit_Renderbuffer<
      __tag_ExplicitSel,
      __tag_Renderbuffer>;

public:
    using Target = typename ExplicitOps::Target;

    Target target;

    BoundObjOps();

    BoundObjOps(Target init_tgt);
    GLint GetIntParam(GLenum query) const;

    const BoundObjOps& Storage(
      __PixelDataInternalFormat internalformat,
      __SizeType width,
      __SizeType height) const;

    const BoundObjOps& Storage(const __images_ImageSpec& image_spec) const;

    const BoundObjOps& StorageMultisample(
      __SizeType samples,
      __PixelDataInternalFormat internalformat,
      __SizeType width,
      __SizeType height) const;

    __SizeType Width() const;

    __SizeType Height() const;

    __SizeType RedSize() const;

    __SizeType GreenSize() const;

    __SizeType BlueSize() const;

    __SizeType AlphaSize() const;

    __SizeType DepthSize() const;

    __SizeType StencilSize() const;

    __SizeType Samples() const;

    __PixelDataInternalFormat InternalFormat() const;
};
//]
