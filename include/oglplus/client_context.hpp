/**
 *  @file oglplus/client_context.hpp
 *  @brief Client context.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_CLIENT_CONTEXT_1412071213_HPP
#define OGLPLUS_CLIENT_CONTEXT_1412071213_HPP

#include <oglplus/client/object_binding.hpp>
#include <oglplus/client/capabilities.hpp>
#include <oglplus/client/hints.hpp>

#include <oglplus/client/depth_test.hpp>
#include <oglplus/client/logical_ops.hpp>
#include <oglplus/client/viewport.hpp>

#include <oglplus/client/drawing.hpp>
#include <oglplus/client/computing.hpp>

namespace oglplus {

class ClientContext
 : public client::CurrentObjects
 , public client::CurrentCapabilities
 , public client::CurrentHints
 , public client::DepthTest
 , public client::LogicalOps
 , public client::ViewportOps
 , public client::DrawingOps
 , public client::ComputingOps
{ };

} // namespace oglplus

#endif // include guard
