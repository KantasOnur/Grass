#ifndef MESH_H
#define MESH_H

#include "Shader.h"
#include <glm/glm.hpp>

#include "Camera.h"

struct Vertex
{
    glm::vec3 position;
};

using Index = unsigned int;

class Mesh
{
private:
    std::vector<Vertex> vertices_;
    std::vector<Index> indices_;
    std::unique_ptr<Shader> shader_;
    unsigned int vao_, vbo_, ibo_;
    void initBuffers();

public:
    Mesh(const std::vector<Vertex>& vertices_, const std::vector<Index>& indices_, std::unique_ptr<Shader>&& shader);
    void draw(const Camera& camera);
};

#endif //MESH_H
