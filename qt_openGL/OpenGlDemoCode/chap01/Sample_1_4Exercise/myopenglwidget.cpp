#include "myopenglwidget.h"

unsigned int VBOs[2],VAOs[2];


unsigned int shaderProgram,shaderProgram2;

float firstTriangle[]={
    -0.9f,-0.5f,0.0f,
    -0.0f,-0.5f,0.0f,
    -0.45f,0.5f,0.0f,
};

float fsecondTriangle[]={
    0.0f,-0.5f,0.0f,
    0.9f,-0.5f,0.0f,
    0.45f,0.5f,0.0f,
};

const char *vertexShaderSource = "#version 450 core\n"
                                 "layout (location=0) in vec3 aPos;\n" "void main()\n"
                                 "{\n"
                                 "gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
                                 "}\0";

const char *fragmentShaderSource = "#version 450 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n" "}\n\0";

const char *fragmentShader2Source = "#version 450 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "FragColor = vec4(1.0f,1.0f,0.0f,1.0f);\n" "}\n\0";

myOpenGLWidget::myOpenGLWidget(QWidget *parent)
    : QOpenGLWidget{parent}
{

}

void myOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glGenVertexArrays(2,VAOs);
    glGenBuffers(2,VBOs);

    //绑定VBO和VAO对象
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER,VBOs[0]);

    //为当前绑定到target的缓冲区对象创建一个新的数据存储
    //如果data不是NULL,则使用来自此指针的数据初始化数据存储

    glBufferData(GL_ARRAY_BUFFER,sizeof(firstTriangle),firstTriangle,GL_STATIC_DRAW);

    //告知显卡如何解析缓冲里的属性值
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    //开启VAO管理的第一个属性值
    glEnableVertexAttribArray(0);//VAO[0]的第一个属性

    //绑定VBO和VAO对象
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER,VBOs[1]);

    //为当前绑定到target的缓冲区对象创建一个新的数据存储
    //如果data不是NULL,则使用来自此指针的数据初始化数据存储

    glBufferData(GL_ARRAY_BUFFER,sizeof(fsecondTriangle),fsecondTriangle,GL_STATIC_DRAW);

    //告知显卡如何解析缓冲里的属性值
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    //开启VAO管理的第一个属性值
    glEnableVertexAttribArray(0);//VAO[1]的第一个属性

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);

    unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2,1,&fragmentShader2Source,NULL);
    glCompileShader(fragmentShader2);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);

    shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2,vertexShader);
    glAttachShader(shaderProgram2,fragmentShader2);
    glLinkProgram(shaderProgram2);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fragmentShader2);
}

void myOpenGLWidget::resizeGL(int w, int h)
{

}

void myOpenGLWidget::paintGL()
{
    glClearColor(0.2f,0.3f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES,0,3);

    glUseProgram(shaderProgram2);
    glBindVertexArray(VAOs[1]);
    glDrawArrays(GL_TRIANGLES,0,3);
}
