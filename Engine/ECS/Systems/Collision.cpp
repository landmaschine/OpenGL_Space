#include "Pyhsics.h"

bool Physics::Collision::AABB(const collRect& recA, const collRect& recB, CollisionSide& side) {
    float recARight = recA.pos.x + recA.w;
    float recBRight = recB.pos.x + recB.w;
    float recABottom = recA.pos.y + recA.h;
    float recBBottom = recB.pos.y + recB.h;

    bool collisionX = recARight >= recB.pos.x && recBRight >= recA.pos.x;
    bool collisionY = recABottom >= recB.pos.y && recBBottom >= recA.pos.y;

    if (collisionX && collisionY) {
        float overlapX = std::min(recARight, recBRight) - std::max(recA.pos.x, recB.pos.x);
        float overlapY = std::min(recABottom, recBBottom) - std::max(recA.pos.y, recB.pos.y);

        if (overlapX < overlapY) {
            side = CollisionSide::Horizontal;
        }
        else if (overlapX > overlapY) {
            side = CollisionSide::Vertical;
        }
        else {
            side = CollisionSide::Both;
        }
        return true;
    }
    else {
        side = CollisionSide::None;
        return false;
    }
}

void Physics::Collision::HandleCollision_Player(MovementComponent& move, CollisionSide& side) {
    switch(side) {
    case CollisionSide::Horizontal:
        move.direction = -move.direction;
        move.velocity.x = -move.velocity.x;
        move.velocity.y = move.velocity.y;
        move.pos = glm::vec3(0.0);
        break;
    case CollisionSide::Vertical:
        move.direction = -move.direction;
        move.velocity.x = move.velocity.x;
        move.velocity.y = -move.velocity.y;
        move.pos = glm::vec3(0.0);
        break;
    case CollisionSide::Both:
        break;
    case CollisionSide::None:
        break;
    }
}

glm::vec2 Physics::Collision::CalculateEdgeNormal(const glm::vec2& p1, const glm::vec2& p2) {
    glm::vec2 edgeNormal;
    edgeNormal.x = -(p2.y - p1.y);
    edgeNormal.y = p2.x - p1.x;
    
    float length = std::sqrt(edgeNormal.x * edgeNormal.x + edgeNormal.y * edgeNormal.y);
    if (length != 0) {
        edgeNormal.x /= length;
        edgeNormal.y /= length;
    }
    
    return edgeNormal;
}

void Physics::Collision::ProjectPolygon(const std::vector<glm::vec2>& polygon, const glm::vec2& axis, float& minProjection, float& maxProjection) {
    minProjection = INFINITY;
    maxProjection = -INFINITY;
    for (const auto& point : polygon) {
        float projection = point.x * axis.x + point.y * axis.y;
        minProjection = std::min(minProjection, projection);
        maxProjection = std::max(maxProjection, projection);
    }
}

bool Physics::Collision::Overlap(float min1, float max1, float min2, float max2) {
    return (max1 >= min2 && max2 >= min1);
}

bool Physics::Collision::CheckCollision(const std::vector<glm::vec2>& polygon1, const std::vector<glm::vec2>& polygon2) {
    std::vector<glm::vec2> edges;
    edges.reserve(polygon1.size() + polygon2.size());
    
    for (size_t i = 0; i < polygon1.size(); ++i) {
        const glm::vec2& p1 = polygon1[i];
        const glm::vec2& p2 = polygon1[(i + 1) % polygon1.size()];
        edges.push_back(CalculateEdgeNormal(p1, p2));
    }
    
    for (size_t i = 0; i < polygon2.size(); ++i) {
        const glm::vec2& p1 = polygon2[i];
        const glm::vec2& p2 = polygon2[(i + 1) % polygon2.size()];
        edges.push_back(CalculateEdgeNormal(p1, p2));
    }
    
    for (const auto& axis : edges) {
        float min1, max1, min2, max2;
        ProjectPolygon(polygon1, axis, min1, max1);
        ProjectPolygon(polygon2, axis, min2, max2);
        if (!Overlap(min1, max1, min2, max2))
            return false;
    }
    
    return true;
}