<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html;charset=UTF-8"/>
<meta http-equiv="Content-Type" content="text/xhtml;charset=UTF-8"/>
<meta name="author" content="Matus Chochlik"/>
<meta name="copyright" content="Copyright 2008-2021 Matus Chochlik"/>
<meta name="keywords" content="C++ OpenGL Graphics Library"/>
<meta name="description" content="C++ wrapper for the OpenGL&reg; C API"/>

<title>OGLplus - a C++ wrapper for modern OpenGL®.</title>

<link rel="icon" type="image/x-icon" href="favicon.ico"/>
<link rel="shortcut icon" type="image/x-icon" href="favicon.ico"/>

<link rel="stylesheet/less" type="text/css" href="oglplus.less"/>
<script src="less.js" type="text/javascript"></script>


<link href="https://oglplus.org/news.rss" rel="alternate" type="application/rss+xml" title="OGLplus news feed" />

<script type="text/javascript">
(function() {
    var po = document.createElement('script'); po.type = 'text/javascript'; po.async = true;
    po.src = 'https://apis.google.com/js/plusone.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(po, s);
})();
</script>
<link href="https://plus.google.com/+OglplusOrg/" rel="publisher" />
</head>
<body>
<div id="main-title">
<h1>OGLplus: a C++ wrapper for modern OpenGL&copy;</h1>
</div>
<div id="frame">
	<div id="head">
		<div id="top">
				Visit the <em>OGLplus</em> pages on
				<a href="https://github.com/matus-chochlik/eagine-all" style="text-decoration: none;">
					<img src="https://github.com/favicon.ico"
						style="border: 0;"
						alt="OGLplus (EAGine) on GitHub"
					/>
				</a>
				<a href="https://www.linkedin.com/groups/OGLplus-4592626" style="text-decoration: none;">
					<img src="https://www.linkedin.com/img/webpromo/btn_in_20x15.png"
						width="20" height="15"
						style="border: 0;"
						alt="OGLplus group on LinkedIn"
					/>
				</a>

				for recent news and more info.
				<hr class="top-div"/>
				<!-- AddThis Button BEGIN -->
				<div id="addthis-box" class="addthis_toolbox addthis_default_style ">
				<a class="addthis_button_tweet"></a>
				<a class="addthis_button_google_plusone" g:plusone:size="medium"></a>
				<a class="addthis_counter addthis_pill_style"></a>
				</div>
				<script type="text/javascript" src="https://s7.addthis.com/js/250/addthis_widget.js#pubid=xa-4f35537052d88ff3"></script>
				<!-- AddThis Button END -->
		</div>
		<div id="logo">
			<img src="oglplus/html/oglplus.png"/>
		</div>
	</div>

	<div id="content">
		<div id="main">
			<div class="content-section">
				<h3>Introduction</h3>
				<p><em>OGLplus</em> is a collection of open-source, cross-platform libraries which implement an object-oriented facade over the OpenGL® (version 3 and higher) and also OpenAL® (version 1.1) and EGL (version 1.4) C-language APIs. It provides wrappers which automate resource and object management and make the use of these libraries in C++ safer and more convenient. <a href="oglplus/html/index.html">Read more...</a></p>
			</div>

			<div class="content-section">
				<div id="quick-links" class="content-column-1">
					<h3>Get the code</h3>
					<ul>
						<li id="git-repo"><a href="https://github.com/matus-chochlik/eagine-all">GIT repository (EAGine)</a></li>
						<li id="git-repo"><a href="https://github.com/matus-chochlik/oglplus">GIT repository (OGLplus, deprecated)</a></li>
					</ul>
					<h3>Documentation</h3>
					<ul>
						<li id="readme"><a href="https://github.com/matus-chochlik/eagine-all#readme">README</a></li>
						<li id="doxygen-doc"><a href="https://matus-chochlik.github.io/oglplu2/doxygen/">Reference</a></li>
					</ul>
					<h3>Follow OGLplus</h3>
					<ul>
						<li id="github"><a href="https://github.com/matus-chochlik/eagine-all">GitHub</a></li>
						<li id="linkedin"><a href="https://www.linkedin.com/groups/OGLplus-4592626">LinkedIn group</a></li>
					</ul>
			  </div>
				<div id="features" class="content-column-2">
					<h3>Features</h3>
					<ul>
						<li><a href="oglplus/html/index.html#feat_auto_resource_management">Automatic resource management</a></li>
						<li><a href="oglplus/html/index.html#feat_type_safety">Type safety</a></li>
						<li><a href="oglplus/html/index.html#feat_error_handling">Error handling and diagnostic</a></li>
						<li><a href="oglplus/html/index.html#feat_interoperability_with_opengl">Interoperability with OpenGL C API</a></li>
						<li><a href="oglplus/html/index.html#feat_related_classes">Additional CG-related classes</a></li>
						<li><a href="oglplus/html/index.html#oglplus_object_description">Optional description of objects and resources</a></li>
						<li><a href="oglplus/html/index.html#oglplus_configurability">Configurability</a></li>
						<li>Utilities
						<ul>
							<li>Text rendering utilities</li>
							<li>Mesh loaders / generators</li>
							<li>Image loaders / generators</li>
						</ul>
						</li>
					</ul>
				</div>
			</div>

			<div class="content-section">
			<div id="screenshot-gallery" class="content-column-3">
				<script src="https://ajax.googleapis.com/ajax/libs/jquery/1/jquery.js"></script>
				<script src="galleria/galleria-1.2.5.min.js"></script>
				<div id="gallery">
					<img src="oglplus/html/007_voronoi.png"/>
					<img src="oglplus/html/021_translucent_arrow.png"/>
					<img src="oglplus/html/022_blender_mesh.png"/>
					<img src="oglplus/html/022_parallax_map.png"/>
					<img src="oglplus/html/023_sky.png"/>
					<img src="oglplus/html/026_furry_torus.png"/>
					<img src="oglplus/html/026_ssao.png"/>
					<img src="oglplus/html/026_stencil_shadow.png"/>
					<img src="oglplus/html/027_brain_scan_vis.png"/>
					<img src="oglplus/html/028_depth_map_sss.png"/>
					<img src="oglplus/html/028_ripples.png"/>
					<img src="oglplus/html/029_gpu_sort_tfb.png"/>
					<img src="oglplus/html/029_fire_hydrant.png"/>
					<img src="oglplus/html/030_light_rays.png"/>
					<img src="oglplus/html/030_pin_display.png"/>
					<img src="oglplus/html/031_brick_torus.png"/>
					<img src="oglplus/html/031_sketch.png"/>
					<img src="oglplus/html/032_bar_grid.png"/>
					<img src="oglplus/html/033_metal_and_glass.png"/>
					<img src="oglplus/html/033_steam.png"/>
					<img src="oglplus/html/040_jelly_cube.png"/>
				</div>
				<script>
					Galleria.loadTheme("galleria/themes/classic/galleria.classic.min.js");
					$("#gallery").galleria({
						width: 400,
						height: 400,
						autoplay: 2000
					});
				</script>
			</div>

			<div id=other" class="content-column-4">
				<h3>Media</h3>
				<ul>
					<li id="screenshots"><a href="oglplus/html/oglplus_screenshot_gallery.html">Screenshots</a></li>
					<li id="videos"><a href="https://plus.google.com/u/0/+OglplusOrg/videos">Videos</a></li>
				</ul>
				<h3>Related projects</h3>
				<ul>
					<li id="oglplus"><a href="https://github.com/matus-chochlik/oglplus">OGLplus</a></li>
				</ul>
				<h3>Other resources</h3>
				<ul>
					<li><a href="https://github.com/jjzazuet/jgl" title="Java wrapper for OpenGL 3 and higher by Jesús Zazueta">JGL</a> by Jesús Zazueta</li>
					<li><a href="https://onlygraphix.com/2014/01/18/oglplus-tutorialdeferred-renderer/" title="by Michael Ivanov at https://onlygraphix.com/">Tutorial: Deferred renderer</a> by Michael Ivanov</li>
				</ul>
			</div>
			</div>

		</div>
		<div id="right">
			<?php
				$xml = new DOMDocument();
				$xml->load('news.rss');

				$xsl = new DOMDocument;
				$xsl->load('rss2html.xsl');

				$proc = new XSLTProcessor();
				$proc->importStyleSheet($xsl);
				$proc->setParameter('', 'feed-name', 'news.rss');

				echo $proc->transformToXML($xml);
			?>
		</div>
	</div>
	<div id="footer">
		<em>Copyright &copy; 2008-2021</em> <strong>Matúš Chochlík</strong><br/>
		&lt;<a href="mailto:chochlik@gmail.com">chochlik -at -gmail.com</a>&gt;<br/>

		<p>Distributed under the Boost Software License, Version 1.0. (See a copy at
		<a href="https://www.boost.org/LICENSE_1_0.txt">www.boost.org/LICENSE_1_0.txt</a>)</p>
	</div>
</div>
</body>
</html>

