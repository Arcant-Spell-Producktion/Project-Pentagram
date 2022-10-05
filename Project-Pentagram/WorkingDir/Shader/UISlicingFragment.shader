#version 330 core

uniform vec4 u_Color;
uniform sampler2D u_Texture;

uniform vec2 u_Dimensions;
uniform vec2 u_TextureBorder;
uniform float u_Border;
uniform float u_SlicingMultiplier;
uniform bool u_IsSlicing;

in vec2 TexCoord;
out vec4 FragColor;

float map(float value, float originalMin, float originalMax, float newMin, float newMax) 
{
    return (value - originalMin) / (originalMax - originalMin) * (newMax - newMin) + newMin;
}
float processAxis(float coord, float textureBorder, float windowBorder) 
{
    if (coord < windowBorder)
    {
        return map(coord, 0.0f, windowBorder, 0.0f, textureBorder);
    }
    else if (coord < 1.0f - windowBorder)
    {
        return map(coord, windowBorder, 1.0f - windowBorder, textureBorder, 1.0f - textureBorder);
    }
    else
    {
        return map(coord, 1.0f - windowBorder, 1.0f, 1.0f - textureBorder, 1.0f);
    }
}

void main() 
{
    vec4 textureResult;
    if (u_IsSlicing)
    {
        vec2 borders = vec2(u_Border) / u_Dimensions.xy * u_SlicingMultiplier;
        vec2 newUV = vec2(
                processAxis(TexCoord.x, u_TextureBorder.x, borders.x),
                processAxis(TexCoord.y, u_TextureBorder.y, borders.y)
        );
        textureResult = texture(u_Texture, newUV);
    }
    else
    {
        textureResult = texture(u_Texture, TexCoord);
        // If alpha less than 0.1f => Don't render
        if (textureResult.a <= 0.1f)
        {
            discard;
        }
    }
    
    // Output the color
    FragColor = textureResult * vec4(u_Color);
}