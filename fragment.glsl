#version 400

in vec4 color_frag;

out vec4 fragment_color;
void main () 
{
	//fragment_color = vec4(color_frag, 1.0f);
	fragment_color = color_frag;
}