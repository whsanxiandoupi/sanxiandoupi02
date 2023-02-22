#include "myopenglwidget.h"

myOpenGLWidget::myOpenGLWidget(QWidget *parent)
    : QOpenGLWidget{parent}
{

}

void myOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
}

void myOpenGLWidget::resizeGL(int w, int h)
{

}

void myOpenGLWidget::paintGL()
{
    glClearColor(0.2f,0.3f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
