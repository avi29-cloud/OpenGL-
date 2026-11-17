//
// Created by avi on 08/11/26.
//

#ifndef OPENGL_CAMERA_H
#define OPENGL_CAMERA_H
#include "../../glad/glad.h"
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include "shaderClass.h"
#include "ShaderClass.h"

class Camera
{
     public:
            glm::vec3 position;
            glm::vec3 Orientation;
            glm::vec3 Up =glm::vec3(0.0f,1.0f,0.0f);

            int width;
            int height;


            float speed = 0.1f;
            float sensitivity = 100. 0f;

            Camera(int width , int height, glm::vec3 position);

            void Matrix(float FOVdeg,float nearPlane , Shader& shader ,const char* uniform);
            void Inputs(GLFWwindow* window);

#endif //OPENGL_CAMERA_H
