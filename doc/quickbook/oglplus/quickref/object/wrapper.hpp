/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_object_ObjGenDelOps
namespace oglplus {

template <typename __ObjTag>
class ObjGenDelOps
{
protected:
	static void Gen(GLsizei count, GLuint* names); /*<
	Generates [^count] objects of the type specified by __ObjTag
	and stores them in [^names].
	Note that [^names] must provide enough space for at least [^count]
	instances of [^GLuint].
	>*/
	static void Delete(GLsizei count, GLuint* names); /*<
	Deletes [^count] objects of the type specified by __ObjTag
	stored in names.
	>*/
	static GLboolean IsA(GLuint name); /*<
	Determines if [^name] is a valid name currently assigned by GL
	to some object of the type specified by __ObjTag.
	>*/
};

//]
//[oglplus_object_ObjectOps

template <typename __OpsTag, typename __ObjTag>
class ObjectOps
 : public __ObjectName<__ObjTag>
{
public: /*<
The public interface depends on the __OpsTag and __ObjTag.
>*/
};

//]
//[oglplus_object_ObjectSubtype

template <typename __ObjTag>
struct ObjectSubtype : __Nothing /*<
Most object types don't have any ['subtypes], which is indicated by
returning __Nothing by default.
>*/
{ };

//]
//[oglplus_object_Object

template <typename __OpsTag, typename __ObjTag>
class Object<ObjectOps<__OpsTag, __ObjTag>>
 : public __ObjGenDelOps<__ObjTag>
 , public __ObjectOps<__OpsTag, __ObjTag>
{
public:
	Object(const Object&) = delete; /*< [^Object]s are non-copyable. >*/
	Object(Object&& temp) noexcept; /*< [^Object]s are move-constructible >*/
	Object& operator = (Object&& temp) /*< [^Object]s are move-assignable.  >*/

	Object(void); /*<
	Default-constructs an [^Object]. This function creates a new GL object
	by calling the appropriate [^glGen*] or [^glCreate*] function.
	Note that object types with a [^Subtype] may not support default
	construction and may require that the subtype is specified.
	>*/
	Object(__ObjectDesc&& description); /*<
	Constructs an [^Object] and attaches the specified [^description] to it.
	>*/

	typedef typename __ObjectSubtype<__ObjTag>::Type Subtype; /*<
	The subtype of the object. If this object type does not have
	any subtypes, then [^Subtype] is defined as __Nothing.
	>*/

	Object(Subtype subtype); /*<
	Constructs an object of the specified [^subtype].
	If [^subtype] is __Nothing then this constructor is equivalent
	to the default constructor.
	>*/
	Object(Subtype subtype, __ObjectDesc&& description); /*<
	Constructs an object of the specified [^subtype] and attaches
	the specified [^description] to it.
	>*/

	~Object(void) noexcept; /*<
	Cleans up the wrapped GL object by calling
	the appropriate [^glDelete*] function.
	>*/

	static Object FromRawName(__ObjectName<__ObjTag> name); /*<
	Wraps an existing GL object with the specified [^name]. This
	function does not create a new GL object, instead it adopts
	the one passed as argument.
	>*/

	const std::string& Description(void) const /*<
	Returns the textual description of this object.
	>*/

	operator __Sequence<__ObjectName<__ObjTag>> (void) const; /*<
	[^Object]s are implicitly convertible to a sequence of object names.
	Note that the returned sequence must not be used after
	this object has been destroyed.
	>*/
};

} // namespace oglplus
//]

