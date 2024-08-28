#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

class Shader
{
private:
    unsigned int id_;
    unsigned int createShader(GLenum type, const std::string& sourcePath);
    void createProgram(const std::vector<unsigned int>& shaders);

    std::unordered_map<std::string, int> uniformToLocation_;
public:
    Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const std::string& geometryShaderPath);
    ~Shader();

    void bind() const;
    void unbind() const;
    void bindTexture() const;
    GLint getUniformLocation(const std::string& name);
    void setMatrix4f(const std::string& name, const glm::mat4& val);
    void setVec3f(const std::string& name, const glm::vec3& val);
    void setVec2(const std::string &name, const glm::vec2 &val);
    void setFloat1f(const std::string& name, const float& val);
    void setInt(const std::string& name, const int& val);
    void setVec2Array(const int& size, const std::string& name, const glm::vec2* array);
    void instance(const int& size, const std::string& name, const glm::vec2* offsets, const int& vertexCount);
};

#endif //SHADER_H
