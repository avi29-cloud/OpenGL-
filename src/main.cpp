#include<iostream>
#include <../glad/glad.h>
#include<GLFW/glfw3.h>
#include <math.h>
#include <string>
#include <fstream>
#include <sstream>


std::string readShaderFile(const char* filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "ERROR: Could not open shader file: " << filePath << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}


int main()
{
    glfwInit();//Initialize GLFW


// Tell glfw what version of Opengl we are using
    //In this case we are using OpenGl 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    //Tell Glfw that we are using core profile
    //so that means we only have the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);


    //Vertices coordinates
    GLfloat vertices[]=
        {
             -0.5f,-0.5f* float(sqrt(3)) /3,0.0f,
             0.5f,-0.5f* float(sqrt(3)) /3,0.0f,
             0.0f, 0.5f* float(sqrt(3)) *2 /3,0.0f,
             -0.5f/2,0.5f* float(sqrt(3)) /6,0.0f,
             0.5f/2,0.5f* float(sqrt(3)) /6,0.0f,
             0.0f, -0.5f* float(sqrt(3)) *2 /3,0.0f
        };


    GLuint indices[] =
    {
        0,3,5,
        3,2,4,
        5,4,1
    };

// Create a glfw object of 800 by 800 pixels , naming it OpenGL
  GLFWwindow* window = glfwCreateWindow(800,800, "OpenGL",NULL,NULL);

    // check if the window fails to create
    if (window ==NULL)
    {
        std::cout <<"failed to create a GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Introduce the window to current context
    glfwMakeContextCurrent(window);

    // load GLAD so it configures OpenGL
    gladLoadGL();

    // Specify the viewport of opengl window
    glViewport(0,0, 800,800);

   //Create vertex and fragment shader object and get reference
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // 1. Read the files into std::string
    std::string vertexCode = readShaderFile("shader.vs");
    std::string fragmentCode = readShaderFile("shader.fs");

    // 2. Convert std::string to const char* for OpenGL
    const char* vertexShaderSource = vertexCode.c_str();
    const char* fragmentShaderSource = fragmentCode.c_str();

    // 3. Pass them to glShaderSource
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);


    //Create shader program object and get its reference
    GLuint shaderProgram =glCreateProgram();

    //attach vertex and fragment shader to the shader program
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);

    //wrap up / link all shaders together into the shader program
    glLinkProgram(shaderProgram);


    //Delete the now useless vertex and fragment shader object
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    //create refernece containers for the vertex array object and vertex buffer object
    GLuint VAO,VBO,EBO;

    //generate VAO and VBO with one object each
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1,&EBO);
  // make the vao the current vertex array object by binding it
    glBindVertexArray(VAO);

    //Bind the VBO specifying its a GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Introduce the vertices into the VBO
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices ,GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices,GL_STATIC_DRAW);

    //Configure the vertex attribute so that OpenGL knows how to read the VBO
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3* sizeof(float), (void*)0);

    //Enable the vertex attributes so that OpenGL knows to use it
    glEnableVertexAttribArray(0);

    // bind both so they won't accidentally modify each other
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);




    // specify the color of the background
    glClearColor(0.07f,0.13f,0.17f,1.0f);

    // Clean the back buffer and assign a new color to it
    glClear(GL_COLOR_BUFFER_BIT);

    // swap back buffer with front buffer
    glfwSwapBuffers(window);
    // main while loop
     while (!glfwWindowShouldClose(window))
     {
         glClearColor(0.07f,0.13f,0.17f,1.0f);
         glClear(GL_COLOR_BUFFER_BIT);
         glUseProgram(shaderProgram);
         glBindVertexArray(VAO);
         glDrawElements(GL_TRIANGLES,9,GL_UNSIGNED_INT,0);
         glfwSwapBuffers(window);

         // Take care of all GLFW events
      glfwPollEvents();
     }

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}