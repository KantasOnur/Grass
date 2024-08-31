#define GLM_ENABLE_EXPERIMENTAL
#include "Tile.h"

#include <iostream>

#include "glm/gtx/transform.hpp"

Tile::Tile(std::unique_ptr<Mesh> &&mesh, const int& tileSize, const int &tilesToBeDrawn)
    : Mesh(), mesh_(std::move(mesh)), tileSize_(tileSize), tilesToBeDrawn_(tilesToBeDrawn) {}

void Tile::draw(const Camera &camera)
{
    glm::vec2 cameraPosition = {camera.getPosition().x, camera.getPosition().z};

    auto updateTilePositionAndBorders = [&](glm::vec3 offset) {
        for (auto& border : currentTileBorders) {
            border += glm::vec2(offset.x, offset.z);
        }
        centerTilePosition_ = centerTilePosition_ + offset;
        mesh_->setPosition(centerTilePosition_);
    };

    if (cameraPosition.x > currentTileBorders[0].x) {
        updateTilePositionAndBorders(glm::vec3{tileSize_, 0.0f, 0.0f});
    } else if (cameraPosition.x < currentTileBorders[1].x) {
        updateTilePositionAndBorders(glm::vec3{-tileSize_, 0.0f, 0.0f});
    }

    if (cameraPosition.y > currentTileBorders[0].y) {
        updateTilePositionAndBorders(glm::vec3{0.0f, 0.0f, tileSize_});
    } else if (cameraPosition.y < currentTileBorders[2].y) {
        updateTilePositionAndBorders(glm::vec3{0.0f, 0.0f, -tileSize_});
    }

    int halfTiles = tilesToBeDrawn_ / 2;

    for(int x = -halfTiles; x <= halfTiles; ++x)
    {
        for(int y = -halfTiles; y <= halfTiles; ++y)
        {
            mesh_->setPosition(centerTilePosition_ + glm::vec3{tileSize_*x, 0.0f, tileSize_*y});
            mesh_->draw(camera);
            mesh_->setPosition(centerTilePosition_);
        }
    }

}
