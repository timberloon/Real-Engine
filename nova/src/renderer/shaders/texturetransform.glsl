#version 330 core

layout (location = 0) in vec2 apos;
layout (location = 1) in vec2 TexCoords;

uniform vec2 u_offset;
uniform vec2 u_scale;

out vec2 TextureCoordinates;

void main(){
    vec2 transformed = apos * u_scale + u_offset;
    gl_Position = vec4(transformed, 0.0, 1.0);
    TextureCoordinates = TexCoords;
}