#version 330 core

// Read position, vertex color, and texture coordinates from the configured VAO.
layout (location = 0) in vec3 aPos;
layout (location =1 ) in vec3 aColor;

layout (location =2) in vec2 aTex;

// Pass interpolated vertex data to the fragment shader.
out vec3 color;
out vec2 texCoord;

uniform mat4 camMatrix;

void main()
{
   // Expand or shrink each position component before projection.
   gl_Position = camMatrix * vec4(aPos,1.0);
   color =aColor;
   texCoord =aTex;
}