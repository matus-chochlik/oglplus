/**
 *  @file advanced/cloud_trace/arg_parser.cpp
 *  @brief Implementation of argument parser class
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2008-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include "arg_parser.hpp"

#include <stdexcept>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cassert>

namespace oglplus {
namespace cloud_trace {

template <typename T>
ArgInfo<T>::ArgInfo(
	std::string&& sn,
	std::string&& ln,
	T& var
): parse_count(0)
 , short_name(std::move(sn))
 , long_name(std::move(ln))
 , description()
 , vars(1, &var)
 , has_min(false)
 , has_max(false)
{
}

template <typename T>
ArgInfo<T>::ArgInfo(ArgInfo&& tmp)
 : parse_count(tmp.parse_count)
 , short_name(std::move(tmp.short_name))
 , long_name(std::move(tmp.long_name))
 , description(std::move(tmp.description))
 , vars(std::move(tmp.vars))
 , has_min(tmp.has_min)
 , has_max(tmp.has_max)
{
}

template <typename T>
void ParseValue(const char* name, const char* str, T& value)
{
	std::stringstream ss(str);

	ss >> value;
	if(ss.fail())
	{
		std::string message;
		message.append("Invalid value '");
		message.append(str);
		message.append("' after '");
		message.append(name);
		message.append("'");

		throw std::runtime_error(message);
	}
}

template <typename T>
void ParseAndSetValue(
	const char* name,
	const char* str,
	std::vector<T*> vars
)
{
	T value;
	ParseValue(name, str, value);

	for(T* ptr : vars)
	{
		assert(ptr != nullptr);
		*ptr = value;
	}
}

template <typename T>
void ParseAndSetValue(
	const char* name,
	const char* str,
	std::vector<std::vector<T>*>& vars
)
{
	T value;
	ParseValue(name, str, value);

	for(std::vector<T>* ptr : vars)
	{
		assert(ptr);
		ptr->push_back(std::move(value));
	}
}

template <typename T>
bool ArgInfo<T>::Parse(int& arg, int argc, char** argv)
{
	const char* name = nullptr;

	std::size_t len = short_name.size();
	if(std::strncmp(argv[arg], short_name.c_str(), len) == 0)
	{
		name = short_name.c_str();
	}
	else
	{
		len = long_name.size();
		if(std::strncmp(argv[arg], long_name.c_str(), len) == 0)
		{
			name = long_name.c_str();
		}
		else len = 0;
	}

	if(name && len)
	{
		if(argv[arg][len] == '=')
		{
			ParseAndSetValue(name, argv[arg]+len+1, vars);
			arg += 1;
			++parse_count;
			return true;
		}
		else if(argv[arg][len] == '\0')
		{
			if(arg+1 < argc)
			{
				ParseAndSetValue(name, argv[arg+1], vars);
				arg += 2;
				++parse_count;
				return true;
			}
			else
			{
				std::string message;
				message.append("Missing value after '");
				message.append(argv[arg]);
				message.append("'");

				throw std::runtime_error(message);
			}
		}
	}
	return false;
}

template <>
bool ArgInfo<bool>::Parse(int& arg, int, char** argv)
{
	bool result =
		(std::strcmp(argv[arg], long_name.c_str()) == 0) ||
		(std::strcmp(argv[arg], short_name.c_str()) == 0);
	if(result)
	{
		++arg;
		for(auto ptr : vars)
		{
			assert(ptr != nullptr);
			*ptr = true;
		}
		++parse_count;
	}

	return result;
}

ArgInfo<bool>& ArgParser::AddOpt(
	std::string&& short_name,
	std::string&& long_name,
	bool& var
)
{
	options.push_back(ArgInfo<bool>(
		std::move(short_name),
		std::move(long_name),
		var
	));
	return options.back();
}

ArgInfo<unsigned>& ArgParser::AddArg(
	std::string&& short_name,
	std::string&& long_name,
	unsigned& var
)
{
	uint_args.push_back(ArgInfo<unsigned>(
		std::move(short_name),
		std::move(long_name),
		var
	));
	return uint_args.back();
}

ArgInfo<float>& ArgParser::AddArg(
	std::string&& short_name,
	std::string&& long_name,
	float& var
)
{
	float_args.push_back(ArgInfo<float>(
		std::move(short_name),
		std::move(long_name),
		var
	));
	return float_args.back();
}

ArgInfo<std::string>& ArgParser::AddArg(
	std::string&& short_name,
	std::string&& long_name,
	std::string& var
)
{
	str_args.push_back(ArgInfo<std::string>(
		std::move(short_name),
		std::move(long_name),
		var
	));
	return str_args.back();
}

ArgInfo<std::vector<std::string>>& ArgParser::AddArg(
	std::string&& short_name,
	std::string&& long_name,
	std::vector<std::string>& var
)
{
	str_list_args.push_back(ArgInfo<std::vector<std::string>>(
		std::move(short_name),
		std::move(long_name),
		var
	));
	return str_list_args.back();
}

template <typename T>
bool ArgParser::ParseOne(
	int& arg,
	int argc,
	char** argv,
	std::vector<ArgInfo<T>>& arg_infos
)
{
	for(auto& arg_info : arg_infos)
	{
		if(arg_info.Parse(arg, argc, argv))
			return true;
	}
	return false;
}

bool ArgParser::ParseOne(int& arg, int argc, char** argv)
{
	if(ParseOne(arg, argc, argv, options))
		return true;
	if(ParseOne(arg, argc, argv, float_args))
		return true;
	if(ParseOne(arg, argc, argv, uint_args))
		return true;
	if(ParseOne(arg, argc, argv, str_args))
		return true;
	if(ParseOne(arg, argc, argv, str_list_args))
		return true;

	return false;
}

bool ArgParser::Parse(int argc, char** argv)
{
	int arg = 1;
	while(arg < argc)
	{
		if(!ParseOne(arg, argc, argv))
		{
			std::string message("Unknown command-line option: '");
			message.append(argv[arg]);
			message.append("'");

			throw std::runtime_error(message);
		}
	}
	return true;
}

} // namespace cloud_trace
} // namespace oglplus
