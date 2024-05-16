#pragma once
#include "Engine/ECS/ECS.h"
#include "Engine/Tools/Json.h"

class Command {
    public:
        virtual ~Command() = default;
        virtual void pressed(Entity& ent) {};
        virtual void released(Entity& ent) {};
    
        Json data;
};