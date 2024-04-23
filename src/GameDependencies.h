#pragma once
#include <glad/glad.h>

#define FMT_HEADER_ONLY
#include <fmt/core.h>
#include "Engine/ECS/Components/Components.h"
#include "profiler/profiler.h"
#include "input/keyClasses.h"

#include "RenderEngine/Window/window.h"
#include "input/InputHandler.h"
#include "RenderEngine/OpenGL/Renderer.h"
#include "ECS/ECS.h"

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