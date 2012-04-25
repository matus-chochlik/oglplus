@echo off
:: Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
:: Software License, Version 1.0. (See accompanying file
:: LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

SET oglplus_archive_items=^
	_prebuilt ^
	config ^
	doc ^
	etc ^
	example ^
	include ^
	source ^
	xslt ^
	LICENSE_1_0.txt ^
	README.txt ^
	CHANGELOG ^
	VERSION ^
	CMakeLists.txt ^
	configure.bat 

:: Get the current version
SET /P oglplus_version=<VERSION

:: make the zip file name
SET oglplus_archive_name=oglplus-%oglplus_version%.zip

zip -r -9 %oglplus_archive_name% %oglplus_archive_items% -x *.sdf *.swp
