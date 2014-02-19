/**
 *  @file oglplus/images/metaballs.ipp
 *  @brief Implementation of images::Metaballs and MetaStarts
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <oglplus/angle.hpp>
#include <oglplus/vector.hpp>
#include <cassert>

namespace oglplus {
namespace images {

OGLPLUS_LIB_FUNC
BaseMetaballs::BaseMetaballs(
	GLsizei width,
	GLsizei height,
	const GLfloat* balls,
	std::size_t size,
	std::size_t n
): Image(
	width,
	height,
	1,
	1,
	(GLfloat*)nullptr,
	PixelDataFormat::Red,
	PixelDataInternalFormat::R32F
)
{
	assert(size % n == 0);

	const auto fc = FullCircle();
	auto a = this->_begin<GLfloat>();

	for(GLsizei y=0; y!=height; ++y)
	{
		const GLfloat j = (y+0.5f)/height;

		for(GLsizei x=0; x!=width; ++x)
		{
			GLfloat v = 0.0f;
			const GLfloat i = (x+0.5f)/width;
			const Vec2f p(i, j);

			for(std::size_t b=0; b!=size; b+=n)
			{
				const Vec2f c(balls+b, 2);

				for(int yo=-1; yo!=2; ++yo)
				for(int xo=-1; xo!=2; ++xo)
				{
					const Vec2f o(xo, yo);
					const Vec2f d = p - c + o;

					GLfloat r = balls[b+2];

					if(n > 3)
					{
						GLfloat w = ArcTan(d.y(), d.x())/fc;
						w += balls[b+2];
						w = Sin(fc*w*balls[b+3]);

						if(n > 4) r += balls[b+4]*r*w;
						else r += 0.25f*r*w;
					}

					float t = (r*r/Dot(d,d))-0.25;
					v += (t>0.0f)?t:0.0f;
				}
			}
			assert(a != this->_end<GLfloat>());
			*a++ = v;
		}
	}
	assert(a == this->_end<GLfloat>());
}

} // namespace images
} // namespace oglplus

