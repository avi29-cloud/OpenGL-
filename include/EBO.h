//
// Created by avi on 25/10/26.
//

#ifndef OPENGL_EBO_H
#define OPENGL_EBO_H
#include <glad/glad.h>

class EBO // Stores indices used to select vertices for drawing.
{
public :
    GLuint ID; // OpenGL identifier for the element buffer.
    EBO(GLuint* indices, GLsizeiptr size); // Create the buffer and upload index data.

    void Bind(); // Attach this buffer as the active element buffer.
    void Unbind(); // Remove the active element-buffer binding.
    void Delete(); // Release the buffer's OpenGL resource.
};
#endif
