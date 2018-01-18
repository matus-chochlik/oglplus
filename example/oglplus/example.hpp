/**
 *  @file oglplus/example.hpp
 *  @brief Declares a common base class for examples
 *
 *  Copyright 2008-2018 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef OGLPLUS_EXAMPLE_EXAMPLE_1119071146_HPP
#define OGLPLUS_EXAMPLE_EXAMPLE_1119071146_HPP

#include <set>
#include <memory>
#include <oglplus/assert.hpp>

#ifndef _NDEBUG
#include <iostream>
#endif

#ifdef _MSC_VER
#pragma warning ( disable : 4244 )
#pragma warning ( disable : 4305 )
#endif //_MSC_VER

namespace oglplus {

/// Run-time parameters for example instances
struct ExampleParams
{
	/// the number of arguments passed on command-line
	int argc;

	/// the arguments strings
	char ** argv;

	/// The quality of rendered image (0.0 = low, 0.5 = default, 1.0 = high)
	float quality;

	/// The number of available GPUs
	unsigned num_gpus;

	/// The number of offscreen rendering threads (not counting the main thread)
	unsigned num_threads;

	/// The maximum number of threads
	unsigned max_threads;

	/// The set of threads for which a compatibility context should be created
	std::set<unsigned> compat_context_threads;

	ExampleParams(int argn, char ** args)
	 : argc(argn)
	 , argv(args)
	 , quality(0.5f)
	 , num_gpus(1)
	 , num_threads(0)
	 , max_threads(0)
	{ }

	void Check(void)
	{
		assert(num_threads <= max_threads);
	}

	bool HighQuality(void) const
	{
		return quality > 0.9f;
	}
};

void setupExample(ExampleParams& params);

/// A class measuring a time period in the examples
class ExampleTimePeriod
{
private:
	double _seconds;
public:
	explicit
	ExampleTimePeriod(double seconds)
	 : _seconds(seconds)
	{ }
	//
	/// Creates a zero-length time period
	static
	ExampleTimePeriod Zero(void)
	{
		return ExampleTimePeriod(0.0);
	}

	/// Creates a time period with the specified number of seconds
	static
	ExampleTimePeriod Seconds(double number)
	{
		return ExampleTimePeriod(number);
	}

	/// Creates a time period with the specified number of minutes
	static
	ExampleTimePeriod Minutes(double number)
	{
		return ExampleTimePeriod(number*60.0);
	}

	/// Creates a time period with the specified number of hours
	static
	ExampleTimePeriod Hours(double number)
	{
		return ExampleTimePeriod(number*3600.0);
	}

	/// The length of the periods in seconds
	double Seconds(void) const
	{
		return _seconds;
	}

	/// The current second of the period <0-60)
	int Second(void) const
	{
		return int(Seconds()) % 60;
	}

	/// The length of the periods in minutes
	double Minutes(void) const
	{
		return _seconds / 60.0;
	}

	/// The current minute of the period <0-60)
	int Minute(void) const
	{
		return int(Minutes()) % 60;
	}

	/// The length of the periods in hours
	double Hours(void) const
	{
		return _seconds / 3600.0;
	}

	/// The current minute of the period <0-24)
	int Hour(void) const
	{
		return int(Hours()) % 24;
	}

	/// The length of the period in days
	double Days(void) const
	{
		return _seconds / (24*3600.0);
	}

	/// The current day of the period
	int Day(void) const
	{
		return int(Days());
	}

	/// Time period addition
	friend
	ExampleTimePeriod operator + (ExampleTimePeriod a, ExampleTimePeriod b)
	{
		return ExampleTimePeriod(a._seconds + b._seconds);
	}

	/// Time period addition
	ExampleTimePeriod& operator += (ExampleTimePeriod p)
	{
		_seconds += p._seconds;
		return *this;
	}

	/// Time period subtraction
	friend
	ExampleTimePeriod operator - (ExampleTimePeriod a, ExampleTimePeriod b)
	{
		return ExampleTimePeriod(a._seconds - b._seconds);
	}

	/// Time period multiplication
	friend
	ExampleTimePeriod operator * (int a, ExampleTimePeriod b)
	{
		return ExampleTimePeriod(a * b._seconds);
	}

	/// Less than comparison
	friend
	bool operator < (ExampleTimePeriod a, ExampleTimePeriod b)
	{
		return a._seconds < b._seconds;
	}

	/// Greater than comparison
	friend
	bool operator > (ExampleTimePeriod a, ExampleTimePeriod b)
	{
		return a._seconds > b._seconds;
	}

	/// Greater than or equal comparison
	friend
	bool operator >= (ExampleTimePeriod a, ExampleTimePeriod b)
	{
		return a._seconds >= b._seconds;
	}
};

/// Class measuring the simulation time of an Example
class ExampleClock
{
private:
	double _start, _past, _real_time, _curr_time, _prev_time, _pace; //[s]
public:
	ExampleClock(ExampleTimePeriod start = ExampleTimePeriod::Zero())
	 : _start(start.Seconds())
	 , _past(start.Seconds())
	 , _real_time(start.Seconds())
	 , _curr_time(start.Seconds())
	 , _prev_time(start.Seconds())
	 , _pace(1.0)
	{ }

	/// Update the clock by providing real time
	void Update(ExampleTimePeriod real_time)
	{
		_prev_time = _curr_time;
		_real_time = real_time.Seconds();
		_curr_time = _past + (_real_time - _start) * _pace;
	}

	/// Advances the clock
	void Advance(ExampleTimePeriod offs)
	{
		_prev_time = _curr_time;
		_real_time += offs.Seconds();
		_curr_time = _past + (_real_time - _start) * _pace;
	}

	/// Set the pace by which the sim. time advances compared to real-time
	void Pace(double pace)
	{
		if(_pace != pace)
		{
			_start = _real_time;
			_past = _curr_time;
			_pace = pace;
		}
	}

	/// Equivalent to Now().Seconds()
	double Time(void) const
	{
		return this->Now().Seconds();
	}

	/// Returns the real time elapsed since the start of the example
	ExampleTimePeriod RealTime(void) const
	{
		return ExampleTimePeriod(_real_time);
	}

	/// Returns the simulation time elapsed since the start of the example
	ExampleTimePeriod Now(void) const
	{
		return ExampleTimePeriod(_curr_time);
	}

	/// Returns the time elapsed between the last and the previous Update
	ExampleTimePeriod Interval(void) const
	{
		return ExampleTimePeriod(_curr_time-_prev_time);
	}
};

class Example;

/// Base class for OGLplus example offscreen rendering threads
class ExampleThread
{
public:
	virtual ~ExampleThread(void)
	{ }

	/// Notifies the thread that the example is closing
	/** Implementations of ExampleThread should cancel
	 *  all rendering operations and quit the Render
	 *  function ASAP.
	 */
	virtual void Cancel(void){ }

	/// Rendering procedure with simple timing
	virtual void Render(double /*time*/)
	{
		OGLPLUS_ABORT("Render must be overloaded by examples!");
	}

	/// Rendering procedure with advanced timing
	virtual void Render(const ExampleClock& clock)
	{
		this->Render(clock.Now().Seconds());
	}

	/// Rendering procedure split into several parts
	virtual double RenderPart(
		unsigned /*part_no*/,
		const ExampleClock& clock
	)
	{
		this->Render(clock);
		return 1.0;
	}
};

