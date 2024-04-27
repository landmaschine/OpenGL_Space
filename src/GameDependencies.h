#pragma once

#define FMT_HEADER_ONLY
#include "RenderEngine/OpenGL/Renderer.h"
#include <fmt/core.h>
#include "ECS/ECS.h"
#include "profiler/guiDebugInfo.h"
#include "profiler/profiler.h"
#include "input/keyClasses.h"

#include "RenderEngine/Window/window.h"
#include "input/InputHandler.h"
#include "Engine/Camera/Camera.h"
#include "Engine/ECS/Components.h"

struct Gamedependencies {
    Window window;
    InputHandler inputhandler;
    Renderer renderer;
    Camera2D cam;
    guiDeb debGui;
};
Gamedependencies* dep = new Gamedependencies;

struct Entities {
    Manager manager;
    Entity& player;
    Entity& test;

    Entities() : player(manager.addEntity()),
                 test(manager.addEntity())
        
    {}
};
Entities* entities = new Entities;

typedef struct gameLoopData
{
    double frameTime = 0;
} loopData;

loopData gameloopdata;