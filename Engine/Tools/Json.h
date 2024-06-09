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
            m_data = json::parse(file);

            win->winName = m_data["app"]["name"];
            win->height = m_data["app"]["window"]["height"];
            win->width = m_data["app"]["window"]["width"];

            physSim->timeStep = m_data["PhysicsSim"]["timeStep"];
            
            player->pos.x = m_data["player"]["posx"];
            player->pos.y = m_data["player"]["posy"];
            player->pos.z = m_data["player"]["posz"];
            player->scale = m_data["player"]["scale"];
            player->accelSpeed = m_data["player"]["accelSpeed"];
            player->speedMod = m_data["player"]["speedMod"];
            player->collision = m_data["player"]["collision"];
            player->texPath = m_data["player"]["texture"];

            player->awake = m_data["player"]["Rigidbody"]["awake"];
            player->mass = m_data["player"]["Rigidbody"]["mass"];
            player->damping = m_data["player"]["Rigidbody"]["damping"];
            player->Static = m_data["player"]["Rigidbody"]["static"];
            player->angularDamping = m_data["player"]["Rigidbody"]["angularDamping"];
            player->inertia = m_data["player"]["Rigidbody"]["inertia"];

            collider->pos.x = m_data["collider"]["posx"];
            collider->pos.y = m_data["collider"]["posy"];
            collider->pos.z = m_data["collider"]["posz"];
            collider->scale = m_data["collider"]["scale"];
            collider->texPath = m_data["collider"]["texture"];
            collider->collision = m_data["collider"]["collision"];
            collider->mass = m_data["collider"]["Rigidbody"]["mass"];
            collider->damping = m_data["collider"]["Rigidbody"]["damping"];
            collider->awake = m_data["collider"]["Rigidbody"]["awake"];
            collider->Static = m_data["collider"]["Rigidbody"]["static"];
            collider->angularDamping = m_data["collider"]["Rigidbody"]["angularDamping"];
            collider->inertia = m_data["collider"]["Rigidbody"]["inertia"];

            backObj->posz = m_data["backObjs"]["posz"];
            backObj->scale = m_data["backObjs"]["scale"];
            backObj->texPath = m_data["backObjs"]["texture"];
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
        json m_data;
};