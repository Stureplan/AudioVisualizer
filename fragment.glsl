#version 400

in vec4 color_frag;
in float y;

out vec4 fragment_color;

float rand(float n){return fract(sin(n) * 43758.5453123);}
//float rand(float n){return fract(sin(n) * 1137.5453123);}

void main () 
{
	//fragment_color = vec4(color_frag, 1.0f);
	fragment_color = color_frag;
}