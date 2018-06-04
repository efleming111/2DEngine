#version 330 core

in vec2 texCoords;  

uniform sampler2D sprite; 
uniform float RGBalance;

out vec4 OutputColor;

void main()
{
	float red = 1.0 - RGBalance;
	float green = 1.0 - red;
	float blue = .05;
	
	vec4 pixel = texture(sprite, texCoords);
	if(pixel.a < .5)
		discard;

	OutputColor = vec4(red, green, blue, pixel.a);
}