//
// Created by avi on 06/11/26.
//

#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H
#include <glad/glad.h>
#include <stb/stb_image.h>
#include "shaderClass.h"

class Texture // Loads an image and manages its OpenGL texture resource.
{
  public :
        GLuint ID; // OpenGL identifier for the texture.
        GLenum type; // Texture target used by bind and cleanup operations.
    Texture(const char* image, GLenum texType , GLenum slot , GLenum format, GLenum pixelType ); // Load image pixels and upload them as a texture.

    void texUnit(Shader& shader, const char* uniform, GLuint unit); // Assign the texture unit to a shader sampler.

    void Bind(); // Bind this texture for rendering.
    void Unbind(); // Clear the active texture binding.
    void Delete(); // Release the texture's OpenGL resource.

};
#endif
