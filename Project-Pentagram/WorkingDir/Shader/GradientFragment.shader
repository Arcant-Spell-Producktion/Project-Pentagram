#version 330 core

uniform vec4 u_Color;
// Use for converting to Grayscale
uniform sampler2D u_Texture;
// For Mapping current Gradient Color
uniform sampler2D u_StartGradient;
uniform sampler2D u_EndGradient;
// Interpolate Value between u_StartGradient and u_EndGradient [0, 1]
uniform float u_InterpolateValue;

in vec2 TexCoord;

out vec4 FragColor;

float ToGreyScale(vec3 color)
{
	float gs = dot(color, vec3(0.299f, 0.587f, 0.114f));
	return gs;
}

// All components are in the range [0…1], including hue.
vec3 rgb2hsv(vec3 c)
{
	vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
	vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
	vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

	float d = q.x - min(q.w, q.y);
	float e = 1.0e-10;
	return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

// All components are in the range [0…1], including hue.
vec3 hsv2rgb(vec3 c)
{
	vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
	vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
	return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main()
{
	vec4 baseTexture = texture(u_Texture, TexCoord);
	// If alpha less than 0.1f => Don't render
	if (baseTexture.a <= 0.1f)
	{
		discard;
	}

	float greyScale = ToGreyScale(baseTexture.rgb);

	vec3 startGradient = texture(u_StartGradient, vec2(greyScale, 0.5f)).rgb;
	vec3 endGradient = texture(u_EndGradient, vec2(greyScale, 0.5f)).rgb;

	// Convtert to HSV
	startGradient = rgb2hsv(startGradient);
	endGradient = rgb2hsv(endGradient);

	// Gradient from Higher Hue to Lower Hue
	if (endGradient.r > startGradient.r)
	{
		startGradient.r += 1.0f;
	}

	vec3 finalColor = mix(startGradient, endGradient, u_InterpolateValue);

	// finalColor.hue must be [0, 1]
	if (finalColor.r > 1.0f)
	{
		finalColor.r -= 1.0f;
	}

	FragColor = vec4(hsv2rgb(finalColor), 1.0f) * vec4(u_Color);
}