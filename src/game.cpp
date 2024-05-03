#include "GameDependencies.h"
#include "game.h"

void init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    dep->window.createWindow(dep->data.win->width, dep->data.win->height, dep->data.win->winName);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to init GLAD!" << std::endl;
    }

    dep->debGui.Init(dep->window.getWin());
    dep->renderer.init();
    glfwSetFramebufferSizeCallback(dep->window.getWin(), framebuffer_size_callback);
    glfwSetScrollCallback(dep->window.getWin(), scroll_callback);
    glViewport(0, 0, dep->window.size().w, dep->window.size().h);

    dep->cam.init(dep->window);

    std::cout << glGetString(GL_VERSION) << std::endl;

    entities->player.addComponent<PositionComponent>();
    entities->player.getComponent<PositionComponent>().pos.x = dep->data.player->pos.x;
    entities->player.getComponent<PositionComponent>().pos.y = dep->data.player->pos.y;
    entities->player.getComponent<PositionComponent>().pos.z = dep->data.player->pos.z;
    entities->player.getComponent<PositionComponent>().scale = dep->data.player->scale;
    entities->player.getComponent<PositionComponent>().datainit();
    entities->player.addComponent<MovementComponent>();
    entities->player.getComponent<MovementComponent>().mass = dep->data.player->mass;
    entities->player.getComponent<MovementComponent>().accelSpeed = dep->data.player->accelSpeed;
    entities->player.getComponent<MovementComponent>().maxSpeed = dep->data.player->maxSpeed;
    entities->player.getComponent<MovementComponent>().datainit();
    entities->player.addComponent<CollisionComponent>();
    entities->player.addComponent<RenderComponent>();
    entities->player.getComponent<RenderComponent>().getCam(dep->cam);
    entities->player.getComponent<RenderComponent>().setModel("/home/leonw/Documents/dev/OpenGL_Space/Engine/assets/cube/cube.obj");

    entities->collider.addComponent<PositionComponent>(10.f, 10.f, 1.f);
    entities->collider.getComponent<PositionComponent>().pos.z = dep->data.backObj->posz;
    entities->collider.getComponent<PositionComponent>().scale = dep->data.backObj->scale;
    entities->collider.getComponent<PositionComponent>().datainit();
    entities->collider.addComponent<CollisionComponent>();
    entities->collider.getComponent<CollisionComponent>().datainit();
    entities->collider.addComponent<RenderComponent>();
    entities->collider.getComponent<RenderComponent>().getCam(dep->cam);
    entities->collider.getComponent<RenderComponent>().setModel("/home/leonw/Documents/dev/OpenGL_Space/Engine/assets/cube/cube.obj");

    entities->collider2.addComponent<PositionComponent>();
    entities->collider2.getComponent<PositionComponent>().pos.z = dep->data.backObj->posz;
    entities->collider2.getComponent<PositionComponent>().scale = dep->data.backObj->scale;
    entities->collider2.getComponent<PositionComponent>().datainit();
    entities->collider2.addComponent<CollisionComponent>();
    entities->collider2.getComponent<CollisionComponent>().datainit();
    entities->collider2.addComponent<RenderComponent>();
    entities->collider2.getComponent<RenderComponent>().getCam(dep->cam);
    entities->collider2.getComponent<RenderComponent>().setModel("/home/leonw/Documents/dev/OpenGL_Space/Engine/assets/cube/cube.obj");

    dep->inputhandler.init(dep->window.getWin(), entities->player);
    dep->inputhandler.bindKey(GLFW_KEY_W, std::make_shared<MoveUp>());
    dep->inputhandler.bindKey(GLFW_KEY_S, std::make_shared<MoveDown>());
    dep->inputhandler.bindKey(GLFW_KEY_A, std::make_shared<MoveLeft>());
    dep->inputhandler.bindKey(GLFW_KEY_D, std::make_shared<MoveRight>());
    dep->inputhandler.bindKey(GLFW_KEY_LEFT_SHIFT, std::make_shared<MoveFaster>());
    dep->inputhandler.bindKey(GLFW_KEY_F2, std::make_shared<setVsync>());
    dep->inputhandler.bindKey(GLFW_KEY_F1, std::make_shared<SetFrameUnlimited>());
}

void input() {
    dep->inputhandler.update();
    dep->inputhandler.shutdownKey();
}

