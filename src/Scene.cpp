#include "Scene.h"

#include <iostream>
#include <random>

#include "Core/Mesh/InstancedMesh.h"
#include "Core/Mesh/Mesh.h"
#include "Core/Mesh/Tile.h"

#define NUM_GRASS 128

/*
 *TODO: Implement some sort of chunking loading and unloading
 */


Scene::Scene(const Window& window)
{
    std::vector<Vertex> grassVertices = {
        // Base Quad
        {{-0.05f, 0.0f, -0.0f}},
        {{0.05f, 0.0f, -0.0f}},
        {{-0.05f, 0.25f, -0.0f}},
        {{0.05f, 0.25f, -0.0f}},

        // Second Quad
        {{-0.045f, 0.45f, -0.0f}},
        {{0.045f, 0.45f, -0.0f}},

        // Third Quad
        {{-0.04f, 0.7f, -0.0f}},
        {{0.04f, 0.7f, -0.0f}},

        // Fifth Quad
        {{-0.03, 0.9f, -0.0f}},
        {{0.03f, 0.9f, -0.0f}},

        // Sixth Quad
        {{-0.02f, 1.0f, -0.0f}},
        {{0.02f, 1.0f, -0.0f}},

        // Tip
        {{0.0f, 1.1f, 0.0f}}
    };

    std::vector<Index> grassIndiced = {
        0, 1, 2,
        1, 2, 3,

        2, 3, 4,
        3, 4, 5,

        4, 5, 6,
        5, 6, 7,

        6, 7, 8,
        7, 8, 9,

        8, 9, 10,
        9, 10, 11,

        10, 11, 12
    };

    std::vector<Vertex> planeVertices = {
        {{-4.0f, 0.0f, 4.0f}},
        {{-4.0f, 0.0f, -4.0f}},
        {{4.0f, 0.0f, 4.0f}},
        {{4.0f, 0.0f, -4.0f}}
    };
    std::vector<Index> planeIndices = {
        0, 1, 2,
        1, 2, 3
    };
    std::vector<glm::vec2> offsets;
    std::default_random_engine generator;
    std::uniform_real_distribution distribution(-0.2f,0.2f);



    for(int z = 0; z <= NUM_GRASS; z++)
    {
        for(int x = 0; x <= NUM_GRASS; x++)
        {
            offsets.push_back(glm::vec2((-3.0f+6.0f/NUM_GRASS*x + distribution(generator)), (-3.0f+6.0f/NUM_GRASS*z + distribution(generator))));
        }
    }


    std::unique_ptr<InstancedMesh> grassBlade = std::make_unique<InstancedMesh>(offsets, grassVertices, grassIndiced, std::make_unique<Shader>("Shaders/grass.vert", "Shaders/grass.frag"));
    auto plane = std::make_unique<Mesh>(planeVertices, planeIndices, std::make_unique<Shader>("Shaders/plane.vert", "Shaders/plane.frag"));
    std::unique_ptr<Tile> tiledPlane = std::make_unique<Tile>(std::move(plane), 8, 3);
    std::unique_ptr<Tile> tiledGrass = std::make_unique<Tile>(std::move(grassBlade), 6, 3);

    meshes_.emplace_back(std::move(tiledGrass));
    meshes_.emplace_back(std::move(tiledPlane));
    camera_ = std::make_unique<Camera>(window);
}

void Scene::render()
{
    meshes_[0]->draw(*camera_);
    //meshes_[1]->draw(*camera_);
}
