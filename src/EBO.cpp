//
// Created by avi on 25/10/26.
//
//
// Created by avi on 24/10/26.
//
#include "EBO.h"

EBO::EBO(GLuint* indices, GLsizeiptr sie)
{
    // Allocate an element buffer and upload the drawing indices.
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sie, indices, GL_STATIC_DRAW);
}

void EBO::Bind()
{
    // Select this index buffer for indexed draw calls.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

}

void EBO::Unbind()
{
    // Clear the current element-buffer binding.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0 );
}

void EBO::Delete()
{
    // Release the element buffer from OpenGL.
    glDeleteBuffers(1, &ID);
}