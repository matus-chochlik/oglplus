/**
 *  @file oglplus/ext/AMD_performance_monitor.hpp
 *  @brief Wrapper for the AMD_performance_monitor extension
 *
 *  @note Work in progress
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_EXT_AMD_PERFORMANCE_MONITOR_1203031902_HPP
#define OGLPLUS_EXT_AMD_PERFORMANCE_MONITOR_1203031902_HPP

#include <oglplus/config.hpp>
#include <oglplus/extension.hpp>
#include <oglplus/enumerations.hpp>

#include <cassert>
#include <vector>

namespace oglplus {

#if OGLPLUS_DOCUMENTATION_ONLY || GL_AMD_performance_monitor

/// Performance counter type
/**
 *  @ingroup enumerations
 *
 *  @glsymbols
 *  @glextref{AMD,performance_monitor}
 */
OGLPLUS_ENUM_CLASS_BEGIN(PerfMonitorAMDType, GLenum)
#include <oglplus/enums/ext/amd_perf_monitor_type.ipp>
OGLPLUS_ENUM_CLASS_END(PerfMonitorAMDType)

#if !OGLPLUS_NO_ENUM_VALUE_NAMES
#include <oglplus/enums/ext/amd_perf_monitor_type_names.ipp>
#endif

#if !OGLPLUS_ENUM_VALUE_RANGES
#include <oglplus/enums/ext/amd_perf_monitor_type_range.ipp>
#endif

class PerfMonitorAMDGroup;
class PerfMonitorAMDOps;
class AMD_performance_monitor;

/// Wrapper for performance monitor counter functionality
/**
 *
 *  @glsymbols
 *  @glextref{AMD,performance_monitor}
 */
class PerfMonitorAMDCounter
{
private:
	GLuint _group;
	GLuint _counter;

	friend class PerfMonitorAMDGroup;
	friend class PerfMonitorAMDOps;

	PerfMonitorAMDCounter(GLuint group, GLuint counter)
	 : _group(group)
	 , _counter(counter)
	{ }
public:
	/// Returns a string describing the monitor counter
	/**
	 *  @glsymbols
	 *  @glfunref{GetPerfMonitorCounterStringAMD}
	 */
	String GetString(void) const
	{
		GLsizei length = 0;
		OGLPLUS_GLFUNC(GetPerfMonitorCounterStringAMD)(
			_group,
			_counter,
			0,
			&length,
			nullptr
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetPerfMonitorCounterStringAMD));

		std::vector<GLchar> buffer(length);
		OGLPLUS_GLFUNC(GetPerfMonitorCounterStringAMD)(
			_group,
			_counter,
			GLsizei(buffer.size()),
			&length,
			buffer.data()
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetPerfMonitorCounterStringAMD));
		return String(buffer.data(), buffer.size());
	}

	/// Returns the type of the counter
	/**
	 *  @glsymbols
	 *  @glfunref{GetPerfMonitorCounterInfoAMD}
	 *  @gldefref{COUNTER_TYPE_AMD}
	 */
	PerfMonitorAMDType Type(void) const
	{
		GLenum result;
		OGLPLUS_GLFUNC(GetPerfMonitorCounterInfoAMD)(
			_group,
			_counter,
			GL_COUNTER_TYPE_AMD,
			&result
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetPerfMonitorCounterInfoAMD));
		return PerfMonitorAMDType(result);
	}
};

/// Wrapper for performance monitor group functionality
/**
 *
 *  @glsymbols
 *  @glextref{AMD,performance_monitor}
 */
class PerfMonitorAMDGroup
{
private:
	GLuint _group;

	friend class AMD_performance_monitor;

	PerfMonitorAMDGroup(GLuint group)
	 : _group(group)
	{ }
public:
	/// Returns a string describing the monitor group
	/**
	 *  @glsymbols
	 *  @glfunref{GetPerfMonitorGroupStringAMD}
	 */
	String GetString(void) const
	{
		GLsizei length = 0;
		OGLPLUS_GLFUNC(GetPerfMonitorGroupStringAMD)(
			_group,
			0,
			&length,
			nullptr
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetPerfMonitorGroupStringAMD));

