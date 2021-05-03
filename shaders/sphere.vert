#version 330 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec3 vNormal;
uniform mat4 model_view;
uniform mat4 projection;
uniform float cursorX;
uniform float cursorY;
uniform float near;
uniform float far;
uniform vec3 translate;

out vec3 out_color;
out vec3 position;
out vec3 vN;

void main()
{
	vec4 vNormal = vec4(vNormal,0);
	
	vN	= normalize(model_view * vNormal).xyz;

	position = vPosition.xyz + translate;
	gl_Position = projection * model_view * vPosition;
}