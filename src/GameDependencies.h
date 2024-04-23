#pragma once

#define FMT_HEADER_ONLY
#include "RenderEngine/OpenGL/Renderer.h"
#include <fmt/core.h>
#include "ECS/ECS.h"
#include "profiler/profiler.h"
#include "input/keyClasses.h"

#include "RenderEngine/Window/window.h"
#include "input/InputHandler.h"
#include "Engine/ECS/Components.h"

struct Gamedependencies {
    Window window;
    InputHandler inputhandler;
    Renderer renderer;
};
Gamedependencies* dep = new Gamedependencies;

struct Entities {
    Manager manager;
    Entity& player;

    Entities() : player(manager.addEntity())
                
    {}
};
Entities* entities = new Entities;