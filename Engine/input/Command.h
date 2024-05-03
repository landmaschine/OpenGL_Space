#pragma once
#include "Engine/ECS/ECS.h"
#include "Engine/ECS/Components.h"
#include "Engine/jsonParser/Json.h"

class Command {
    public:
        virtual ~Command() = default;
        virtual void pressed(Entity& ent) {};
        virtual void released(Entity& ent) {};
    
        Json data;
};