/**
 *  @file oglplus/ext/NV_path_rendering/path_spec.hpp
 *  @brief Wrapper for the NV_path_rendering path specification wrapper
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_EXT_NV_PATH_RENDERING_PATH_SPEC_1203031902_HPP
#define OGLPLUS_EXT_NV_PATH_RENDERING_PATH_SPEC_1203031902_HPP

#if OGLPLUS_DOCUMENTATION_ONLY || GL_NV_path_rendering

#include <oglplus/ext/NV_path_rendering/command.hpp>

#include <vector>

namespace oglplus {

class PathNVOps;

template <typename PathCoordType>
class PathNVSpec
{
private:
	friend class PathNVOps;

	std::vector<PathNVCommand> _commands;
	std::vector<PathCoordType> _coords;

	typedef PathCoordType T;

	PathNVSpec& _append(PathNVCommand command)
	{
		_commands.push_back(command);

		return *this;
	}

	PathNVSpec& _append(PathNVCommand command, T coord)
	{
		_commands.push_back(command);
		_coords.push_back(coord);

		return *this;
	}

	template <typename ... C>
	PathNVSpec& _append(PathNVCommand command, C ... coord)
	{
		const std::size_t N = sizeof ... (coord);
		const T coords[N] = { T(coord)... };

		_commands.push_back(command);
		_coords.insert(_coords.end(), coords, coords+N);

		return *this;
	}
public:
	PathNVSpec(void) { }

	PathNVSpec(GLuint command_count_hint, GLuint coord_count_hint)
	{
		_commands.reserve(command_count_hint);
		_coords.reserve(coord_count_hint);
	}

	PathNVSpec(PathNVSpec&& tmp)
	 : _commands(std::move(tmp._commands))
	 , _coords(std::move(tmp._coords))
	{ }

	PathNVSpec& Close(void)
	{
		return _append(PathNVCommand::Close);
	}

	PathNVSpec& Restart(void)
	{
		return _append(PathNVCommand::Restart);
	}

	PathNVSpec& MoveTo(T c0, T c1)
	{
		return _append(PathNVCommand::MoveTo, c0, c1);
	}

	PathNVSpec& RelativeMoveTo(T c0, T c1)
	{
		return _append(PathNVCommand::RelativeMoveTo, c0, c1);
	}

	PathNVSpec& LineTo(T c0, T c1)
	{
		return _append(PathNVCommand::LineTo, c0, c1);
	}

	PathNVSpec& RelativeLineTo(T c0, T c1)
	{
		return _append(PathNVCommand::RelativeLineTo, c0, c1);
	}

	PathNVSpec& HorizontalLineTo(T c0)
	{
		return _append(PathNVCommand::HorizontalLineTo, c0);
	}

	PathNVSpec& RelativeHorizontalLineTo(T c0)
	{
		return _append(PathNVCommand::RelativeHorizontalLineTo, c0);
	}

	PathNVSpec& VerticalLineTo(T c0)
	{
		return _append(PathNVCommand::VerticalLineTo, c0);
	}

	PathNVSpec& RelativeVerticalLineTo(T c0)
	{
		return _append(PathNVCommand::RelativeVerticalLineTo, c0);
	}

	PathNVSpec& QuadraticCurveTo(T c0, T c1, T c2, T c3)
	{
		return _append(
			PathNVCommand::QuadraticCurveTo,
			c0, c1, c2, c3
		);
	}

	PathNVSpec& RelativeQuadraticCurveTo(T c0, T c1, T c2, T c3)
	{
		return _append(
			PathNVCommand::RelativeQuadraticCurveTo,
			c0, c1, c2, c3
		);
	}

	PathNVSpec& CubicCurveTo(T c0, T c1, T c2, T c3, T c4, T c5)
	{
		return _append(
			PathNVCommand::CubicCurveTo,
			c0, c1, c2, c3, c4, c5
		);
	}

	PathNVSpec& RelativeCubicCurveTo(T c0, T c1, T c2, T c3, T c4, T c5)
	{
		return _append(
			PathNVCommand::RelativeCubicCurveTo,
			c0, c1, c2, c3, c4, c5
		);
	}

	PathNVSpec& SmoothQuadraticCurveTo(T c0, T c1)
	{
		return _append(
			PathNVCommand::SmoothQuadraticCurveTo,
			c0, c1
		);
	}

	PathNVSpec& RelativeSmoothQuadraticCurveTo(T c0, T c1)
	{
		return _append(
			PathNVCommand::RelativeSmoothQuadraticCurveTo,
			c0, c1
		);
	}

	PathNVSpec& SmoothCubicCurveTo(T c0, T c1, T c2, T c3)
	{
		return _append(
			PathNVCommand::SmoothCubicCurveTo,
			c0, c1, c2, c3
		);
	}

	PathNVSpec& RelativeSmoothCubicCurveTo(T c0, T c1, T c2, T c3)
	{
		return _append(
			PathNVCommand::RelativeSmoothCubicCurveTo,
			c0, c1, c2, c3
		);
	}

	PathNVSpec& SmallCCWArcTo(T c0, T c1, T c2, T c3, T c4)
	{
		return _append(
			PathNVCommand::SmallCCWArcTo,
			c0, c1, c2, c3, c4
		);
	}

	PathNVSpec& RelativeSmallCCWArcTo(T c0, T c1, T c2, T c3, T c4)
	{
		return _append(
			PathNVCommand::RelativeSmallCCWArcTo,
			c0, c1, c2, c3, c4
		);
	}

	PathNVSpec& SmallCWArcTo(T c0, T c1, T c2, T c3, T c4)
	{
		return _append(
			PathNVCommand::SmallCWArcTo,
			c0, c1, c2, c3, c4
		);
	}

	PathNVSpec& RelativeSmallCWArcTo(T c0, T c1, T c2, T c3, T c4)
	{
		return _append(
			PathNVCommand::RelativeSmallCWArcTo,
			c0, c1, c2, c3, c4
		);
	}

	PathNVSpec& LargeCCWArcTo(T c0, T c1, T c2, T c3, T c4)
	{
		return _append(
			PathNVCommand::LargeCCWArcTo,
			c0, c1, c2, c3, c4
		);
	}

	PathNVSpec& RelativeLargeCCWArcTo(T c0, T c1, T c2, T c3, T c4)
	{
		return _append(
			PathNVCommand::RelativeLargeCCWArcTo,
			c0, c1, c2, c3, c4
		);
	}

	PathNVSpec& LargeCWArcTo(T c0, T c1, T c2, T c3, T c4)
	{
		return _append(
			PathNVCommand::LargeCWArcTo,
			c0, c1, c2, c3, c4
		);
	}

	PathNVSpec& RelativeLargeCWArcTo(T c0, T c1, T c2, T c3, T c4)
	{
		return _append(
			PathNVCommand::RelativeLargeCWArcTo,
			c0, c1, c2, c3, c4
		);
	}

	PathNVSpec& DupFirstCubicCurveTo(T c0, T c1, T c2, T c3)
	{
		return _append(
			PathNVCommand::DupFirstCubicCurveTo,
			c0, c1, c2, c3
		);
	}

	PathNVSpec& DupLastCubicCurveTo(T c0, T c1, T c2, T c3)
	{
		return _append(
			PathNVCommand::DupLastCubicCurveTo,
			c0, c1, c2, c3
		);
	}

	PathNVSpec& Rect(T c0, T c1, T c2, T c3)
	{
		return _append(PathNVCommand::Rect, c0, c1, c2, c3);
	}

	PathNVSpec& CircularCCWArcTo(T c0, T c1, T c2, T c3, T c4)
	{
		return _append(
			PathNVCommand::CircularCCWArcTo,
			c0, c1, c2, c3, c4
		);
	}

	PathNVSpec& CircularCWArcTo(T c0, T c1, T c2, T c3, T c4)
	{
		return _append(
			PathNVCommand::CircularCWArcTo,
			c0, c1, c2, c3, c4
		);
	}

	PathNVSpec& CircularTangentArcTo(T c0, T c1, T c2, T c3, T c4)
	{
		return _append(
			PathNVCommand::CircularTangentArcTo,
			c0, c1, c2, c3, c4
		);
	}

	PathNVSpec& ArcTo(T c0, T c1, T c2, T c3, T c4, T c5, T c6)
	{
		return _append(
			PathNVCommand::ArcTo,
			c0, c1, c2, c3, c4, c5, c6
		);
	}

	PathNVSpec& RelativeArcTo(T c0, T c1, T c2, T c3, T c4, T c5, T c6)
	{
		return _append(
			PathNVCommand::RelativeArcTo,
			c0, c1, c2, c3, c4, c5, c6
		);
	}
};

} // namespace oglplus

#endif // NV_path_rendering

#endif // include guard
