#include "CollisionSystem.h"

void CollisionSystem::update(std::vector<std::unique_ptr<Entity>>& entities, float dt) {    
    for (auto it1 = entities.begin(); it1 != entities.end(); ++it1) {
        for (auto it2 = std::next(it1); it2 != entities.end(); ++it2) {
            if ((*it1)->hasComponent<CollisionComponentPoly>() && (*it2)->hasComponent<CollisionComponentPoly>()) {
                auto& poly1 = (*it1)->getComponent<CollisionComponentPoly>().polygon;
                auto& poly2 = (*it2)->getComponent<CollisionComponentPoly>().polygon;

                if (Collision().CheckCollision(poly1, poly2, m_collinfo)) {
                    std::cout << "Hello" << std::endl;
                } else {
                    std::cout << "nolle" << std::endl;
                }
            }
        }
    }
}