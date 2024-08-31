#ifndef INSTANCEDMESH_H
#define INSTANCEDMESH_H
#include "Mesh.h"

class InstancedMesh : public Mesh
{
protected:
    unsigned int instanceVbo_;
    int count_;
public:
    InstancedMesh(const std::vector<glm::vec2>& positions, const std::vector<Vertex>& vertices, const std::vector<Index>& indices, std::unique_ptr<Shader>&& shader);
    void draw(const Camera &camera) override;
};



#endif //INSTANCEDMESH_H
