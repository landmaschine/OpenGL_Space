#pragma once
#include "Engine/math/math.h"

typedef struct winData {
    int width;
    int height;
    std::string winName;
} winData;

typedef struct PhysicsSim {
    float timeStep;
}PhysicsSim;

typedef struct playerData {
    float mass;
    float damping;
    float angularDamping;
    float inertia;
    bool awake;
    bool Static;
    
    float accelSpeed;
    int speedMod;
    double scale;
    std::string texPath;
    std::string collision;
    glm::vec3 pos;
} playerData;

typedef struct background {
    int posz;
    double scale;
    std::string texPath;
} background;

typedef struct colliderData {
    float mass;
    float damping;
    float angularDamping;
    float inertia;
    bool awake;
    bool Static;
    glm::vec3 pos;
    double scale;
    std::string texPath;
    std::string collision;
} colliderData;