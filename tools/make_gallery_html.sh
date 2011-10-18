#!/bin/bash
# Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
echo '<script src="http://ajax.googleapis.com/ajax/libs/jquery/1/jquery.js"></script>'
echo '<script src="../galleria/galleria-1.2.5.min.js"></script>'
echo '<div id="gallery">'
for file
do echo '<img src="'$(basename ${file})'" title="Example '$(basename ${file} .png)'.cpp" longdesc="oglplus_2'$(basename ${file} .png)'_8cpp-example.html"/>'
done
echo '</div>'
echo '<script>'
echo '	Galleria.loadTheme("../galleria/themes/classic/galleria.classic.min.js");'
echo '	$("#gallery").galleria({'
echo '		width: 500,'
echo '		height: 500,'
echo '		autoplay: 1000'
echo '	});'
echo '</script>'
