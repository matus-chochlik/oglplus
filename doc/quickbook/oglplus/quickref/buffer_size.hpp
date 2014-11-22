/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_buffer_size
namespace oglplus {

class BufferSize
{
public:
	BufferSize(void); /*< Constructs a zero size. >*/
	BufferSize(GLsizeiptr size); /*<
	Constructs a [^BufferSize] object from a [^value] in bytes.
	>*/

	template <typename T>
	BufferSize(unsigned count, const T*); /*<
	Constructs a [^BufferSize] required to store [^count] instances of [^T].
	>*/

	template <typename T, std::size_t N>
	BufferSize(const T (&)[N]); /*<
	Constructs a [^BufferSize] required to store [^N] instances of [^T].
	>*/

	template <typename T, std::size_t N>
	BufferSize(const std::array<T, N>& array); /*<
	Constructs a [^BufferSize] required to store elements in [^array].
	>*/

	template <typename T>
	BufferSize(const std::vector<T>& vector); /*<
	Constructs a [^BufferSize] required to store elements in [^vector].
	>*/

	template <typename T>
	static BufferSize Of(unsigned count, const T* data = nullptr); /*<
	Makes a new instance of [^BufferSize] required to store [^count]
	instances of [^T].
	>*/

	template <typename T>
	BufferSize Add(unsigned count, const T* = nullptr) const; /*<
	Returns a new [^BufferSize] that is the sum of [^this]
	and the size of count instances of T.
	>*/

	BufferSize Add(const BufferSize& buffer_size); const /*<
	Returns a new [^BufferSize] that is the sum of [^this]
	and the specified [^buffer_size].
	>*/

	GLsizeiptr Get(void) const; /*<
	Returns the stored size in bytes.
	>*/
};
//]
//[oglplus_buffer_typed_size
template <typename T>
class BufferTypedSize
 : public __BufferSize
{
public:
	BufferTypedSize(void);
	BufferTypedSize(GLsizeiptr count); /*<
	Constructs a [^BufferSize] required to store [^count] instances of [^T].
	>*/
};

} // namespace oglplus
//]

