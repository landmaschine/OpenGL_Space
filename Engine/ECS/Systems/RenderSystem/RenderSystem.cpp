#include "RenderSystem.h"

void RenderSystem::render(Icamer2D& cam, bool renderhitbox, std::vector<std::unique_ptr<Entity>>& entities) {
    renderer.render();
    shader.use();
    shader.setMat4("projection", cam.projection());
    shader.setMat4("view", cam.view());

    for (auto& e : entities) {
        if (e->hasComponent<RenderComponent>()) {
            shader.setMat4("model", e->getComponent<RenderComponent>().model);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, e->getComponent<RenderComponent>().texture);
            glBindVertexArray(e->getComponent<RenderComponent>().VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
    }

    if (renderhitbox) {
        renderHitbox(cam, entities);
    }
}

void RenderSystem::renderHitbox(Icamer2D& cam, std::vector<std::unique_ptr<Entity>>& entities) {
    for (auto& e : entities) {
        if (e->hasComponent<CollisionComponentPoly>()) {
            auto& hitboxShader = e->getComponent<CollisionComponentPoly>().render.hitboxShader;
            hitboxShader.use();
            hitboxShader.setMat4("view", cam.view());
            hitboxShader.setMat4("projection", cam.projection());
            hitboxShader.setMat4("model", e->getComponent<CollisionComponentPoly>().transform);

            glBindVertexArray(e->getComponent<CollisionComponentPoly>().render.VAO);
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(e->getComponent<CollisionComponentPoly>().render.indices.size()), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
    }
}