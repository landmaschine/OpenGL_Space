#include <iostream>
#include "RenderSystem.h"

void RenderSystem::render(Icamer2D& cam, bool renderhitbox, std::vector<std::unique_ptr<Entity>>& entities) {
    renderer.render();
    renderTex(cam, entities);
    if (renderhitbox) {
        renderHitbox(cam, entities);
    }
}

void RenderSystem::renderTex(Icamer2D& cam, std::vector<std::unique_ptr<Entity>>& entities) {
    shader.use();
    shader.setMat4("projection", cam.projection());
    shader.setMat4("view", cam.view());
    for (auto& e : entities) {
        if (e->hasComponent<RenderComponent>()) {
            auto& renderComponent = e->getComponent<RenderComponent>();
            shader.setMat4("model", renderComponent.model);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, renderComponent.texture);
            glBindVertexArray(renderComponent.VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
    }
}

void RenderSystem::renderHitbox(Icamer2D& cam, std::vector<std::unique_ptr<Entity>>& entities) {
    hitboxShader.use();
    hitboxShader.setMat4("projection", cam.projection());
    hitboxShader.setMat4("view", cam.view());

    for (auto& e : entities) {
        if (e->hasComponent<CollisionComponentPoly>()) {
            auto& collisionComponent = e->getComponent<CollisionComponentPoly>();
            hitboxShader.setMat4("model", collisionComponent.transform);

            glm::vec3 colpos = utils::extractTranslation(collisionComponent.transform);

            std::cout << colpos.x << " " << colpos.y << " " << colpos.z << std::endl;

            glBindVertexArray(collisionComponent.render.VAO);
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(collisionComponent.render.indices.size()), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        } else {
            std::cerr << "Entity missing CollisionComponentPoly" << std::endl;
        }
    }
}
