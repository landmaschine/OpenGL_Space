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
#include "Engine/ECS/MovementComponent.h"
#include "Engine/ECS/PositionComponent.h"
#include "Engine/ECS/PlanetComponent.h"
#include "Engine/ECS/RenderComponent/RenderComponent.h"
#include "Engine/ECS/Systems/Collision/CollisionSystem.h"
#include "Engine/ECS/Systems/RenderSystem/RenderSystem.h"

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
    Physics::CollisionInfo collinfo;
} loopata;
loopata gameloopdata;