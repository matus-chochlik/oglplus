/**
 *  @file advanced/cloud_trace/arg_parser.hpp
 *  @brief Declaration of argument parser class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2008-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef OGLPLUS_ADVANCED_CLOUD_ARG_PARSER_1119071146_HPP
#define OGLPLUS_ADVANCED_CLOUD_ARG_PARSER_1119071146_HPP

#include <string>
#include <vector>

namespace oglplus {
namespace cloud_trace {

template <typename T>
struct ArgInfo
{
	unsigned parse_count;
	std::string short_name;
	std::string long_name;
	std::string description;

	std::vector<T*> vars;

	T min, max;
	bool has_min, has_max;

	ArgInfo(std::string&&, std::string&&, T&);
	ArgInfo(ArgInfo&&);

	ArgInfo& AddDesc(std::string&& desc)
	{
		description = std::move(desc);
		return *this;
	}

	ArgInfo& AddVar(T& var)
	{
		vars.push_back(&var);
		return *this;
	}

	ArgInfo& SetMin(const T& val)
	{
		min = val;
		has_min = true;
		return *this;
	}

	ArgInfo& SetMax(const T& val)
	{
		max = val;
		has_max = true;
		return *this;
	}

	bool Parse(int& arg, int argc, char** argv);
};

class ArgParser
{
private:
	std::vector<ArgInfo<bool>> options;
	std::vector<ArgInfo<float>> float_args;
	std::vector<ArgInfo<unsigned>> uint_args;
	std::vector<ArgInfo<std::string>> str_args;
	std::vector<ArgInfo<std::vector<std::string>>> str_list_args;

	template <typename T>
	bool ParseOne(int&, int, char**, std::vector<ArgInfo<T>>& args);
	bool ParseOne(int&, int, char**);
public:
	ArgInfo<bool>& AddOpt(std::string&&, std::string&&, bool&);
	ArgInfo<float>& AddArg(std::string&&, std::string&&, float&);
	ArgInfo<unsigned>& AddArg(std::string&&, std::string&&, unsigned&);
	ArgInfo<std::string>& AddArg(std::string&&, std::string&&, std::string&);
	ArgInfo<std::vector<std::string>>&
	AddArg(std::string&&, std::string&&, std::vector<std::string>&);

	bool Parse(int argc, char** argv);
};


} // namespace cloud_trace
} // namespace oglplus

#endif // include guard
