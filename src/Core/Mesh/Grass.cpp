#include "Grass.h"
#include "../../Game.h"
#include <iostream>
#include <random>
#define NUM_GRASS 128


std::vector<glm::vec2> createOffsets()
{
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

    return offsets;
}

Grass::Grass(std::unique_ptr<Shader> &&shader)
    : InstancedMesh(createOffsets(), grassVertices_, grassIndices_, std::move(shader)) {}

void Grass::draw(const Camera &camera)
{
    float distance = glm::length(camera.getPosition() - position_);
    shader_->bind();
    model_ = glm::translate(model_, position_);
    shader_->setMatrix4f("modelMatrix", model_);
    shader_->setMatrix4f("projectionMatrix", camera.getProjection());
    shader_->setMatrix4f("viewMatrix", camera.getView());
    shader_->setVec3f("viewPos", camera.getPosition());
    shader_->setFloat1f("time", Game::window_->getTime());
    glBindVertexArray(vao_);
    if(distance <= 3.0f) glDrawElementsInstanced(GL_TRIANGLES, 33, GL_UNSIGNED_INT, nullptr, count_);
    else if(distance > 3.0f && distance < 9.0f) glDrawElementsInstanced(GL_TRIANGLES, 15, GL_UNSIGNED_INT, (void*)(33*sizeof(Index)), count_);
    else glDrawElementsInstanced(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)((33+15)*sizeof(Index)), count_);
    glBindVertexArray(0);
    shader_->unbind();
    resetTransform();
}
