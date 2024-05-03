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

