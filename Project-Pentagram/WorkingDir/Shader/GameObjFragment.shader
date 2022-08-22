#version 330 core

uniform vec4 ObjColor;
uniform sampler2D ObjTexture;

in vec2 TexCoord;

out vec4 FragColor;

void main()
{
	// If alpha less than 0.1f => Don't render
	if (texture(ObjTexture, TexCoord).a <= 0.1f)
	{
		discard;
	}

	FragColor = texture(ObjTexture, TexCoord) * vec4(ObjColor);
}