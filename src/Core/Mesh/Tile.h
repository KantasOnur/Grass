#ifndef TILE_H
#define TILE_H
#include "Mesh.h"
#include <memory>

class Tile : public Mesh
{
private:
    std::unique_ptr<Mesh> mesh_;
    const int tileSize_;
    const int tilesToBeDrawn_;
    std::vector<glm::vec2> currentTileBorders = {{4, 4}, {-4, 4}, {-4, -4}, {4, -4}};
    glm::vec3 centerTilePosition_ = {0.0f, 0.0f, 0.0f};
    int counter_ = 0;
public:
    Tile(std::unique_ptr<Mesh> &&mesh, const int& tileSize, const int &tilesToBeDrawn);
    void draw(const Camera &camera) override;
};



#endif //TILE_H
