#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D tex;

void main()
{
    FragColor = texture(tex, TexCoords);
    //FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}