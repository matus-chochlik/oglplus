/**
 *  @file oglplus/client/rasterization.hpp
 *  @brief Client current rasterization setting stack
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_CLIENT_RASTERIZTION_1412071213_HPP
#define OGLPLUS_CLIENT_RASTERIZTION_1412071213_HPP

#include <oglplus/client/setting.hpp>
#include <oglplus/context/rasterization.hpp>

namespace oglplus {
namespace client {
namespace aux {

class FrontFace
 : public SettingStack<FaceOrientation, Nothing>
{
private:
	static
	FaceOrientation _do_get(Nothing)
	{
		return context::RasterizationState::FrontFace();
	}

	static
	void _do_set(FaceOrientation val, Nothing)
	{
		context::RasterizationState::FrontFace(val);
	}
public:
	FrontFace(void)
	 : SettingStack<FaceOrientation, Nothing>(&_do_get, &_do_set)
	{ }
};

class CullFace
 : public SettingStack<Face, Nothing>
{
private:
	static
	Face _do_get(Nothing)
	{
		return context::RasterizationState::CullFaceMode();
	}

	static
	void _do_set(Face val, Nothing)
	{
		context::RasterizationState::CullFace(val);
	}
public:
	CullFace(void)
	 : SettingStack<Face, Nothing>(&_do_get, &_do_set)
	{ }
};

#if GL_VERSION_3_2 || GL_ARB_provoking_vertex
class ProvokingVertex
 : public SettingStack<ProvokeMode, Nothing>
{
private:
	static
	ProvokeMode _do_get(Nothing)
	{
		return context::RasterizationState::ProvokingVertex();
	}

	static
	void _do_set(ProvokeMode val, Nothing)
	{
		context::RasterizationState::ProvokingVertex(val);
	}
public:
	ProvokingVertex(void)
	 : SettingStack<ProvokeMode, Nothing>(&_do_get, &_do_set)
	{ }
};
#endif

#if GL_VERSION_3_0
class PolygonMode
 : public SettingStack<context::PolygonModes, Nothing>
{
private:
	static
	context::PolygonModes _do_get(Nothing)
	{
		return context::RasterizationState::PolygonMode();
	}

	static
	void _do_set(context::PolygonModes val, Nothing)
	{
		context::RasterizationState::PolygonMode(val);
	}
public:
	PolygonMode(void)
	 : SettingStack<context::PolygonModes, Nothing>(&_do_get, &_do_set)
	{ }
};
#endif

class PolygonOffset
 : public SettingStack<context::PolygonOffsPara, Nothing>
{
private:
	static
	context::PolygonOffsPara _do_get(Nothing)
	{
		return context::RasterizationState::PolygonOffset();
	}

	static
	void _do_set(context::PolygonOffsPara val, Nothing)
	{
		context::RasterizationState::PolygonOffset(val);
	}
public:
	PolygonOffset(void)
	 : SettingStack<context::PolygonOffsPara, Nothing>(&_do_get, &_do_set)
	{ }
};

} // namespace aux

class RasterizationState
{
public:
	aux::FrontFace FrontFace;
	aux::CullFace CullFace;

#if GL_VERSION_3_0
	aux::PolygonMode PolygonMode;
#endif
	aux::PolygonOffset PolygonOffset;

#if GL_VERSION_3_2 || GL_ARB_provoking_vertex
	aux::ProvokingVertex ProvokingVertex;
#endif

// TODO
};

} // namespace client
} // namespace oglplus

#endif // include guard
