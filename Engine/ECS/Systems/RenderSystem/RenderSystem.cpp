#include "RenderSystem.h"

 void RenderSystem::render(Icamer2D& cam, bool renderhitbox, std::vector<std::unique_ptr<Entity>>& entities) {
    renderer.render();
    for(auto& e : entities) {
        if(e->hasComponent<RenderComponent>()) {
            shader.use();
            shader.setMat4("model", e->getComponent<RenderComponent>().model);
            shader.setMat4("projection", cam.projection());
            shader.setMat4("view", cam.view());

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, e->getComponent<RenderComponent>().texture);
            glBindVertexArray(e->getComponent<RenderComponent>().VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            
            renderHitbox(cam, entities);

            if(renderhitbox) {
            }
        }
    }
}

void RenderSystem::renderHitbox(Icamer2D& cam, std::vector<std::unique_ptr<Entity>>& entities) {
    for(auto& e : entities) {
        if(e->hasComponent<CollisionComponentPoly>()) {
            shader.use();
            shader.setMat4("view", cam.view());
            shader.setMat4("projection", cam.projection());
            shader.setMat4("model", e->getComponent<CollisionComponentPoly>().transform);

            glBindVertexArray(e->getComponent<CollisionComponentPoly>().render.VAO);
            glDrawElements(GL_TRIANGLES, e->getComponent<CollisionComponentPoly>().render.indices.size(), GL_UNSIGNED_INT, 0);
        }
    }
}