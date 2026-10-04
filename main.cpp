#include <stdio.h>
#include <cstring>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "vector.h"

GLuint VBO;
const char* pVSFileName="shader.vs";
const char* pFSFileName="shader.fs";

static void RenderSceneCB(){
    
    glClear(GL_COLOR_BUFFER_BIT);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0,3, GL_FLOAT,GL_FALSE,0,0);

    glDrawArrays(GL_TRIANGLES,0,3);// with this first parameter the gpu now understands every 3 vertices will make a triangle

    glDisableVertexAttribArray(0);
    
    glutSwapBuffers();
}


static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType ){
    GLuint ShaderObj = glCreateShader(ShaderType);

    if (ShaderObj == 0){
        fprintf(stderr,"Error creating shader type %d \n", ShaderType);
        exit(0);
    }

    const GLchar* p[1];
    p[0] = pShaderText;

    GLint Lengths[1];
    Lengths[0]=strlen(pShaderText);

    glShaderSource(ShaderObj,1,p,Lengths);
    glCompileShader(ShaderObj);

    GLint success;
    glGetShaderiv(ShaderObj,GL_COMPILE_STATUS,&success);

    if (!success){
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj,sizeof(InfoLog),NULL,InfoLog);
        fprintf(stderr,"Error Compiling Shader type %d: '%s'\n",ShaderType,InfoLog);
        exit(1);
    }
    glAttachShader(ShaderProgram, ShaderObj);
}

bool ReadFile(const char* filename, std::string& target) {//Readfile helper function
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    std::stringstream buffer;
    buffer << file.rdbuf();
    target = buffer.str();
    return true;
}

static void CompileShaders(){
    GLuint ShaderProgram = glCreateProgram();

    if (ShaderProgram ==0){
        fprintf(stderr, "Error creating Shader program \n");
        exit(1);
    }

    std::string vs, fs;

    if (!ReadFile(pVSFileName, vs)){
        exit(1);
    }

    AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);

    if (!ReadFile(pFSFileName, fs)){
        exit(1);
    }

    AddShader(ShaderProgram, fs.c_str(),GL_FRAGMENT_SHADER);

    GLint Success = 0;
    GLchar ErrorLog[1024] = {0};

    glLinkProgram(ShaderProgram);

    glGetProgramiv(ShaderProgram,GL_LINK_STATUS,&Success);
    if (Success =0){
        glGetProgramInfoLog(ShaderProgram , sizeof(ErrorLog),NULL,ErrorLog);
        fprintf(stderr,"Error linking Shader program '%s' \n",ErrorLog);
        exit(1);
    }

    glValidateProgram(ShaderProgram);
        glGetProgramiv(ShaderProgram,GL_VALIDATE_STATUS,&Success);

        if (!Success){
            glGetProgramInfoLog(ShaderProgram,sizeof(ErrorLog),NULL,ErrorLog);
            fprintf(stderr,"Invalid Shader Program : '%s' \n",ErrorLog);
            exit(1);
        }
    

    glUseProgram(ShaderProgram);
}
static void CreateVertexBuffer(){
      Vector3 Vertices[3];
      glEnable(GL_CULL_FACE);
      glFrontFace(GL_CW);
      
      Vertices[0] = Vector3(-1.0f, -1.0f,0.0f); //bottom left
      Vertices[1] = Vector3(0.0f,1.0f,0.0f); // top
      Vertices[2] = Vector3(1.0f, -1.0f,0.0f); //bottom right 

      glGenBuffers(1,&VBO);
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferData(GL_ARRAY_BUFFER,sizeof(Vertices),Vertices, GL_STATIC_DRAW);

}


int main (int argc , char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);

    int width = 1920;
    int height = 1080;
    glutInitWindowSize(width , height);

    int x = 200;
    int y = 100;

    glutInitWindowPosition(x,y);
    int win = glutCreateWindow("2nd  Window");
    printf("window id: %d\n",win);
    // Must be fone after glut is initialized 
    GLenum res = glewInit();
    if (res != GLEW_OK){
        fprintf(stderr, "error : '%s' \n",glewGetErrorString(res));
        return 1;
    }

    GLclampf Red =0.0f, Green =0.0f , Blue =0.0f , Alpha= 0.0f;
    glClearColor(Red, Green , Blue , Alpha);

    CreateVertexBuffer();
    CompileShaders();

    glutDisplayFunc(RenderSceneCB);//render callback

    glutMainLoop();

    return 0;
}