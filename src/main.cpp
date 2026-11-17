#include<iostream>
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include <math.h>
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include <stb/stb_image.h>
#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"

const unsigned int width =800;
const unsigned int height =800;


int main()
{
    // Initialize GLFW before requesting a window or OpenGL context.
    glfwInit();


// Tell glfw what version of Opengl we are using
    //In this case we are using OpenGl 3.3
    // Request an OpenGL 3.3 core-profile context.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    //Tell Glfw that we are using core profile
    //so that means we only have the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);


    //Vertices coordinates
    // Store each vertex's position, color, and texture coordinate in one interleaved array.
    GLfloat vertices[]=
        {  // coordinates                                       / colors     /TexCoord
             -0.5f,0.0f,0.5f,                           0.83f,0.70f,0.44f,      0.0f,0.0f,
             -0.5f,0.0f,-0.5f,                          0.83f,0.70f,0.44f,      5.0f,0.0f,
             0.5f,0.0f,-0.5f,                           0.83f,0.70f,0.44f,      0.0f,0.0f,
             0.5f,0.0f,0.5f,                            0.83f,0.70f,0.44f,      5.0f,0.0f,
             0.0f,0.8f,0.0f,                            0.92f,0.86f,0.76,       2.5f,5.0f

        };


    // Reuse the four vertices to form the two triangles of a rectangle.
    GLuint indices[] =
    {
        0,1,2,
        0,2,3,
        0,1,4,
        1,2,4,
        2,3,4,
        3,0,4
    };

    GLfloat lightVertices[] =
    { //     COORDINATES     //
        -0.1f, -0.1f,  0.1f, // 0: Bottom-Front-Left
        -0.1f, -0.1f, -0.1f, // 1: Bottom-Back-Left
         0.1f, -0.1f, -0.1f, // 2: Bottom-Back-Right
         0.1f, -0.1f,  0.1f, // 3: Bottom-Front-Right
        -0.1f,  0.1f,  0.1f, // 4: Top-Front-Left
        -0.1f,  0.1f, -0.1f, // 5: Top-Back-Left
         0.1f,  0.1f, -0.1f, // 6: Top-Back-Right
         0.1f,  0.1f,  0.1f  // 7: Top-Front-Right
    };

   GLuint lightIndices[]=
   {
       0,1,2,
       0,2,3,
       0,1,4,
       0,7,3,
       3,7,6,
       3,6,2,
       2,6,5,
       2,5,1,
       1,5,4,
       1,4,0,
       4,5,6,
       4,6,7

   };

// Create a glfw object of 800 by 800 pixels , naming it OpenGL
  GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL",NULL,NULL);

    // check if the window fails to create
    if (window ==NULL)
    {
        std::cout <<"failed to create a GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Introduce the window to current context
    glfwMakeContextCurrent(window);

    // Load GLAD after the OpenGL context is current so it can resolve entry points.
    gladLoadGL();

    // Specify the viewport of opengl window
    glViewport(0,0, width,height);
    // Compile the shaders and set up vertex input and GPU buffers.
    Shader shaderProgram(OPENGL_ASSET_DIR "/Shaders/shader.vs", OPENGL_ASSET_DIR "/Shaders/shader.fs");
    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));


    // Describe the position, color, and texture-coordinate offsets in each vertex.
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    Shader lightShader(OPENGL_ASSET_DIR "/Shaders/light.vs", OPENGL_ASSET_DIR "/Shaders/light.fs");

    VAO lightVAO;
    lightVAO.Bind();

    VBO lightVBO(lightVertices, sizeof(lightVertices));
    EBO lightEBO(lightIndices, sizeof(lightIndices));

    lightVAO.LinkAttrib(lightVBO,0,3,GL_FLOAT,3* sizeof(float),(void*)0);

    lightVAO.Unbind();
    lightVBO.Unbind();
    lightEBO.Unbind();

    glm::vec4 lightColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

    glm::vec3 lightPos =glm::vec3(0.5f,0.5f,0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel,lightPos);

    glm::vec3 pyramidPos =glm::vec3(0.0f,0.0f,0.0f);
    glm::mat4 pyramidModel = glm::mat4(1.0f);
    pyramidModel =glm::translate(pyramidModel,pyramidPos);

    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID,"model"),1,GL_FALSE,glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID,"lightColor"),lightColor.x,lightColor.y,lightColor.z,lightColor.w);
    shaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID,"model"),1,GL_FALSE,glm::value_ptr(pyramidModel));
    glUniform4f(glGetUniformLocation(shaderProgram.ID,"lightColor"),1.0f,1.0f,1.0f,1.0f);



    //Texture
  Texture piplup(OPENGL_ASSET_DIR "/resource files/Textures/brick.png",GL_TEXTURE_2D,GL_TEXTURE0,GL_RGBA,GL_UNSIGNED_BYTE);
  piplup.texUnit(shaderProgram,"tex0",0);

    glEnable(GL_DEPTH_TEST);

    Camera camera(width,height,glm::vec3(0.0f,0.0f,2.0f));
    // main while loop
     while (!glfwWindowShouldClose(window))
     {
         // Clear the frame, activate render resources, and draw the indexed rectangle.
         glClearColor(0.07f,0.13f,0.17f,1.0f);
         glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


        camera.Inputs(window);
         camera.updateMatrix(45.0f,1.0f,100.0f);
         shaderProgram.Activate();
         camera.Matrix(shaderProgram,"camMatrix");
         piplup.Bind();


         VAO1.Bind();
         glDrawElements(GL_TRIANGLES,sizeof(indices)/sizeof(int),GL_UNSIGNED_INT,0);

         lightShader.Activate();
         camera.Matrix(lightShader,"camMatrix");
         lightVAO.Bind();
         glDrawElements(GL_TRIANGLES,sizeof(lightIndices)/sizeof(int),GL_UNSIGNED_INT,0);
         // Present the rendered frame before processing the next iteration.
         glfwSwapBuffers(window);

         // Take care of all GLFW events
      glfwPollEvents();
     }

    // Release GPU resources before destroying the window and its context.
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    piplup.Delete();

    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}