#ifndef MESH_H
#define MESH_H

#include "../Shader.h"
#include <glm/glm.hpp>
#include "../Camera.h"
#include <string>

struct Vertex
{
    glm::vec3 position;
};

using Index = unsigned int;

class Mesh
{
protected:
    std::vector<Vertex> vertices_;
    std::vector<Index> indices_;
    glm::vec3 position_ = glm::vec3(0.0f);
    glm::mat4 model_ = glm::mat4(1.0f);
    unsigned int vao_, vbo_, ibo_;
    std::unique_ptr<Shader> shader_;
    void initBuffers();
    Mesh() = default;

public:
    Mesh(const std::vector<Vertex>& vertices_, const std::vector<Index>& indices_, std::unique_ptr<Shader>&& shader);
    glm::vec3 getPosition() {return position_;}
    void setPosition(const glm::vec3& position);
    void transform(const glm::mat4& transformation);
    void resetTransform();
    virtual void draw(const Camera& camera);
};

#endif //MESH_H
