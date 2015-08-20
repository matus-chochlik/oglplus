/*
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_client_CurrentObjects1
namespace client {

class CurrentObjects
{
private:
	template <typename __ObjTag>
	struct CurrentObject
	{
		template <typename __ObjBindingOps<__ObjTag>::Target ObjTarget>
		class WithTarget
		 : public __SettingStack<GLuint, ...> /*<
		Stack of unwrapped object names.
		>*/
		 , public __BoundObjOps<__ObjTag> /*<
		This class has the same interface as [^BoundObjOps] for the objecgt
		type specified by [^ObjTag].
		>*/
		{
			WithTarget(void);

			ObjectName<ObjTag> Get(void) const
			noexcept;

			operator ObjectName<ObjTag> (void) const
			noexcept;

			typedef __SettingHolder<GLuint, ...> Holder;

			Holder Push(__ObjectName<__ObjTag> obj); /*<
			Unwraps the object name, binds it to [^ObjTarget]
			and pushes it onto the stack.
			>*/

			void Bind(__ObjectName<__ObjTag> obj); /*<
			Unwraps the object name, binds it to [^ObjTarget]
			and calls __SettingStack::Set.
			>*/
		};
	};

	template <typename __ObjTag>
	class CurrentObjectsWithTarget /*<
	Set of stacks of objects names the top of which is currently bound
	to a named binding point.
	>*/
	 : public __enums_EnumToClass<
		__Nothing,
		typename __ObjBindingOps<__ObjTag>::Target,
		CurrentObject<__ObjTag>::template WithTarget
	>
	{ };
public:
	CurrentObjectsWithTarget<__tag_Buffer> Buffer;
	CurrentObjectsWithTarget<__tag_Framebuffer> Framebuffer;
	CurrentObjectsWithTarget<__tag_Renderbuffer> Renderbuffer;
	CurrentObjectsWithTarget<__tag_TransformFeedback> TransformFeedback;

//]
//[oglplus_client_CurrentObjects2
private:
	template <typename __ObjTag>
	class CurrentObjectWithoutTarget /*<
	Stack of objects the top of which is currently bound
	to an implicit binding point.
	>*/
	 : public __SettingStack<GLuint, ...>
	{
	public:
		CurrentObjectWithoutTarget(void);

		__ObjectName<__ObjTag> Get(void) const
		noexcept;

		operator __ObjectName<__ObjTag> (void) const
		noexcept;

		typedef __SettingHolder<GLuint, ...> Holder;

		Holder Push(__ObjectName<__ObjTag> obj); /*<
		Unwraps the object name, binds it to the implicit
		binding point and pushes it onto the stack.
		>*/

		void Bind(__ObjectName<__ObjTag> obj); /*<
		Unwraps the object name, binds it to the implicit
		binding point and calls __SettingStack::Set.
		>*/

	};
public:
	CurrentObjectWithoutTarget<__tag_Program> Program;
	CurrentObjectWithoutTarget<__tag_ProgramPipeline> ProgramPipeline;
	CurrentObjectWithoutTarget<__tag_VertexArray> VertexArray;
//]
//[oglplus_client_CurrentObjects3
private:
	template <TextureTarget TexTarget>
	class CurrentUnitTexture /*<
	Stack of texture names the top of which is currently bound
	to the specified [^TexTarget].
	>*/
	 : public __SettingStack<GLuint, ...>
	{
		CurrentUnitTexture(__TextureUnitSelector tex_unit);

		__TextureName Get(void) const
		noexcept;

		operator TextureName (void) const
		noexcept;

		typedef __SettingHolder<GLuint, ...> Holder;

		Holder Push(__TextureName tex); /*<
		Unwraps the texture name, binds it to [^TexTarget]
		and pushes it onto the stack.
		>*/

		void Bind(__TextureName tex); /*<
		Unwraps the texture name, binds it to [^TexTarget]
		and calls __SettingStack::Set.
		>*/
	};

	class CurrentTextures /*<
	Set of stacks (each for a particular texture unit) managing
	the binding of textures to binding points.
	>*/
	{
	private:
		typedef __enums_EnumToClass_TextureTarget<
			__TextureUnitSelector,
			__TextureTarget,
			CurrentUnitTexture
		> CurrentUnitTextures;
	public:
		CurrentUnitTextures& Unit(std::size_t index); /*<
		Returns a reference to the stack of texture bindings
		on the texture unit at the specified [^index].
		>*/
		CurrentUnitTextures& operator [] (std::size_t index);
	};
public:
	CurrentTextures Texture;
//]
//[oglplus_client_CurrentObjects4
private:
	class CurrentUnitSampler /*<
	Stack of sampler names, the top of which is currently bound.
	>*/
	 : public __SettingStack<GLuint, ...>
	{
	public:
		CurrentUnitSampler(__TextureUnitSelector tex_unit);

		__SamplerName Get(void) const
		noexcept;

		operator SamplerName (void) const
		noexcept;
		{
			return Get();
		}

		typedef __SettingHolder<GLuint, ...> Holder;

		Holder Push(__SamplerName sam); /*<
		Unwraps the sampler name, binds it and pushes it onto the stack.
		>*/

		void Bind(__SamplerName sam); /*<
		Unwraps the texture name, binds it
		and calls __SettingStack::Set.
		>*/
	};

	class CurrentSamplers
	{
	public:
		CurrentUnitSampler& Unit(std::size_t index); /*<
		Returns a reference to the stack of sampler bindings
		on the texture unit at the specified [^index].
		>*/
		CurrentUnitSampler& operator [] (std::size_t index);
	};
public:
	CurrentSamplers Sampler;
};


} // namespace client
//]
