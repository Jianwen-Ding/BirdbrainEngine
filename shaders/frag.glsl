#version 410 core

in vec3 v_vertexColors;

out vec4 FragColor;

void main()
{
    FragColor = vec4(v_vertexColors.x, v_vertexColors.y, v_vertexColors.z, 1.0f);
}