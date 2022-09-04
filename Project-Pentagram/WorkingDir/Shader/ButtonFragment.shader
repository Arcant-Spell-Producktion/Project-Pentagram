#version 330 core

uniform vec4 u_Color;
uniform sampler2D u_Texture;

uniform vec2 u_Dimensions;
uniform vec2 u_Border;

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
        return map(coord, 0, windowBorder, 0, textureBorder);
    }
    if (coord < 1 - windowBorder)
    {
        return map(coord, windowBorder, 1 - windowBorder, textureBorder, 1 - textureBorder);
    }
    return map(coord, 1 - windowBorder, 1, 1 - textureBorder, 1);
}

void main() 
{
    vec2 newUV = vec2(
            processAxis(TexCoord.x, u_Border.x, u_Dimensions.x),
            processAxis(TexCoord.y, u_Border.y, u_Dimensions.y)
    );
    
    vec4 textureResult = texture(u_Texture, newUV);
    
    // Output the color
    FragColor = textureResult * vec4(u_Color);
}