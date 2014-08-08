/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_opt_ranges_begin
namespace oglplus {
namespace ranges {
//]
//[oglplus_opt_ranges_IsRange
template <typename Range>
struct IsRange
{
	typedef __Unspecified Type; /*<
	[^std::true_type] if [^Range] conforms to the __Range concept or
	[^std::false_type] otherwise.
	>*/
};
//]

//[oglplus_opt_ranges_AnyRange
template <typename Element>
class AnyRange
{
public:
	AnyRange(void);

	template <typename Range>
	AnyRange(Range range); /*<
	Construction and assignment from a [^Range] type.
	>*/
	template <typename Range>
	AnyRange& operator = (const Range& range);

	AnyRange(const AnyRange& other); /*<
	Copy and move construction.
	>*/
	AnyRange(AnyRange&& temp);

	AnyRange& operator = (const AnyRange& other); /*<
	Copy and move assignment.
	>*/
	AnyRange& operator = (AnyRange&& other);

	typedef Element ValueType; /*< The __Range interface. >*/
	bool Empty(void) const;
	size_t Size(void) const;
	void Next(void);
	ValueType Front(void) const;
};

template <typename Range>
__AnyRange<typename Range::ValueType> EraseType(Range range); /*<
Erases the real type of the range passed as argument.
>*/
//]

//[oglplus_opt_ranges_end
} // namespace ranges
} // namespace oglplus
//]

