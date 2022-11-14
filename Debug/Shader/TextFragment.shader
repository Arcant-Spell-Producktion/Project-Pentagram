#version 330 core
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D u_Texture;
uniform vec4 u_TextColor;
uniform vec4 u_OutlineColor;

void main()
{
    vec2 tex = texture2D(u_Texture, TexCoord).rg;
    float fill = tex.r;
    if (u_OutlineColor.a > 0.0f)
    {
        float outline = tex.g;

        float alpha = max(fill, outline);
        vec3 mix_color = mix(mix(vec3(0.0), u_TextColor.rgb, fill), u_OutlineColor.rgb, outline);
        FragColor = vec4(mix_color, alpha);
    }
    else
    {
        FragColor = vec4(u_TextColor.rgb, fill);
    }

}