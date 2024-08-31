#ifndef GRASS_H
#define GRASS_H
#include "InstancedMesh.h"


class Grass : public InstancedMesh
{
private:
    static inline std::vector<Vertex> grassVertices_ = {
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

    static inline std::vector<Index> grassIndices_ = {
        // Level 1 (high detail)
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

        10, 11, 12,

        // Level 2 (medium detailed)
        0, 1, 2,
        1, 2, 3,

        2, 3, 8,
        3, 8, 9,

        8, 9, 12,

        // Level 3 (low detail)
        0, 1, 12
    };

public:
    Grass(std::unique_ptr<Shader>&& shader);
    void draw(const Camera &camera) override;
};



#endif //GRASS_H
