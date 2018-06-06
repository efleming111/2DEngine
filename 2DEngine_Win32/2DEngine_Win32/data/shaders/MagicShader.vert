#version 330 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inTexture;

uniform mat4 model;
uniform mat4 camera;
uniform mat4 projection;

out vec2 texCoords;

void main()
{
	texCoords = inTexture;
	
	gl_Position = projection * camera * model * vec4(inPosition, 1.0);
}