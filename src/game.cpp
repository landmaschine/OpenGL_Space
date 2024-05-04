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
    stbi_set_flip_vertically_on_load(true);

    std::cout << glGetString(GL_VERSION) << std::endl;

    entities->player.addComponent<PositionComponent>(dep->data.player);
    entities->player.addComponent<MovementComponent>(dep->data.player);
    entities->player.addComponent<CollisionComponent>(dep->data.player);
    entities->player.addComponent<RenderComponent>(dep->data.player->texPath);

    entities->collider.addComponent<PositionComponent>(0.f, 0.f, dep->data.backObj);
    entities->collider.addComponent<CollisionComponent>(0.f, 0.f, dep->data.backObj);
    entities->collider.addComponent<RenderComponent>(dep->data.backObj->texPath);

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
    
    for(auto& re : entities->manager.entities) {
        if(re->hasComponent<RenderComponent>()) {
            re->getComponent<RenderComponent>().cam(&dep->cam);
        }
    }
}

void render() {
    dep->renderer.render();
    entities->manager.draw();

    dep->debGui.newFrame();
    dep->debGui.showValue((const char*)(glGetString(GL_VERSION)), gameloopdata.frameTime, 1/gameloopdata.frameTime);
    dep->debGui.showVec("Player Pos", entities->player.getComponent<MovementComponent>().pos);
    dep->debGui.showVec("player Vel", entities->player.getComponent<MovementComponent>().velocity);
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