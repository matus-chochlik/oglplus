/*
 *  .file example/oglplus/qtgl_main.hpp
 *  Declares Qt/GL-based program main function for running examples
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef __OGLPLUS_EXAMPLE_QTGL_MAIN_HPP__
#define __OGLPLUS_EXAMPLE_QTGL_MAIN_HPP__

#include <QWidget>
#include <QGLWidget>
#include <QTime>

#include <memory>

#include "example.hpp"

QT_BEGIN_NAMESPACE
class QLabel;
class QStatusBar;
QT_END_NAMESPACE

// The GL-widget used by the example window
class OGLplusExampleGLWidget
 : public QGLWidget
{
private:
	Q_OBJECT

	static QGLFormat getGLFormat(void);

	int argc;
	char** argv;
	const char* screenshot_path;

	QTime qt_clock;
	oglplus::ExampleClock clock;
	std::shared_ptr<oglplus::Example> example;
protected:
	void initializeGL(void);
	void paintGL(void);
	void resizeGL(int width, int height);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

signals:
	void updatedGL(void);
	void exampleFinished(void);
public slots:
	void setWidth(int);
	void setHeight(int);
public:
	OGLplusExampleGLWidget(QWidget *parent, int, char**, const char*);
	~OGLplusExampleGLWidget(void);

	QSize minimumSizeHint(void) const;
	QSize sizeHint(void) const;
};

// The main example window
class OGLplusExampleWindow
 : public QWidget
{
private:
	Q_OBJECT

	OGLplusExampleGLWidget* gl_widget;

	QLabel* info_gl_vendor;
	QLabel* info_gl_renderer;
	QLabel* info_gl_version;

	QLabel* info_gl_width;
	QLabel* info_gl_height;

	QStatusBar* status_bar;
protected:
	void keyPressEvent(QKeyEvent *event);

public slots:
	void updateGLInfo(void);

public:
	OGLplusExampleWindow(int, char**, const char*);
};

#endif
