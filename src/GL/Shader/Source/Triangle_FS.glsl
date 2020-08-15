#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;

uniform float blend;

void main()
{
    FragColor = mix(texture(texture2, TexCoord), texture(texture3, TexCoord), blend);
}