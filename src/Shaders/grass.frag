#version 410 core

in float heightPercent;

uniform vec3 lightPos;
uniform vec3 viewPos;

out vec4 color;

void main()
{
    vec3 grassColorTip = vec3(0.5f, 0.5f, 0.1f);
    vec3 grassColorBase = vec3(0.05f, 0.2f, 0.01f);
    vec3 grassColor =  mix(grassColorBase, grassColorTip, pow(heightPercent, 4.0f));
    color = vec4(grassColor, 1.0);
}
