#include "Pyhsics.h"
#include <algorithm>
#include <cfloat>

void Physics::Collision::HandleCollision_Player(PhysicsComponent& move, const glm::vec2& collisionNormal) {
    move.velocity -= 2.0f * glm::dot(move.velocity, collisionNormal) * collisionNormal;

    float restitution = 0.8f;
    move.velocity *= restitution;
}

glm::vec2 Physics::Collision::Support(const std::vector<glm::vec2>& poly1, const std::vector<glm::vec2>& poly2, const glm::vec2& direction) {
    glm::vec2 furthestPointInPoly1 = poly1[0];
    glm::vec2 furthestPointInPoly2 = poly2[0];
    
    float maxDot1 = glm::dot(furthestPointInPoly1, direction);
    float maxDot2 = glm::dot(furthestPointInPoly2, -direction);
    
    for (const auto& point : poly1) {
        float dotProduct = glm::dot(point, direction);
        if (dotProduct > maxDot1) {
            maxDot1 = dotProduct;
            furthestPointInPoly1 = point;
        }
    }
    
    for (const auto& point : poly2) {
        float dotProduct = glm::dot(point, -direction);
        if (dotProduct > maxDot2) {
            maxDot2 = dotProduct;
            furthestPointInPoly2 = point;
        }
    }
    
    return furthestPointInPoly1 - furthestPointInPoly2;
}

bool Physics::Collision::SameDirection(const glm::vec2& direction, const glm::vec2& ao) {
    return glm::dot(direction, ao) > 0;
}

bool Physics::Collision::CheckCollision(const PolyData& obj1, const PolyData& obj2, CollisionInfo& collisionInfo) {
    for (const auto& poly1 : obj1.Polygons) {
        for (const auto& poly2 : obj2.Polygons) {
            std::vector<glm::vec2> simplex;
            if (GJK(poly1, poly2, simplex)) {
                return EPA(poly1, poly2, simplex, collisionInfo);
            }
        }
    }
    return false;
}

glm::vec2 Physics::Collision::TripleProduct(const glm::vec2& a, const glm::vec2& b, const glm::vec2& c) {
    float ac = glm::dot(a, c);
    float bc = glm::dot(b, c);
    return b * ac - a * bc;
}

bool Physics::Collision::GJK(const std::vector<glm::vec2>& poly1, const std::vector<glm::vec2>& poly2, std::vector<glm::vec2>& simplex) {
    glm::vec2 direction(1, 0);
    simplex.push_back(Support(poly1, poly2, direction));
    direction = -simplex[0];

    while (true) {
        simplex.push_back(Support(poly1, poly2, direction));

        if (glm::dot(simplex.back(), direction) <= 0) {
            return false;
        }

        glm::vec2 a = simplex.back();
        glm::vec2 ao = -a;

        if (simplex.size() == 3) {
            glm::vec2 b = simplex[1];
            glm::vec2 c = simplex[0];

            glm::vec2 ab = b - a;
            glm::vec2 ac = c - a;

            glm::vec2 abPerp = TripleProduct(ac, ab, ab);
            glm::vec2 acPerp = TripleProduct(ab, ac, ac);

            if (SameDirection(abPerp, ao)) {
                simplex.erase(simplex.begin());
                direction = abPerp;
            } else {
                if (SameDirection(acPerp, ao)) {
                    simplex.erase(simplex.begin() + 1);
                    direction = acPerp;
                } else {
                    return true;
                }
            }
        } else {
            glm::vec2 b = simplex[0];
            glm::vec2 ab = b - a;
            glm::vec2 abPerp = TripleProduct(ab, ao, ab);

            direction = abPerp;
        }
    }
}

bool Physics::Collision::EPA(const std::vector<glm::vec2>& poly1, const std::vector<glm::vec2>& poly2, std::vector<glm::vec2>& simplex, CollisionInfo& collisionInfo) {
    const float EPA_TOLERANCE = 0.0001f;
    const int EPA_MAX_ITERATIONS = 100;
    int iterations = 0;

    while (iterations < EPA_MAX_ITERATIONS) {
        float minDistance = FLT_MAX;
        int closestEdgeIndex = 0;
        glm::vec2 closestEdgeNormal;

        for (int i = 0; i < simplex.size(); ++i) {
            int j = (i + 1) % simplex.size();
            glm::vec2 edge = simplex[j] - simplex[i];
            glm::vec2 normal = glm::vec2(edge.y, -edge.x);
            normal = glm::normalize(normal);

            float distance = glm::dot(normal, simplex[i]);
            if (distance < minDistance) {
                minDistance = distance;
                closestEdgeIndex = i;
                closestEdgeNormal = normal;
            }
        }

        glm::vec2 support = Support(poly1, poly2, closestEdgeNormal);
        float supportDistance = glm::dot(support, closestEdgeNormal);

        if (supportDistance - minDistance < EPA_TOLERANCE) {
            collisionInfo.collisionNormal = closestEdgeNormal;
            collisionInfo.penetrationDepth = supportDistance;
            collisionInfo.hasCollision = true;
            return true;
        } else {
            simplex.insert(simplex.begin() + closestEdgeIndex + 1, support);
        }

        iterations++;
    }

    collisionInfo.hasCollision = false;
    return false;
}
