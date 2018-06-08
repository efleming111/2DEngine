#version 330 core

in vec2 texCoords;  

uniform sampler2D sprite; 

out vec4 OutputColor;

void main()
{
	vec4 pixel = texture(sprite, texCoords);
	if(pixel.a < .5)
		discard;

	OutputColor = pixel;
}