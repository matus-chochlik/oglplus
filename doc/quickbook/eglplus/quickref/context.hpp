/*
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[eglplus_context_attribs
namespace eglplus {

typedef __AttributeList<__ContextAttrib, ...> ContextAttribs; /*<
Attribute list type for context attributes.
>*/

typedef __FinishedAttributeList<__ContextAttrib, ...> FinishedContextAttribs; /*<
Finished attribute list type for context attributes.
>*/

//]
//[eglplus_context

class Context
{
public:
	Context(Context&& tmp);
	Context(const Context& tmp) = delete;

	Context(
		const __Display& display,
		const __Config& config
	); /*<
	Constructs a non-sharing context without any attributes.
	See [eglfunc CreateContext].
	>*/

	Context(
		const __Display& display,
		const __Config& config,
		const Context& shared_context
	); /*<
	Construct a sharing context without any attributes.
	See [eglfunc CreateContext].
	>*/

	Context(
		const __Display& display,
		const __Config& config,
		const __FinishedContextAttribs& attribs
	); /*<
	Construct a non-sharing context with the specified attributes.
	See [eglfunc CreateContext].
	>*/

	Context(
		const __Display& display,
		const __Config& config,
		const Context& shared_context,
		const __FinishedContextAttribs& attribs
	); /*<
	Construct a sharing context without any attributes.
	See [eglfunc CreateContext].
	>*/

	~Context(void); /*<
	Destroys the wrapped context.
	See [eglfunc DestroyContext].
	>*/
//TODO
};

} // namespace eglplus
//]

