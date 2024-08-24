#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "Core/Mesh/Mesh.h"
#include "Core/Camera.h"
class Scene
{
private:
    std::vector<std::unique_ptr<Mesh>> meshes_;
    std::unique_ptr<Camera> camera_;
    std::vector<glm::vec3> lightPositions_;
public:
    Scene(const Window& window);
    void render();
};



#endif //SCENE_H
