#pragma once
#include <fstream>
#include <iostream>
#include "lib/json.h"
#include "Engine/math/math.h"
#include "datastructures.h"

using json = nlohmann::json;

class Json {
    public:
        Json() {
            std::ifstream file("/home/leonw/Documents/dev/OpenGL_Space/src/game.json");
            if(!file.is_open()) {
                std::cout << "failed to Open JSON" << std::endl;
            }
            data = json::parse(file);

            win->winName = data["app"]["name"];
            win->height = data["app"]["window"]["height"];
            win->width = data["app"]["window"]["width"];

            physSim->timeStep = data["PhysicsSim"]["timeStep"];
            
            player->pos.x = data["player"]["posx"];
            player->pos.y = data["player"]["posy"];
            player->pos.z = data["player"]["posz"];
            player->scale = data["player"]["scale"];
            player->accelSpeed = data["player"]["accelSpeed"];
            player->speedMod = data["player"]["speedMod"];
            player->collision = data["player"]["collision"];
            player->texPath = data["player"]["texture"];

            player->awake = data["player"]["Rigidbody"]["awake"];
            player->mass = data["player"]["Rigidbody"]["mass"];
            player->damping = data["player"]["Rigidbody"]["damping"];
            player->Static = data["player"]["Rigidbody"]["static"];
            player->angularDamping = data["player"]["Rigidbody"]["angularDamping"];
            player->inertia = data["player"]["Rigidbody"]["inertia"];

            collider->pos.x = data["collider"]["posx"];
            collider->pos.y = data["collider"]["posy"];
            collider->pos.z = data["collider"]["posz"];
            collider->scale = data["collider"]["scale"];
            collider->texPath = data["collider"]["texture"];
            collider->collision = data["collider"]["collision"];
            collider->mass = data["collider"]["Rigidbody"]["mass"];
            collider->damping = data["collider"]["Rigidbody"]["damping"];
            collider->awake = data["collider"]["Rigidbody"]["awake"];
            collider->Static = data["collider"]["Rigidbody"]["static"];
            collider->angularDamping = data["collider"]["Rigidbody"]["angularDamping"];
            collider->inertia = data["collider"]["Rigidbody"]["inertia"];

            backObj->posz = data["backObjs"]["posz"];
            backObj->scale = data["backObjs"]["scale"];
            backObj->texPath = data["backObjs"]["texture"];
        }

        background* backObj = new background;
        winData* win = new winData;
        playerData* player = new playerData;
        colliderData* collider = new colliderData;
        PhysicsSim* physSim = new PhysicsSim;

        ~Json() {
            delete physSim;
            delete collider;
            delete backObj;
            delete win;
            delete player;
        }

    private:
        json data;
};