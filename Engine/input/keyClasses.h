#pragma once
#include "Command.h"

class MoveLeft : public Command {
    void pressed(Entity& ent) override {
        ent.getComponent<PlayerMovementComponent>().setX_vel(-1.f);
    }
};

class MoveRight : public Command {
    void pressed(Entity& ent) override {
       ent.getComponent<PlayerMovementComponent>().setX_vel(1.f);
    }
    void released(Entity& ent) override {
        ent.getComponent<PlayerMovementComponent>().setX_vel(0);
    }
};

class MoveUp : public Command {
    void pressed(Entity& ent) override {
        ent.getComponent<PlayerMovementComponent>().setY_vel(1.f);
    }
};

class MoveDown : public Command {
    void pressed(Entity& ent) override {
        ent.getComponent<PlayerMovementComponent>().setY_vel(-1.f);
    }
    void released(Entity& ent) override {
        ent.getComponent<PlayerMovementComponent>().setY_vel(0);
    }
};

class MoveFaster : public Command {
    void pressed(Entity& ent) override {
        ent.getComponent<PlayerMovementComponent>().getSpeedMod() = 2; 
    }

    void released(Entity& ent) override {
        ent.getComponent<PlayerMovementComponent>().getSpeedMod() = 1;
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