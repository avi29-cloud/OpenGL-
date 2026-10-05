#version 330 core

layout (location = 0) in vec3 Position;

uniform float gScale;
uniform mat4 gTranslation;

void main(){
    vec4 scaledPosition = vec4(gScale * Position.x, gScale * Position.y, Position.z, 1.0);
    gl_Position = gTranslation * scaledPosition;
}