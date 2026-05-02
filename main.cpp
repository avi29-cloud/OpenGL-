#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Callback function to resize the viewport when the window size changes
void framebuffer_size_callback(GLFWwindow* window , int width ,int height){
    glViewport(0,0,width, height);
}
int main(){
    if(!glfwInit()){
        std::cerr <<"failed to Initialize GLFW"<<std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR , 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR , 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE ,GLFW_OPENGL_CORE_PROFILE);


    //Create window object 
    GLFWwindow* window = glfwCreateWindow(800,600,"My first OpenGL Window ",NULL,NULL);//parameters

    if (window == NULL){
        std::cerr <<"failed to create GLFW window"<<std::endl;
        glfwTerminate();
        return -1;

    }    

    glfwMakeContextCurrent(window);//create a context of our window

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr <<"failed to initialize glad"<<std::endl;
        glfwTerminate();
        return -1;
    }
    glViewport(0,0,800,600);//tell openGL size of rendering window
   
    glfwSetFramebufferSizeCallback(window ,framebuffer_size_callback);


    //render loop

    while(!glfwWindowShouldClose(window)){
        //pressing escape to close the window 
        if (glfwGetKey(window , GLFW_KEY_ESCAPE)==GLFW_PRESS)
        glfwSetWindowShouldClose(window , true);

      //rendering;

      glClearColor(0.2f,0.3f,0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      //swap buffers and poll events 

      glfwSwapBuffers(window);

      glfwPollEvents();


    }
      
   glfwTerminate();
    return 0;
    
}



