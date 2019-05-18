/*
 *  Copyright 2014-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_dsa_buffer_raw_map

#if GL_VERSION_4_5 || GL_ARB_direct_state_access

class DSABufferRawMap {
public:
    DSABufferRawMap(
      __BufferName buffer,
      __BufferSize offset,
      __BufferSize size,
      __Bitfield<__BufferMapAccess>
        access); /*<
              Maps a range (specified by [^offset] and [^size]) of
              the specified [^buffer] with the specified [^access]
              to the client address space.
              See [glfunc MapNamedBufferRange].
              >*/

    DSABufferRawMap(
      __BufferName buffer,
      __Bitfield<__BufferMapAccess>
        access); /*<
              Maps the whole specified buffer
              with the specified [^access] to the client address space.
              See [glfunc MapNamedBuffer].
              >*/

    DSABufferRawMap(const DSABufferRawMap&) = delete; /*<
    DSABuffer maps are not copyable.
    >*/
    DSABufferRawMap(DSABufferRawMap&&);               /*<
                  DSABuffer maps are moveable.
                  >*/

    ~DSABufferRawMap(); /*<
    Unmaps the buffer from client address space (if mapped).
    See [glfunc UnmapNamedBuffer].
    >*/
    void Unmap();

    bool Mapped() const;     /*<
        Returns true if the buffer is mapped.
        >*/
    GLsizeiptr Size() const; /*<
    Returns the size (in bytes) of the mapped buffer.
    >*/

    const GLvoid* RawData() const; /*<
    Returns a raw pointer to the mapped data.
    Note that the buffer has to be mapped or the result is undefined.
    >*/
    GLvoid* RawData();

    void FlushRange(__BufferSize offset, __BufferSize length); /*<
    Indicate modifications to a mapped buffer range.
    Note that the buffer has to be mapped or the result is undefined.
    See [glfunc FlushMappedNamedBufferRange].
    >*/
};
//]
//[oglplus_dsa_buffer_typed_map

template <typename Type>
class DSABufferTypedMap : public __DSABufferRawMap {
public:
    DSABufferTypedMap(
      __BufferName buffer,
      __BufferTypedSize<Type> offset,
      __BufferTypedSize<Type> size,
      __Bitfield<__BufferMapAccess>
        access) /*<
              Maps a range (specified by [^offset] and [^size]) of
              the specified [^buffer] with the specified [^access]
              to the client address space.
              See [glfunc MapNamedBufferRange].
              >*/

      DSABufferTypedMap(
        __BufferName buffer,
        __Bitfield<__BufferMapAccess>
          access); /*<
                Maps the whole specified buffer
                with the specified [^access] to the client address space.
                See [glfunc MapNamedBuffer].
                >*/

    GLsizeiptr Count() const; /*<
    Returns the count of elements of [^Type] in the mapped buffer.
    >*/

    const Type* Data() const; /*<
    Returns a typed pointer to the mapped data.
    Note that the buffer has to be mapped or the result is undefined.
    >*/
    Type* Data();

    const Type& At(GLuint index) const; /*<
    Returns a reference to the element at the specified [^index].
    Note that the buffer has to be mapped or the result is undefined.
    >*/
    Type& At(GLuint index);

    void FlushElements(
      __BufferTypedSize<Type> start,
      __BufferTypedSize<Type>
        count); /*<
             Indicate modifications to a mapped range of elements of [^Type].
             Note that the buffer has to be mapped or the result is undefined.
             See [glfunc FlushMappedNamedBufferRange].
             >*/
};

#endif // GL_VERSION_4_5 || GL_ARB_direct_state_access

//]
