#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <cstdlib>
#include "RenderEngine/OpenGL/Renderer.h"
#include "ECS/ECS.h"
#include "profiler/guiDebugInfo.h"
#include "profiler/profiler.h"
#include "input/keyClasses.h"

#include "RenderEngine/Window/window.h"
#include "input/InputHandler.h"
#include "Engine/Camera/Camera.h"
#include "Engine/ECS/depComponents.h"

#include "Engine/Tools/Json.h"
#include "Engine/Tools/extractColPolygon.h"

#include "Engine/ECS/CollisionComponent/CollisionComponentPoly.h"
#include "Engine/ECS/PositionComponent.h"
#include "Engine/ECS/PlanetComponent.h"
#include "Engine/ECS/RenderComponent.h"
#include "Engine/ECS/Systems/Collision/CollisionSystem.h"
#include "Engine/ECS/Systems/RenderSystem/RenderSystem.h"
#include "Engine/ECS/Systems/PhysicsSystem/PhysicsSystem.h"

#include "Engine/PhysicsEngine/Pyhsics.h"

struct Gamedependencies {
    Window window;
    InputHandler inputhandler;
    Camera2D cam;
    guiDeb debGui;
    Json data;
    PolyFromTxt colData;
};
Gamedependencies* dep = new Gamedependencies;

struct Ecs {
    Entities entities;
    EntityManager ent_manager = EntityManager(entities);
    SystemManager sys_manager = SystemManager(entities);
    
    Entity& player = ent_manager.addEntity();
    Entity& collider = ent_manager.addEntity();
    Entity& collider1 = ent_manager.addEntity();
    Entity& collider2 = ent_manager.addEntity();
};
Ecs* ecs = new Ecs;

typedef struct gameLoopData {
    double frameTime = 0;
    int zoom = 50;
    int col = 0;
    bool shouldRenderHitbox;
    Physics::CollisionInfo collinfo;
} loopata;
loopata gameloopdata;

void mousePos(InputComponent* input) {
    int width, height;
    double ypos, xpos;
    glfwGetCursorPos(dep->window.getWin(), &xpos, &ypos);
    glfwGetWindowSize(dep->window.getWin(), &width, &height);
    float center_x = static_cast<float>(width) / 2.0f;
    float center_y = static_cast<float>(height) / 2.0f;
    float x_window = static_cast<float>(xpos) - center_x;
    float y_window = center_y - static_cast<float>(ypos);
    input->mouseX = x_window;
    input->mouseY = y_window;
}