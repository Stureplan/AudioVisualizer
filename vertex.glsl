#version 400

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_color;
		
out vec4 color_frag;
out float y;

uniform mat4 MVP;
uniform float height;

vec4 minColor = vec4(0.0, 1.0, 1.0, 1.0);
vec4 maxColor = vec4(0.0, 0.0, 1.0, 1.0);


void main () 
{
	vec3 pos = vertex_position;

	float s = sin((pos.x) + height);
	//s = 1;
	float c = cos((pos.z) + height);
	pos.y = (s * c) * 0.4f;

	gl_Position = MVP * vec4(pos, 1.0f);


	//color_frag = vertex_color;
	color_frag = mix(minColor, maxColor, pos.y / 2.0f + 0.5f);
	//color_frag.w += max(pos.y, 0.05f);
	//color_frag.xyz += max(vec3(0.1f, pos.y, pos.y),vec3(0.1f, 0.1f, 0.1f));


	y = pos.y;
}