#version 410 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 instanceOffset;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

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

vec3 rotateY(vec3 vertex, float angle)
{
    float cosAngle = cos(angle);
    float sinAngle = sin(angle);
    mat3 rotationMatrix = mat3(
    cosAngle,  0.0f, sinAngle,
    0.0f,      1.0f, 0.0f,
    -sinAngle, 0.0f, cosAngle
    );
    return rotationMatrix * vertex;
}

void main()
{
    vec3 pos = inPos;
    float instanceHash = hash11(gl_InstanceID);
    float randomAngle = instanceHash * 2.0f * 3.14159;

    pos = rotateY(pos, randomAngle);
    pos.xz += instanceOffset;
    gl_Position = projectionMatrix * viewMatrix * vec4(pos, 1.0);

}