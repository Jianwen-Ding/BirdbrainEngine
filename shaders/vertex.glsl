#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

uniform mat4 u_perspectiveMat;
uniform mat4 u_modelMat;
uniform mat4 u_rotationMat;
uniform mat4 u_rotationInverseQuat;

out vec3 v_vertexColors;
void main()
{
    v_vertexColors = color;
    vec4 newPos = u_perspectiveMat * u_modelMat * u_rotationMat * vec4(position,1.0f);
    gl_Position = newPos;
}