		std::vector<GLchar> buffer(length);
		OGLPLUS_GLFUNC(GetPerfMonitorGroupStringAMD)(
			_group,
			GLsizei(buffer.size()),
			&length,
			buffer.data()
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetPerfMonitorGroupStringAMD));
		return String(buffer.data(), buffer.size());
	}

	/// Queries the performance counters in this group
	/**
	 *  @glsymbols
	 *  @glfunref{GetPerfMonitorCountersAMD}
	 */
	void GetCounters(
		GLint& max_active_counters,
		std::vector<PerfMonitorAMDCounter>& counters
	) const
	{
		GLint count = 0;
		OGLPLUS_GLFUNC(GetPerfMonitorCountersAMD)(
			_group,
			&count,
			&max_active_counters,
			0,
			nullptr
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetPerfMonitorCountersAMD));

		std::vector<GLuint> buffer(count);
		OGLPLUS_GLFUNC(GetPerfMonitorCountersAMD)(
			_group,
			&count,
			&max_active_counters,
			buffer.size(),
			buffer.data()
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetPerfMonitorCountersAMD));

		counters.clear();
		counters.reserve(count);
		for(auto i=buffer.begin(), e=buffer.end(); i!=e; ++i)
			counters.push_back(PerfMonitorAMDCounter(_group, *i));
	}

	/// Returns the performance counters in this group
	/**
	 *  @glsymbols
	 *  @glfunref{GetPerfMonitorCountersAMD}
	 */
	std::vector<PerfMonitorAMDCounter>
	GetCounters(GLint& max_active_counters) const
	{
		std::vector<PerfMonitorAMDCounter> result;
		GetCounters(max_active_counters, result);
		return result;
	}

};

/// Wrapper for performance counter result
/**
 *
 *  @glsymbols
 *  @glextref{AMD,performance_monitor}
 */
class PerfMonitorAMDResult
{
private:
	PerfMonitorAMDCounter _counter;

	union {
		GLfloat _fl;
		struct {
			GLuint _lo;
			GLuint _hi;
		} _qw;
	};

	PerfMonitorAMDResult(
		PerfMonitorAMDCounter counter,
		GLuint lo,
		GLuint hi
	): _counter(counter)
	{
		_qw._lo = lo;
		_qw._hi = hi;
	}

	friend class PerfMonitorAMDOps;
public:
	/// Returns the counter that this is a result of
	PerfMonitorAMDCounter Counter(void) const
	{
		return _counter;
	}

	/// Returns the low dword of the result
	GLuint Low(void) const
	{
		return _qw._lo;
	}

	/// Returns the high dword of the result
	GLuint High(void) const
	{
		return _qw._lo;
	}

	/// Returns the floating-point value of the result
	GLfloat Float(void) const
	{
		return _fl;
	}
};

/// Wrapper for AMD_performance_monitor-object-related operations
/** @note Do not use this class directly, use Texture instead.
 *
 *  @glsymbols
 *  @glfunref{GenPerfMonitorsAMD}
 *  @glfunref{DeletePerfMonitorsAMD}
 *  @glfunref{IsPerfMonitorAMD}
 *  @glextref{AMD,performance_monitor}
 */
class PerfMonitorAMDOps
 : public Named
 , public BaseObject<true>
{
protected:
	typedef std::true_type _can_be_zero;

	static void _init(GLsizei count, GLuint* _name)
	{
		assert(_name != nullptr);
		OGLPLUS_GLFUNC(GenPerfMonitorsAMD)(count, _name);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GenPerfMonitorsAMD));
	}

	static void _cleanup(GLsizei count, GLuint* _name)
	OGLPLUS_NOEXCEPT(true)
	{
		assert(_name != nullptr);
		assert(*_name != 0);
		try{OGLPLUS_GLFUNC(DeletePerfMonitorsAMD)(count, _name);}
		catch(...){ }
	}

	static GLboolean _is_x(GLuint _name)
	OGLPLUS_NOEXCEPT(true)
	{
		OGLPLUS_FAKE_USE(_name);
		assert(_name != 0);
		return GL_TRUE;
	}

	friend class FriendOf<PerfMonitorAMDOps>;
