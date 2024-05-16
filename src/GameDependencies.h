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
#include "Engine/ECS/CollisionComponent.h"
#include "Engine/ECS/MovementComponent.h"
#include "Engine/ECS/PositionComponent.h"
#include "Engine/ECS/PlanetComponent.h"
#include "Engine/ECS/RenderComponent/RenderComponent.h"

#include "Engine/ECS/Systems/Pyhsics.h"


struct Gamedependencies {
    Window window;
    InputHandler inputhandler;
    Renderer renderer;
    Camera2D cam;
    guiDeb debGui;
    Json data;
    PolyFromTxt colData;
};

Gamedependencies* dep = new Gamedependencies;

struct Entities {
    Manager manager;
    Entity& player;

    Entity& collider;
    Entity& collider2;
    Entity& collider3;

    Entities() : player(manager.addEntity()), collider(manager.addEntity()), collider2(manager.addEntity()), collider3(manager.addEntity())
    {

    }
};
Entities* entities = new Entities;

typedef struct gameLoopData
{
    double frameTime = 0;
    int zoom = 50;
    int col = 0;
    CollisionSide side;
} loopData;

loopData gameloopdata;