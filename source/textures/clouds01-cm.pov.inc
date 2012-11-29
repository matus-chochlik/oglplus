// Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Output_Alpha=On

#declare WorldRadius = 6371000;
#declare AtmThickness = 50000;

#declare CameraPosition = <0.00, 10.00, 0.00>;
#include "cube_map_common.pov.inc"

global_settings {
	assumed_gamma 1.0
}

background { rgbt <0.5, 0.5, 0.5, 0.0> }

#macro CloudColor(Altitude, Layer, Density)
		function {
			min(25 * sqrt(
				pow(x/AtmThickness, 2)+
				pow(y/AtmThickness, 2)+
				pow(z/AtmThickness, 2)
			), 1.0)
		}
		color_map {
			[0.00 color rgbt <0.0, min(Altitude / AtmThickness, 1), min(Layer * 0.025, 1), min(Density, 1)>]
			[1.00 color rgbt <1.0, min(Altitude / AtmThickness, 1), min(Layer * 0.025, 1), min(Density, 1)>]
		}
#end

#macro CloudLayer(Altitude, Scale, Coverage, Turbulence, Octaves, Omega, BorderTransparency, CenterTransparency)
	#for(Layer, 0, 40, 1)
		sphere {
			<0, -WorldRadius, 0>, WorldRadius+Altitude+Layer*10
			texture {
				pigment {
					bozo turbulence Turbulence+0.004*Layer
					octaves Octaves+Layer*0.04 omega Omega+Layer*0.003 lambda 2
					pigment_map {
						[0.00 CloudColor(Altitude, Layer, CenterTransparency)]
						[Coverage-0.05-Layer*0.005 CloudColor(Altitude, Layer, BorderTransparency-Layer*0.004)]
						[Coverage+0.05+Layer*0.002 CloudColor(Altitude, Layer, 1.00)]
						[1.00 CloudColor(Altitude, Layer, 1.00)]
					}
					rotate<20, 20 , 0>
					scale <0.5, 0.3, 0.7> * WorldRadius * 0.001 * Scale
				}
				finish {ambient 1 diffuse 0}
			}
			hollow
		}
	#end
#end

CloudLayer(25000, 9, 0.40, 0.90, 11, 0.7, 0.70, 0.30)
CloudLayer(10000, 7, 0.30, 0.80, 11, 0.5, 0.45, 0.10)
CloudLayer(3000, 2, 0.35, 0.91, 12, 0.6, 0.40, 0.05)

plane {
	y,0
	texture {
		pigment
		{
			function { min(5 * sqrt(pow(x / AtmThickness, 2) + pow(z / AtmThickness, 2)), 1) }
			color_map {
				[0.00 color rgb <0,0,0>]
				[1.00 color rgb <1,0,0>]
			}
		}
		finish {ambient 1 diffuse 0}
	}
}
