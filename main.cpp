
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector.h>

GLuint VBO;

static void RenderSceneCB(){
    
    glClear(GL_COLOR_BUFFER_BIT);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0,3, GL_FLOAT,GL_FALSE,0,0);

    glDrawArrays(GL_POINTS,0,1);

    glDisableVertexAttribArray(0);
    
    glutSwapBuffers();
}

static void CreateVertexBuffer(){
      Vector3 Vertices[1];
      Vertices[0] = Vector3(0.0f, 0.0f,0.0f);

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

    glutDisplayFunc(RenderSceneCB);//render callback

    glutMainLoop();

    return 0;
}