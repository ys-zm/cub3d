#version 330 core

in vec2 TexCoord;
flat in int TexIndex;

out vec4 FragColor;

uniform sampler2D Texture0;
uniform sampler2D Texture1;
uniform sampler2D Texture2;
uniform sampler2D Texture3;
uniform sampler2D Texture4;
uniform sampler2D Texture5;
uniform sampler2D Texture6;
uniform sampler2D Texture7;
uniform sampler2D Texture8;
uniform sampler2D Texture9;
uniform sampler2D Texture10;
uniform sampler2D Texture11;
uniform sampler2D Texture12;
uniform sampler2D Texture13;
uniform sampler2D Texture14;
uniform sampler2D Texture15;

void main()
{
    vec4 outColor = vec4(1.0, 1.0, 1.0, 1.0);
    FragColor = outColor;
}