void update(float dt) {
    auto& playerMovement = entities->player.getComponent<MovementComponent>();
    
    dep->cam.updatePosition(playerMovement.pos, dep->window);

    for(auto& e : entities->manager.entities) {
        if(e.get()->hasComponent<RenderComponent>()) {
            e.get()->getComponent<RenderComponent>().getCam(dep->cam);
        }
    }

    //Physics::PlanetRotation().planetRotation(&entities->collider.getComponent<PlanetComponent>(), dt);

    for(auto it1 = entities->manager.entities.begin(); it1 != entities->manager.entities.end(); ++it1) {
        for(auto it2 = std::next(it1); it2 != entities->manager.entities.end(); ++it2) {
            if((*it1)->hasComponent<CollisionComponent>() && (*it2)->hasComponent<CollisionComponent>()) {
                gameloopdata.col = Physics::Collision().AABB((*it1)->getComponent<CollisionComponent>().rect, (*it2)->getComponent<CollisionComponent>().rect, gameloopdata.side);
                switch(gameloopdata.side) {
                    case CollisionSide::Horizontal:
                        entities->player.getComponent<MovementComponent>().direction = -entities->player.getComponent<MovementComponent>().direction;
                        entities->player.getComponent<MovementComponent>().velocity.x = -entities->player.getComponent<MovementComponent>().velocity.x;
                        entities->player.getComponent<MovementComponent>().velocity.y = entities->player.getComponent<MovementComponent>().velocity.y;
                        break;
                    case CollisionSide::Vertical:
                        entities->player.getComponent<MovementComponent>().direction = -entities->player.getComponent<MovementComponent>().direction;
                        entities->player.getComponent<MovementComponent>().velocity.x = entities->player.getComponent<MovementComponent>().velocity.x;
                        entities->player.getComponent<MovementComponent>().velocity.y = -entities->player.getComponent<MovementComponent>().velocity.y;
                        break;
                    case CollisionSide::Both:
                        break;
                    case CollisionSide::None:
                        break;
                }
            }
        }
    }

    Physics::Movement().calcBehaviour(&entities->player.getComponent<MovementComponent>(), dt);

    int width, height;
    double ypos, xpos;
    glfwGetCursorPos(dep->window.getWin(), &xpos, &ypos);
    glfwGetWindowSize(dep->window.getWin(), &width, &height);
    float center_x = static_cast<float>(width) / 2.0f;
    float center_y = static_cast<float>(height) / 2.0f;
    float x_window = static_cast<float>(xpos) - center_x;
    float y_window = center_y - static_cast<float>(ypos);
    playerMovement.mouseX = x_window;
    playerMovement.mouseY = y_window;

    entities->manager.update(dt);
}

void render() {
    dep->renderer.render();
    entities->manager.draw();

    dep->debGui.newFrame();
    dep->debGui.showValue("time/FPS", gameloopdata.frameTime, 1/gameloopdata.frameTime);
    dep->debGui.showVec("Player Pos", entities->player.getComponent<MovementComponent>().pos);
    dep->debGui.showVec("player vel", entities->player.getComponent<MovementComponent>().velocity);
    dep->debGui.draw();

    glfwSwapBuffers(dep->window.getWin());
    glfwPollEvents(); 
}

void gameLoop::run() {
    init();

    double currentTime = 0;
    const float timeStep = 0.005f;
    float accumulator = 0;

    while(!glfwWindowShouldClose(dep->window.getWin())) {
        
        double newTime = glfwGetTime();
        gameloopdata.frameTime = 0;
        gameloopdata.frameTime = newTime - currentTime;

        if(gameloopdata.frameTime > 0.25f) {gameloopdata.frameTime = 0.25f;}

        currentTime = newTime;
        accumulator += gameloopdata.frameTime;

        while(accumulator >= timeStep) {
            //measureFPS([&]() {input();}, [&](){update(frameTime);}, [&](){render();});
            input();
            update(gameloopdata.frameTime);
            render(); 

            accumulator -= gameloopdata.frameTime;
        }
    }
    shutDown();
}

void shutDown() {
    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();

    delete entities;
    glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    dep->window.size().w = width;
    dep->window.size().h = height;
    glViewport(0, 0, width, height);
    dep->cam.updatePosition(entities->player.getComponent<MovementComponent>().pos, dep->window);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    if(yoffset >= 1) gameloopdata.zoom += 2;
    if(yoffset <= -1) gameloopdata.zoom -= 2;
    if(gameloopdata.zoom <= 1) gameloopdata.zoom = 1;
    if(gameloopdata.zoom >= 250) gameloopdata.zoom = 250;
    dep->cam.setZoom(gameloopdata.zoom);
}