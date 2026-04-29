#version 330 core

out vec4 fragcolor;
uniform vec4 u_clr;

in vec2 TextureCoordinates;
uniform sampler2D myTexture;

void main(){
    fragcolor = texture(myTexture,TextureCoordinates);
}   