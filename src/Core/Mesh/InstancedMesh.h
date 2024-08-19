#ifndef INSTANCEDMESH_H
#define INSTANCEDMESH_H
#include "Mesh.h"

class InstancedMesh : public Mesh
{
private:
    unsigned int instanceVbo_;
    int count_;
public:
    InstancedMesh(const std::vector<glm::vec2>& positions, const std::vector<Vertex>& vertices_, const std::vector<Index>& indices_, std::unique_ptr<Shader>&& shader);
    void draw(const Camera &camera) override;
};



#endif //INSTANCEDMESH_H
