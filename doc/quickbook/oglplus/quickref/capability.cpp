/*
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_capability_ex_ss
using namespace oglplus;

Capability::DepthTest << true; /*< Enables depth test. >*/
Capability::StencilTest << false; /*< Disables stencil test. >*/

+Capability::CullFace; /*< Enables face culling. >*/
-Capability::Blend; /*< Disables blending. >*/

for(int i=0; i<4; ++i)
{
	(Functionality::ClipDistance | i) << true; /*<
	Enables the [^i]th clipping plane.
	>*/
}
//]

