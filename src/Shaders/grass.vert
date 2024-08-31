#version 410 core
#include <FastNoiseLite>

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 instanceOffset;
uniform float time;
uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

uniform vec3 viewPos;

out float heightPercent;

/*https://www.shadertoy.com/view/ttc3zr*/
uint murmurHash11(uint src) {
    const uint M = 0x5bd1e995u;
    uint h = 1190494759u;
    src *= M; src ^= src>>24u; src *= M;
    h *= M; h ^= src;
    h ^= h>>13u; h *= M; h ^= h>>15u;
    return h;
}

/*https://www.shadertoy.com/view/ttc3zr*/
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

/*https://gist.github.com/companje/29408948f1e8be54dd5733a74ca49bb9*/
float map(float value, float min1, float max1, float min2, float max2) {
    return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

void main()
{
    vec3 pos = inPos;
    vec3 modelPos = vec3(modelMatrix * vec4(pos, 1.0f));
    float instanceHash = hash11(gl_InstanceID);

    float maxVertexHeight = 1.1f;
    heightPercent = pos.y / maxVertexHeight;
    float randomLeanAngle = hash11(instanceHash) * 0.8f;

    //widthPercent = smoothstep(-abs(pos.x), abs(pos.x), pos.x);

    //normal = vec3(0.0f, 0.0f, 1.0f);

    fnl_state props = fnlCreateState(1337);
    props.noise_type = FNL_NOISE_PERLIN;

    float windDirection = map(fnlGetNoise2D(props, (instanceOffset.x)*100.0f+time*10.0f, (instanceOffset.y)*100.0f+time*10.0f), -1.0f, 0.0f, 1.0f, 2*3.14159f);
    float windLeanAngle = fnlGetNoise2D(props, (instanceOffset.x)*30.0f+time*100.0f, (instanceOffset.y)*30.0f+time*100.0f);

    // More curvy towards the top
    mat3 grass = rotateX(randomLeanAngle + windLeanAngle*heightPercent) * rotateY(windDirection);
    pos *= grass;
    pos.xz += instanceOffset;

    /*
    normal = normalize(rotateX(-(randomLeanAngle + windLeanAngle*heightPercent)) * rotateY(-(windDirection)) * normal);
    vec3 viewDir = normalize(viewPos - pos);
    widthPercent = dot(viewDir, normal) >= 0.0f ? widthPercent : 1 - widthPercent;
    normal = dot(viewDir, normal) >= 0.0f ? normal : -normal;

    normalL = normalize(rotateY(3.14159 * 0.1f) * normal);
    normalR = normalize(rotateY(3.14159 * -0.1f) * normal);
    fragPos = vec3(modelMatrix * vec4(pos, 1.0));
    */
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0);
}