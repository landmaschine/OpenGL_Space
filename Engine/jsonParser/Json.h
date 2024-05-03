#pragma once
#include <fstream>
#include <iostream>
#include "lib/json.h"
using json = nlohmann::json;

typedef struct winData {
    int width;
    int height;
    std::string winName;
} winData;

typedef struct playerData {
    float mass;
    float accelSpeed;
    int speedMod;
    double maxSpeed;
    double scale;
    glm::vec3 pos;
} playerData;

typedef struct background {
    int posz;
    double scale;
} background;

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
            
            player->pos.x = data["player"]["posx"];
            player->pos.z = data["player"]["posy"];
            player->pos.y = data["player"]["posz"];
            player->scale = data["player"]["scale"];
            player->accelSpeed = data["player"]["accelSpeed"];
            player->speedMod = data["player"]["speedMod"];
            player->mass = data["player"]["mass"];
            player->maxSpeed = data["player"]["maxSpeed"];

            backObj->posz = data["backObjs"]["posz"];
            backObj->scale = data["backObjs"]["scale"];
        }

        background* backObj = new background;
        winData* win = new winData;
        playerData* player = new playerData;

        ~Json() {
            delete backObj;
            delete win;
            delete player;
        }
    private:
        json data;
};