#include "myopenglwidget.h"

unsigned int VBO,VAO,EBO;
unsigned int shaderProgram;

float vertices[]={
    0.5f,0.5f,0.0f,
    0.5f,-0.5f,0.0f,
    -0.5f,-0.5f,0.0f,
    -0.5f,0.5f,0.0f
};

unsigned int indices[]={
    0,1,3,
    1,2,3
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


myOpenGLWidget::myOpenGLWidget(QWidget *parent)
    : QOpenGLWidget{parent}
{

}

void myOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    //绑定VBO和VAO对象
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    //为当前绑定到target的缓冲区对象创建一个新的数据存储
    //如果data不是NULL,则使用来自此指针的数据初始化数据存储

    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    //告知显卡如何解析缓冲里的属性值
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    //开启VAO管理的第一个属性值
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER,0);
//    glBindVertexArray(0);//解绑VAO？

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

//    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);//线方式显示

    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindVertexArray(0);
}

void myOpenGLWidget::resizeGL(int w, int h)
{
//    glViewport(0,0,w,h);
}

void myOpenGLWidget::paintGL()
{
    glClearColor(0.2f,0.3f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
//    glDrawArrays(GL_TRIANGLES,0,6);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,indices);
}
