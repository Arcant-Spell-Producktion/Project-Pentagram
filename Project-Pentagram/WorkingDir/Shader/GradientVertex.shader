#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexTexCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;
uniform mat4 u_WindowRatio;

uniform float u_OffsetX;
uniform float u_OffsetY;

out vec2 TexCoord;

void main()
{
	gl_Position = u_Projection * u_View * u_WindowRatio * u_Model * vec4(vertexPosition, 1.0f);
	TexCoord.x = vertexTexCoord.x + u_OffsetX;
	TexCoord.y = vertexTexCoord.y + u_OffsetY;
}