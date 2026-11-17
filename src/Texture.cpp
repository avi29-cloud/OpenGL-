//
// Created by avi on 06/11/26.
//

#include "Texture.h"
#include <iostream>
Texture::Texture(const char* image, GLenum texType, GLenum slot , GLenum format , GLenum pixelType)
{
    type = texType; // Remember the target so later binding calls use the same texture type.
    int widthImg,heightImg, numColch; // stb_image fills these with the image dimensions and channel count.
    // Flip the image vertically to match OpenGL's texture-coordinate convention.
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load(image,&widthImg,&heightImg,&numColch,STBI_rgb_alpha);

    // Report a missing or unsupported image before attempting the GPU upload.
    if (!bytes) {
        std::cout << "Failed to load image!" << std::endl;
        // return or exit instead of continuing
    }

    // Create and bind the texture on the requested texture unit.
    glGenTextures(1,&ID);
    glActiveTexture(slot);
    glBindTexture(texType,ID);

    // Use nearest-neighbor sampling and repeat texture coordinates outside the image.
    glTexParameteri(texType,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(texType,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    glTexParameteri(texType,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(texType,GL_TEXTURE_WRAP_T,GL_REPEAT);

    // Upload the image pixels and generate mip levels for minified rendering.
    glTexImage2D(texType,0,GL_RGBA, widthImg, heightImg, 0,format,pixelType,bytes);
    glGenerateMipmap(texType);

    // stb_image owns the decoded data; release it after the GPU upload.
    stbi_image_free(bytes);
    glBindTexture(texType,0);

}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
  // Find the sampler uniform and connect it to the selected texture unit.
  GLuint tex0Uni = glGetUniformLocation(shader.ID,uniform);
    shader.Activate();
    glUniform1i(tex0Uni,unit);
}
void Texture::Bind()
{
  // Make this texture available to the active texture unit.
  glBindTexture(type,ID);
}
void Texture::Unbind()
{
    // Clear the texture binding for this target.
    glBindTexture(type,0);
}
void Texture::Delete()
{
 // Release the texture object from OpenGL.
 glDeleteTextures(1,&ID);
}