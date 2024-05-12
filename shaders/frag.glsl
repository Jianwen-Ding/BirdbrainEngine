#version 410 core

in vec2 texCoord;
in vec3 v_vertexColors;

out vec4 FragColor;

uniform sampler2D u_givenTexture1;
uniform sampler2D u_givenTexture2;
uniform vec3 lightColor;

void main()
{
    FragColor = mix(texture(u_givenTexture2, texCoord),texture(u_givenTexture1, texCoord),0.2f);
}