std::unique_ptr<ExampleThread> makeExampleThread(
	Example& example,
	unsigned thread_id,
	const ExampleParams& params
);

/// Base class for OGLplus examples
class Example
{
public:
	virtual ~Example(void)
	{ }

	/// Place to do additional thread-related initialization of example
	/** This function is called in the context of the main thread
	 *  after all example threads are created, before the rendering
	 *  loop starts.
	 */
	virtual void PrepareThread(unsigned, ExampleThread&)
	{
	}

	/// Returns the timeout period for the example.
	virtual ExampleTimePeriod DefaultTimeout(void)
	{
		return ExampleTimePeriod::Seconds(5.0);
	}

	/// Hint for the main function whether to continue rendering
	/** Implementations of the main function may choose to ignore
	 *  the result of this function or not call it at all.
	 *  This is the overload for advanced timing.
	 */
	virtual bool Continue(const ExampleClock& clock)
	{
		return clock.Now() < DefaultTimeout(); // [seconds]
	}

	/// Reshape event handler
	virtual void Reshape(GLuint width, GLuint height) = 0;

	/// Mouse move event handler
	virtual void MouseMoveNormalized(float x, float y, float aspect)
	{
		(void)(x+y+aspect);
	}

	/// Mouse move event handler
	virtual void MouseMove(GLuint x, GLuint y, GLuint width, GLuint height)
	{
		return MouseMoveNormalized(
			(float(x) - width * 0.5f) / (width * 0.5f),
			(float(y) - height* 0.5f) / (height* 0.5f),
			float(width)/height
		);
	}

	/// Rendering procedure with simple timing
	virtual void Render(double /*time*/)
	{
		OGLPLUS_ABORT("Render must be overloaded by examples!");
	}

	/// Rendering procedure with advanced timing
	virtual void Render(ExampleClock& clock)
	{
		this->Render(clock.Now().Seconds());
	}

	/// Rendering procedure split into several parts
	virtual double RenderPart(unsigned /*part_no*/, ExampleClock& clock)
	{
		this->Render(clock);
		return 1.0;
	}

	/// The number of heat-up sequence frames
	virtual int HeatUpFrames(void) const
	{
		return 5;
	}

	/// The screenshot capture heat-up sequence start time
	virtual ExampleTimePeriod HeatUpTime(void) const
	{
		return ScreenshotTime()-HeatUpFrames()*FrameTime();
	}

	/// The time of the default screenshot
	virtual ExampleTimePeriod ScreenshotTime(void) const
	{
		return ExampleTimePeriod::Seconds(1.0);
	}

	/// Single frame time in the screenshot capture sequence
	virtual ExampleTimePeriod FrameTime(void) const
	{
		return ExampleTimePeriod::Seconds(1.0/25.0);
	}
};

std::unique_ptr<Example> makeExample(const ExampleParams& params);

} // namespace oglplus

#endif // include guard
