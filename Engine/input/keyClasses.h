#pragma once
#include "Command.h"

class MoveLeft : public Command {
    void pressed(Entity& ent) override {
        ent.getComponent<MovementComponent>().direction.x = -1;
    }
};

class MoveRight : public Command {
    void pressed(Entity& ent) override {
       ent.getComponent<MovementComponent>().direction.x = 1;
    }
    void released(Entity& ent) override {
        ent.getComponent<MovementComponent>().direction.x = 0;
    }
};

class MoveUp : public Command {
    void pressed(Entity& ent) override {
        ent.getComponent<MovementComponent>().direction.y = 1;
    }
};

class MoveDown : public Command {
    void pressed(Entity& ent) override {
        ent.getComponent<MovementComponent>().direction.y = -1;
    }
    void released(Entity& ent) override {
        ent.getComponent<MovementComponent>().direction.y = 0;
    }
};

class MoveFaster : public Command {
    void pressed(Entity& ent) override {
        ent.getComponent<MovementComponent>().speedMod = 2; 
    }

    void released(Entity& ent) override {
        ent.getComponent<MovementComponent>().speedMod = 1;
    }
};

class SetFrameUnlimited : public Command {
    void pressed(Entity& ent) override {
        glfwSwapInterval(0);
    }
};

class setVsync : public Command {
    void pressed(Entity& ent) override {
        glfwSwapInterval(1);
    }
};