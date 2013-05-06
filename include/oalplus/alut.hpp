/**
 *  @file oalplus/alut.hpp
 *  @brief Wrapper around ALUT
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OALPLUS_ALUT_1303201721_HPP
#define OALPLUS_ALUT_1303201721_HPP

#include <oalplus/config.hpp>
#include <oalplus/fwd.hpp>
#include <oalplus/alfunc.hpp>
#include <oalplus/error.hpp>
#include <oalplus/string.hpp>

#include <oalplus/data_format.hpp>

#include <oalplus/buffer.hpp>

#include <vector>

namespace oalplus {

class ALUtilityToolkit
{
private:
	bool _initialized;
	ALUtilityToolkit(const ALUtilityToolkit&);
public:
	ALUtilityToolkit(bool with_context, int argc = 0, char** argv = nullptr)
	 : _initialized(
		with_context
		?(OALPLUS_ALFUNC(alut,Init)(&argc, argv) == AL_TRUE)
		:(OALPLUS_ALFUNC(alut,InitWithoutContext)(&argc, argv)==AL_TRUE)
	)
	{
		OALPLUS_CHECK_ALUT(OALPLUS_ERROR_INFO(alut, Init));
	}

	ALUtilityToolkit(ALUtilityToolkit&& tmp)
	 : _initialized(tmp._initialized)
	{
		tmp._initialized = false;
	}

	~ALUtilityToolkit(void)
	{
		if(_initialized)
		{
			OALPLUS_ALFUNC(alut,Exit)();
		}
	}

private:
	static ALfloat _normalize_sample(ALubyte v)
	{
		return (ALfloat(v)-128.0f)/128.0f;
	}

	static ALfloat _normalize_sample(ALshort v)
	{
		return ALfloat(v)/32768.0f;
	}

	template <typename T>
	void _do_load_mem_norm(
		std::vector<ALfloat>& result,
		T*,
		::ALvoid* raw_data,
		::ALsizei size
	) const
	{
		std::size_t n = size/sizeof(T);
		result.resize(n);
		T* data = static_cast<T*>(raw_data);
		for(std::size_t i=0; i!=n; ++i)
		{
			result[i] = _normalize_sample(data[i]);
		}
	}

	struct _free_on_scope_exit
	{
		::ALvoid* ptr;

		~_free_on_scope_exit(void)
		{
			free(ptr);
		}
	};

	std::vector<ALfloat> _load_mem_norm(
		::ALvoid* raw_data,
		::ALenum format,
		::ALsizei size
	) const
	{
		std::vector<ALfloat> result;

		if(format == AL_FORMAT_MONO8)
		{
			_do_load_mem_norm(
				result,
				(::ALubyte*)nullptr,
				raw_data,
				size
			);
		}
		else if(format == AL_FORMAT_MONO16)
		{
			_do_load_mem_norm(
				result,
				(::ALshort*)nullptr,
				raw_data,
				size
			);
		}
		else if(format == AL_FORMAT_STEREO8)
		{
			_do_load_mem_norm(
				result,
				(::ALubyte*)nullptr,
				raw_data,
				size
			);
		}
		else if(format == AL_FORMAT_STEREO16)
		{
			_do_load_mem_norm(
				result,
				(::ALshort*)nullptr,
				raw_data,
				size
			);
		}

		return std::move(result);
	};

	std::vector<ALubyte> _load_memory(
		::ALvoid* raw_data,
		::ALsizei size
	) const
	{
		::ALubyte* data = (::ALubyte*)raw_data;
		return std::vector<ALubyte>(data, data+size);
	}
public:
	Buffer CreateBufferHelloWorld(void) const
	{
		assert(_initialized);
		ALuint name = OALPLUS_ALFUNC(alut,CreateBufferHelloWorld)();
		OALPLUS_VERIFY_ALUT(OALPLUS_ERROR_INFO(alut, CreateBufferHelloWorld));
		return Buffer::FromRawName(name);
	}

	Buffer CreateBufferFromFile(const ALchar* file_path) const
	{
		assert(_initialized);
		ALuint name = OALPLUS_ALFUNC(alut,CreateBufferFromFile)(file_path);
		OALPLUS_VERIFY_ALUT(OALPLUS_ERROR_INFO(alut, CreateBufferFromFile));
		return Buffer::FromRawName(name);
	}

	std::vector<ALfloat> LoadMemoryHelloWorldNormalized(
		DataFormat* data_format,
		ALfloat* frequency
	) const
	{
		::ALenum format = 0;
		::ALsizei size = 0;
		::ALvoid* ptr = OALPLUS_ALFUNC(alut,LoadMemoryHelloWorld)(
			&format,
			&size,
			frequency
		);
		OALPLUS_CHECK_ALUT(OALPLUS_ERROR_INFO(alut, LoadMemoryHelloWorld));

		_free_on_scope_exit cleaner = { ptr };
		OALPLUS_FAKE_USE(cleaner);

		if(data_format) *data_format = DataFormat(format);

		return _load_mem_norm(ptr, format, size);
	}

	std::vector<ALfloat> LoadMemoryFromFileNormalized(
		const ALchar* file_path,
		DataFormat* data_format,
		ALfloat* frequency
	) const
	{
		::ALenum format = 0;
		::ALsizei size = 0;
		::ALvoid* ptr = OALPLUS_ALFUNC(alut,LoadMemoryFromFile)(
			file_path,
			&format,
			&size,
			frequency
		);
		OALPLUS_CHECK_ALUT(OALPLUS_ERROR_INFO(alut, LoadMemoryFromFile));

		_free_on_scope_exit cleaner = { ptr };
		OALPLUS_FAKE_USE(cleaner);

		if(data_format) *data_format = DataFormat(format);

		return _load_mem_norm(ptr, format, size);
	}

	std::vector<ALubyte> LoadMemoryFromFile(
		const ALchar* file_path,
		DataFormat* data_format,
		ALfloat* frequency
	) const
	{
		::ALenum format = 0;
		::ALsizei size = 0;
		::ALvoid* ptr = OALPLUS_ALFUNC(alut,LoadMemoryFromFile)(
			file_path,
			&format,
			&size,
			frequency
		);
		OALPLUS_CHECK_ALUT(OALPLUS_ERROR_INFO(alut, LoadMemoryFromFile));

		_free_on_scope_exit cleaner = { ptr };
		OALPLUS_FAKE_USE(cleaner);

		if(data_format) *data_format = DataFormat(format);

		return _load_memory(ptr, size);
	}

	void LoadMemoryFromFile(
		std::vector<ALubyte>& raw,
		std::vector<ALfloat>& norm,
		const ALchar* file_path,
		DataFormat* data_format,
		ALfloat* frequency
	) const
	{
		::ALenum format = 0;
		::ALsizei size = 0;
		::ALvoid* ptr = OALPLUS_ALFUNC(alut,LoadMemoryFromFile)(
			file_path,
			&format,
			&size,
			frequency
		);
		OALPLUS_CHECK_ALUT(OALPLUS_ERROR_INFO(alut, LoadMemoryFromFile));

		_free_on_scope_exit cleaner = { ptr };
		OALPLUS_FAKE_USE(cleaner);

		if(data_format) *data_format = DataFormat(format);

		raw = _load_memory(ptr, size);
		norm = _load_mem_norm(ptr, format, size);
	}
};

} // namespace oalplus

#endif // include guard
