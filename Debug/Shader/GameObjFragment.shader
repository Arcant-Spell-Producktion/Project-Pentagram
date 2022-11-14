#version 330 core

uniform vec4 u_Color;
uniform sampler2D u_Texture;

in vec2 TexCoord;

out vec4 FragColor;

void main()
{
	vec4 textureResult = texture(u_Texture, TexCoord);
	// If alpha less than 0.1f => Don't render
	if (textureResult.a <= 0.1f)
	{
		discard;
	}

	FragColor = textureResult * vec4(u_Color);
}