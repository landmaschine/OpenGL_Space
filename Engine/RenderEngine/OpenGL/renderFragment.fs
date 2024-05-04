#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 ourColor;

uniform sampler2D tex;

void main()
{
    FragColor = texture(tex, TexCoords);
}