public:
	/// Enables or disables the specified counters for this monitor
	/**
	 *  The @p counters must be from the same group.
	 *
	 *  @glsymbols
	 *  @glfunref{SelectPerfMonitorCountersAMD}
	 */
	void SelectCounters(
		bool enable,
		const std::vector<PerfMonitorAMDCounter>& counters
	) const
	{
		if(counters.empty()) return;

		std::vector<GLuint> list(counters.size());
		GLuint group = counters[0]._group;

		for(size_t i=0, n=counters.size(); i!=n; ++i)
		{
			assert(group == counters[i]._group);
			list[i] = counters[i]._counter;
		}

		OGLPLUS_GLFUNC(SelectPerfMonitorCountersAMD)(
			this->_name,
			enable? GL_TRUE: GL_FALSE,
			group,
			GLint(list.size()),
			list.data()
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(SelectPerfMonitorCountersAMD));
	}

	/// Begins a monitoring session on this monitor
	/**
	 *  @glsymbols
	 *  @glfunref{BeginPerfMonitorAMD}
	 */
	void Begin(void) const
	{
		OGLPLUS_GLFUNC(BeginPerfMonitorAMD)(this->_name);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(BeginPerfMonitorAMD));
	}

	/// Ends a monitoring session on this monitor
	/**
	 *  @glsymbols
	 *  @glfunref{EndPerfMonitorAMD}
	 */
	void End(void) const
	{
		OGLPLUS_GLFUNC(EndPerfMonitorAMD)(this->_name);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(EndPerfMonitorAMD));
	}

	/// Returns true if results are available
	/**
	 *  @glsymbols
	 *  @glfunref{GetPerfMonitorCounterDataAMD}
	 *  @gldefref{PERFMON_RESULT_AVAILABLE_AMD}
	 */
	bool ResultAvailable(void) const
	{
		GLuint result = 0;
		OGLPLUS_GLFUNC(GetPerfMonitorCounterDataAMD)(
			this->_name,
			GL_PERFMON_RESULT_AVAILABLE_AMD,
			sizeof(result),
			&result,
			nullptr
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetPerfMonitorCounterDataAMD));
		return result != 0;
	}

	/// Returns the results
	/**
	 *  @glsymbols
	 *  @glfunref{GetPerfMonitorCounterDataAMD}
	 *  @gldefref{PERFMON_RESULT_SIZE_AMD}
	 *  @gldefref{PERFMON_RESULT_AMD}
	 */
	void Result(std::vector<PerfMonitorAMDResult>& results) const
	{
		GLuint size = 0;
		OGLPLUS_GLFUNC(GetPerfMonitorCounterDataAMD)(
			this->_name,
			GL_PERFMON_RESULT_SIZE_AMD,
			sizeof(size),
			&size,
			nullptr
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetPerfMonitorCounterDataAMD));

		std::vector<GLuint> data(size / sizeof(GLuint));
		OGLPLUS_GLFUNC(GetPerfMonitorCounterDataAMD)(
			this->_name,
			GL_PERFMON_RESULT_AMD,
			data.size() * sizeof(GLuint),
			data.data(),
			nullptr
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetPerfMonitorCounterDataAMD));

		results.clear();
		results.reserve(data.size() / 3);

		auto i = data.begin(), e = data.end();
		while(i != e)
		{
			GLuint group = *i++;
			assert(i != e);
			GLuint ctr = *i++;
			assert(i != e);

			PerfMonitorAMDCounter counter(group, ctr);
			auto type = counter.Type();
			GLuint lo = *i++, hi = 0;
			if(type == PerfMonitorAMDType::UnsignedInt64)
				hi = *i++;

			results.push_back(PerfMonitorAMDResult(counter, lo, hi));
		}
	}
};

#if OGLPLUS_DOCUMENTATION_ONLY
/// An @ref oglplus_object encapsulating the performance monitor functionality
/**
 *  @ingroup oglplus_objects
 *
 *  @glsymbols
 *  @glextref{AMD,performance_monitor}
 */
class PerfMonitorAMD
 : public PerfMonitorAMDOps
{ };
#else
typedef Object<PerfMonitorAMDOps> PerfMonitorAMD;
#endif

/// Wrapper for the AMD_performance_monitor extension
/**
 *  @glsymbols
 *  @glextref{AMD,performance_monitor}
 *
 *  @ingroup gl_extensions
 */
class AMD_performance_monitor
{
public:
	OGLPLUS_EXTENSION_CLASS(AMD, performance_monitor)

	/// Queries the available performance counters groups
	/**
	 *  @glsymbols
	 *  @glfunref{GetPerfMonitorGroupsAMD}
	 */
	void GetGroups(std::vector<PerfMonitorAMDGroup>& groups) const
	{
		GLint count = 0;
		OGLPLUS_GLFUNC(GetPerfMonitorGroupsAMD)(
			&count,
			0,
			nullptr
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetPerfMonitorGroupsAMD));

		std::vector<GLuint> buffer(count);
		OGLPLUS_GLFUNC(GetPerfMonitorGroupsAMD)(
			&count,
			buffer.size(),
			buffer.data()
		);
		OGLPLUS_CHECK(OGLPLUS_ERROR_INFO(GetPerfMonitorGroupsAMD));

		groups.clear();
		groups.reserve(count);
		for(auto i=buffer.begin(), e=buffer.end(); i!=e; ++i)
			groups.push_back(PerfMonitorAMDGroup(*i));
	}

	/// Returns the available performance counter groups
	/**
	 *  @glsymbols
	 *  @glfunref{GetPerfMonitorGroupsAMD}
	 */
	std::vector<PerfMonitorAMDGroup> GetGroups(void) const
	{
		std::vector<PerfMonitorAMDGroup> result;
		GetGroups(result);
		return result;
	}
};
#endif

} // namespace oglplus

#endif // include guard
