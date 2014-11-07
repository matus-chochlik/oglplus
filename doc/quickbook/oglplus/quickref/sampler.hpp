/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_sampler_common
namespace oglplus {

template <>
class __ObjCommonOps<__tag_Sampler>
 : public __SamplerName
{
public:
	typedef __TextureUnitSelector Target; /*<
	Sampler bind target.
	>*/

	static __SamplerName Binding(Target target); /*<
	Returns the sampler currently bound to the specified [^target].
	See [glfunc GetIntegerv].
	>*/
	static void Bind(Target target, __SamplerName sampler); /*<
	Binds the specified [^sampler] to the specified [^target].
	See [glfunc BindSampler].
	>*/

	void Bind(Target target) const; /*<
	Binds [^this] sampler to the specified [^target].
	See [glfunc BindSampler].
	>*/
};
//]
//[oglplus_sampler_zero
template <>
class __ObjZeroOps<__tag_DirectState, __tag_Sampler>
 : public __ObjCommonOps<__tag_Sampler>
{
public: /*<
There are no operations that can work explicitly on sampler
object zero besides binding, so this class just inherits from
the common sampler operations wrapper.
>*/
};
//]
//[oglplus_sampler_1
template <>
class __ObjectOps<__tag_DirectState, __tag_Sampler>
 : public __ObjZeroOps<__tag_DirectState, __tag_Sampler>
{
public:
	__Vector<GLfloat, 4> BorderColor(TypeTag<GLfloat>) const;

	void BorderColor(__Vector<GLfloat, 4> color)

// TODO
};

} // namespace oglplus
//]

