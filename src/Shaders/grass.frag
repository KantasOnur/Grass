#version 410 core

in float widthPercent;
in vec3 fragPos;
in vec3 viewCameraPos;
in vec3 normalL;
in vec3 normalR;
in vec3 viewLightPos;
in vec3 viewDir;

uniform vec3 lightPos;
uniform vec3 viewPos;

out vec4 color;

void main()
{

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * vec3(1.0f);

    vec3 norm = normalize(mix(normalL, normalR, widthPercent));
    vec3 lightDir = normalize(viewLightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse =  0.4 * diff * vec3(1.0f);

    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewCameraPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 10);
    vec3 specular = specularStrength * spec * vec3(1.0f);

    color = vec4(ambient+diffuse+specular, 1.0);
}
