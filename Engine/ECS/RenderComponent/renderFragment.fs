#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 ourColor;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

void main()
{
    FragColor = vec4(ourColor, 1.0);
}