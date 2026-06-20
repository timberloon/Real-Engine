#version 330 core

layout (location = 0) in vec2 apos;
layout (location = 1) in vec2 TexCoords;
out vec2 TextureCoordinates;
uniform mat4 projection;

void main(){
    gl_Position = projection * vec4(apos,0.0,1.0);
    TextureCoordinates = TexCoords;
}