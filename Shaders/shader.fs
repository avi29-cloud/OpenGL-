#version 330 core

// Receive texture coordinates and vertex color interpolated by the vertex shader.
in vec2 texCoord;
out vec4 FragColor;
in vec3 color;
// The application selects the texture unit used by this sampler.
uniform sampler2D tex0;

uniform vec4 lightColor;





void main(){
    // Sample the bound image at this fragment's interpolated texture coordinate.
    FragColor = texture(tex0,texCoord)* lightColor;
}