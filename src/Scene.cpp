#include "Scene.h"

#include "Core/Mesh/Grass.h"
#include "Core/Mesh/Mesh.h"
#include "Core/Mesh/Tile.h"

Scene::Scene(const Window& window)
{
    std::unique_ptr<Grass> patchOfGrass = std::make_unique<Grass>(std::make_unique<Shader>("../src/Shaders/grass.vert", "../src/Shaders/grass.frag"));
    std::unique_ptr<Tile> tiledGrass = std::make_unique<Tile>(std::move(patchOfGrass), 6, 5);

    meshes_.emplace_back(std::move(tiledGrass));
    camera_ = std::make_unique<Camera>(window);
}

void Scene::render()
{
    meshes_[0]->draw(*camera_);
}
