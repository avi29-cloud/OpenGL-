//
// Created by avi on 24/10/26.
//
#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr sie)
{
   // Allocate a GPU buffer and initialize it with the supplied vertex bytes.
   glGenBuffers(1, &ID);
   glBindBuffer(GL_ARRAY_BUFFER, ID);
   glBufferData(GL_ARRAY_BUFFER, sie, vertices, GL_STATIC_DRAW);
}

void VBO::Bind()
{
 // Select this buffer so later vertex-buffer operations use it.
 glBindBuffer(GL_ARRAY_BUFFER, ID);

}

void VBO::Unbind()
{
 // Prevent subsequent operations from accidentally changing this binding.
 glBindBuffer(GL_ARRAY_BUFFER,0 );
}

void VBO::Delete()
{
 // Return the allocated buffer resource to OpenGL.
 glDeleteBuffers(1, &ID);
}