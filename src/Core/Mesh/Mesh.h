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
    unsigned int vao_, vbo_, ibo_;
    std::unique_ptr<Shader> shader_;
    void initBuffers();

public:
    Mesh(const std::vector<Vertex>& vertices_, const std::vector<Index>& indices_, std::unique_ptr<Shader>&& shader);
    virtual void draw(const Camera& camera);
};

#endif //MESH_H
