#include <stdio.h>
#include <cstring>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector.h>

GLuint VBO;
GLint gScaleLocation;
GLuint gTranslationLocation; 
GLuint gRotationLocation;
const char* pVSFileName="shader.vs";
const char* pFSFileName="shader.fs";


struct Matrix4f { // copied as i didn't have math3d.h
    float m[4][4];
    
    // Constructor to initialize the matrix
    Matrix4f(float a00, float a01, float a02, float a03,
             float a10, float a11, float a12, float a13,
             float a20, float a21, float a22, float a23,
             float a30, float a31, float a32, float a33) 
    {
        m[0][0] = a00; m[0][1] = a01; m[0][2] = a02; m[0][3] = a03;
        m[1][0] = a10; m[1][1] = a11; m[1][2] = a12; m[1][3] = a13;
        m[2][0] = a20; m[2][1] = a21; m[2][2] = a22; m[2][3] = a23;
        m[3][0] = a30; m[3][1] = a31; m[3][2] = a32; m[3][3] = a33;
    }
};

static void RenderSceneCB(){
    
    glClear(GL_COLOR_BUFFER_BIT);

  // static float Scale =0.0f;
  static float AngleInRadians =0.0f;  
  static float Delta =0.01f;

    AngleInRadians += Delta;
    if ((AngleInRadians>=1.5708f)||(AngleInRadians<=-1.5708f)){
        Delta*=-1.0f;
    }

    Matrix4f Rotation (cosf(AngleInRadians), -sinf(AngleInRadians),   0.0f,0.0f,
                       sinf(AngleInRadians),   cosf(AngleInRadians),  0.0f,0.0f,
                        0.0f,                    0.0f,                1.0f,0.0f,
                        0.0f,                    0.0f,                0.0f,1.0f);

   glUniformMatrix4fv(gRotationLocation, 1 , GL_TRUE, &Rotation.m[0][0]);                     
  /* Matrix4f Translation (1.0f, 0.0f, 0.0f, Scale *2,
                         0.0f, 1.0f, 0.0f, Scale,
                         0.0f, 0.0f, 1.0f, 0.0f,
                         0.0f, 0.0f, 0.0f, 1.0f);

    glUniformMatrix4fv(gTranslationLocation,1,GL_TRUE,&Translation.m[0][0]); //3rd parameter tells if the matrix is row major or column major (true means row major) ,4th parameter is just address of array  */                 

   // glUniform1f(gScaleLocation, Scale);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0,3, GL_FLOAT,GL_FALSE,0,0);

    glDrawArrays(GL_TRIANGLES,0,3);// with this first parameter the gpu now understands every 3 vertices will make a triangle

    glDisableVertexAttribArray(0);

    glutPostRedisplay();
    
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
    if (Success == 0){
        glGetProgramInfoLog(ShaderProgram , sizeof(ErrorLog),NULL,ErrorLog);
        fprintf(stderr,"Error linking Shader program '%s' \n",ErrorLog);
        exit(1);
    }
    /*gScaleLocation = glGetUniformLocation(ShaderProgram,"gScale");//anywhere after the link is fine ,or else shows error
    if (gScaleLocation == -1){
        printf("Error getting uniform location of gScale \n");
        exit(1);
    }*/

    glValidateProgram(ShaderProgram);
        glGetProgramiv(ShaderProgram,GL_VALIDATE_STATUS,&Success);

        if (!Success){
            glGetProgramInfoLog(ShaderProgram,sizeof(ErrorLog),NULL,ErrorLog);
            fprintf(stderr,"Invalid Shader Program : '%s' \n",ErrorLog);
            exit(1);
        }
    

    glUseProgram(ShaderProgram);

  /*  gTranslationLocation = glGetUniformLocation(ShaderProgram,"gTranslation");
    if (gTranslationLocation ==-1){
        fprintf(stderr,"uniform gtranslation not found in the shader \n");
    }*/
    gRotationLocation =glGetUniformLocation(ShaderProgram,"gRotation");
    if(gRotationLocation ==-1){
        fprintf(stderr,"uniform gRotation not found in the shader program \n");
    }
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