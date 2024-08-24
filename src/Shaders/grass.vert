#version 410 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 instanceOffset;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

uniform vec3 viewPos;
uniform vec3 lightPos;

out float widthPercent;
out vec3 fragPos;
out vec3 viewCameraPos;
out vec3 normalL;
out vec3 normalR;
out vec3 viewLightPos;
out vec3 viewDir;


uint murmurHash11(uint src) {
    const uint M = 0x5bd1e995u;
    uint h = 1190494759u;
    src *= M; src ^= src>>24u; src *= M;
    h *= M; h ^= src;
    h ^= h>>13u; h *= M; h ^= h>>15u;
    return h;
}

float hash11(float src) {
    uint h = murmurHash11(floatBitsToUint(src));
    return uintBitsToFloat(h & 0x007fffffu | 0x3f800000u) - 1.0;
}

mat3 rotateY(float angle)
{
    float cosAngle = cos(angle);
    float sinAngle = sin(angle);
    mat3 rotationMatrix = mat3(
    cosAngle,  0.0f, sinAngle,
    0.0f,      1.0f, 0.0f,
    -sinAngle, 0.0f, cosAngle
    );
    return rotationMatrix;
}

mat3 rotateX(float angle)
{
    float cosAngle = cos(angle);
    float sinAngle = sin(angle);
    mat3 rotationMatrix = mat3(
    1.0f,    0.0f,      0.0f,
    0.0f, cosAngle, -sinAngle,
    0.0f, sinAngle,  cosAngle
    );
    return rotationMatrix;
}

float InverseLerp(float a, float b, float value) {
    return (value - a) / (b - a);
}

mat4 translate(vec3 translation) {
    return mat4(
    1.0, 0.0, 0.0, translation.x,
    0.0, 1.0, 0.0, translation.y,
    0.0, 0.0, 1.0, translation.z,
    0.0, 0.0, 0.0, 1.0
    );
}

void main()
{
    vec3 pos = inPos;
    float instanceHash = hash11(gl_InstanceID);
    float randomAngle = instanceHash * 2.0f * 3.14159;

    float maxVertexHeight = 1.1f;
    float heightPercent = pos.y / maxVertexHeight;
    float randomLeanAngle = hash11(instanceHash) * 0.5f * heightPercent;


    widthPercent = smoothstep(-abs(pos.x), abs(pos.x), pos.x);

    vec3 normal = vec3(0.0f, 0.0f, 1.0f);


    mat3 grass = rotateY(randomAngle) * rotateX(randomLeanAngle);
    pos = grass * pos;
    pos.xz += instanceOffset;


    normal = mat3(transpose(inverse(viewMatrix))) * grass * normal;
    viewDir = normalize(vec3(viewMatrix * vec4(lightPos, 1.0f)) - vec3(viewMatrix * vec4(pos, 1.0f)));
    float viewDirDotNormal = dot(viewDir, normal);
    float dotProductBool = step(0.0, viewDirDotNormal);

    widthPercent = mix( 1.0 - widthPercent, widthPercent, dotProductBool);
    normal = mix(-normal, normal, dotProductBool);

    normalL = rotateY(3.14159 * 0.3f) * normal;
    normalR = rotateY(3.14159 * -0.3f) * normal;

    fragPos = vec3(viewMatrix * vec4(pos, 1.0));
    viewLightPos = vec3(viewMatrix * vec4(lightPos, 1.0));

    viewCameraPos = vec3(viewMatrix * vec4(viewPos, 1.0f));
    gl_Position = projectionMatrix * viewMatrix * vec4(pos, 1.0);
}