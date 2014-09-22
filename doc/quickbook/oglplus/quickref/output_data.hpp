/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_output_data
namespace oglplus {

class OutputData
{
public:
	typedef __OneOf<__DataType, __PixelDataType> PixDataType;

	/// Construction from @p size in bytes and pointer to @p addr
	OutputData(BufferSize size, GLvoid* address); /*<
	Constructs [^OutputData] from a raw [^address] of a memory block
	and its [^size].
	>*/

	OutputData(PixDataType type, BufferSize size, GLvoid* address); /*<
	Constructs [^OutputData] from an [^address] of a memory block
	and its [^size] also specifying explicit data [^type].
	>*/

	template <typename T>
	OutputData(GLsizei count, T* address);  /*<
	Constructs [^OutputData] from a typed [^address] of a memory block
	and the [^count] of elements stored inside.
	>*/

	template <typename T, std::size_t N>
	OutputData(T (&array)[N]); /*<
	Constructs [^OutputData] from an [^array] of [^N] instances of type [^T].
	>*/

	template <typename T, std::size_t N>
	OutputData(std::array<T, N>& array); /*<
	Constructs [^OutputData] from an [^array].
	>*/

	template <typename T>
	OutputData(std::vector<T>& vector); /*<
	Constructs [^OutputData] from a [^vector].
	>*/

};

} // namespace oglplus
//]

