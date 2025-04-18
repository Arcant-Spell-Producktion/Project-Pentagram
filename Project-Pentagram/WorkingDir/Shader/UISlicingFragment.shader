#version 330 core

uniform vec4 u_Color;
uniform sampler2D u_Texture;

uniform vec2 u_Dimensions;
uniform vec2 u_TextureBorder;

// UI Slicing
uniform float u_Border;
uniform float u_SlicingMultiplier;
uniform vec2 u_SlicingRepeatValue;
uniform bool u_IsSlicing;
uniform int u_SlicingType;

uniform bool u_IsClip;
uniform float u_ClipPercent;

in vec2 TexCoord;
out vec4 FragColor;

float map(float value, float originalMin, float originalMax, float newMin, float newMax) 
{
    return (value - originalMin) / (originalMax - originalMin) * (newMax - newMin) + newMin;
}
// SlicingType::STRETCH
float processAxisStretch(float coord, float textureBorder, float windowBorder) 
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

// SlicingType::REPEAT
float mapRepeat(float value, float originalMin, float originalMax, float newMin, float newMax)
{
    float val = (value - originalMin) / (originalMax - originalMin) * (newMax - newMin) + newMin;
    while (val >= 1.0f - newMin)
    {
        val -= (1.0f - newMin - newMin);
    }
    return val;
}
float processAxisRepeat(float coord, float textureBorder, float windowBorder, float repeatValue)
{
    if (coord < windowBorder)
    {
        return map(coord, 0.0f, windowBorder, 0.0f, textureBorder);
    }
    else if (coord < 1.0f - windowBorder)
    {
        return mapRepeat(coord, windowBorder, 1.0f - windowBorder, textureBorder, repeatValue);
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
        // SlicingType::STRETCH
        if (u_SlicingType == 0)
        {
            vec2 newUV = vec2(
                processAxisStretch(TexCoord.x, u_TextureBorder.x, borders.x),
                processAxisStretch(TexCoord.y, u_TextureBorder.y, borders.y)
            );
            textureResult = texture(u_Texture, newUV);
        }
        // SlicingType::REPEAT
        else if (u_SlicingType == 1)
        {
            vec2 slicingRepeatValue = u_SlicingRepeatValue * (1.0f / u_SlicingMultiplier);
            vec2 newUV = vec2(
                processAxisRepeat(TexCoord.x, u_TextureBorder.x, borders.x, slicingRepeatValue.x),
                processAxisRepeat(TexCoord.y, u_TextureBorder.y, borders.y, slicingRepeatValue.y)
            );
            textureResult = texture(u_Texture, newUV);
        }
    }
    else
    {
        if (u_IsClip)
        {
            textureResult = texture(u_Texture, vec2(map(TexCoord.x, 0.0f, 1.0f, 0.0f, u_ClipPercent), TexCoord.y));
        }
        else
        {
            textureResult = texture(u_Texture, TexCoord);
        }
        // If alpha less than 0.1f => Don't render
        if (textureResult.a <= 0.1f)
        {
            discard;
        }
    }
    
    // Output the color
    FragColor = textureResult * vec4(u_Color);
}