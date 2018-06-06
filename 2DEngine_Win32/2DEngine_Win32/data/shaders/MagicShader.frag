#version 330 core

in vec2 texCoords;  

uniform sampler2D sprite; 
uniform float RGBalance;

out vec4 OutputColor;

void main()
{
	float green = RGBalance - .05;
	float red = 1.0 - green + .05;
	float blue = .05;
	
	vec4 pixel = texture(sprite, texCoords);
	if(pixel.a < .5)
		discard;

	OutputColor = vec4(red, green, blue, pixel.a);
}