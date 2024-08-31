#version 410 core

in float heightPercent;

uniform vec3 viewPos;

out vec4 color;

void main()
{

    //vec3 norm = normalize(mix(normalL, normalR, widthPercent));

    vec3 grassColorTip = vec3(0.5f, 0.5f, 0.1f);
    vec3 grassColorBase = vec3(0.05f, 0.2f, 0.01f);
    vec3 grassColor =  mix(grassColorBase, grassColorTip, pow(heightPercent, 4.0f));


    /*
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 lightDir = normalize(lightPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * vec3(1.0f);
    */

    color = vec4(grassColor, 1.0);
}
