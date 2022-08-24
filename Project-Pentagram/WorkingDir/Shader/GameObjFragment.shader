#version 330 core

uniform vec4 u_Color;
uniform sampler2D u_Texture;

in vec2 TexCoord;

out vec4 FragColor;

void main()
{
	// If alpha less than 0.1f => Don't render
	if (texture(u_Texture, TexCoord).a <= 0.1f)
	{
		discard;
	}

	FragColor = texture(u_Texture, TexCoord) * vec4(u_Color);
}