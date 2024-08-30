#include "InstancedMesh.h"

#include "../../Game.h"

InstancedMesh::InstancedMesh(const std::vector<glm::vec2>& positions, const std::vector<Vertex> &vertices_, const std::vector<Index> &indices_, std::unique_ptr<Shader> &&shader)
    :   Mesh(vertices_, indices_, std::move(shader)), count_(positions.size())
{

    glBindVertexArray(vao_);
    glGenBuffers(1, &instanceVbo_);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*positions.size(), &positions[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(1, 1);
    glBindVertexArray(0);
}

void InstancedMesh::draw(const Camera &camera)
{
    shader_->bind();
    model_ = glm::translate(model_, position_);
    shader_->setMatrix4f("modelMatrix", model_);
    shader_->setMatrix4f("projectionMatrix", camera.getProjection());
    shader_->setMatrix4f("viewMatrix", camera.getView());
    shader_->setVec3f("viewPos", camera.getPosition());
    shader_->setVec3f("lightPos", {camera.getPosition()});
    shader_->setFloat1f("time", Game::window_->getTime());
    glBindVertexArray(vao_);
    glDrawElementsInstanced(GL_TRIANGLES, (int)indices_.size(), GL_UNSIGNED_INT, nullptr, count_);
    glBindVertexArray(0);
    shader_->unbind();
    resetTransform();
}
