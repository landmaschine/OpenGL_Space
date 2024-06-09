#include "GameDependencies.h"
#include "game.h"

void init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    dep->window.createWindow(dep->data.win->width, dep->data.win->height, dep->data.win->winName);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to init GLAD!" << std::endl;
    }

    dep->debGui.Init(dep->window.getWin());
    glfwSetFramebufferSizeCallback(dep->window.getWin(), framebuffer_size_callback);
    glfwSetScrollCallback(dep->window.getWin(), scroll_callback);
    glViewport(0, 0, dep->window.size().w, dep->window.size().h);

    dep->cam.init(dep->window);

    std::cout << glGetString(GL_VERSION) << std::endl;

    //TODO: Handle entitie creation enterily over Json file
    ecs->player.addComponent<PositionComponent>(dep->data.player);
    ecs->player.addComponent<InputComponent>(dep->data.player);
    ecs->player.addComponent<PhysicsComponent>(dep->data.player);
    ecs->player.addComponent<CollisionComponentPoly>(dep->data.player);
    ecs->player.addComponent<RenderComponent>(dep->data.player->texPath);

    ecs->collider.addComponent<PositionComponent>(dep->data.collider);
    ecs->collider.addComponent<CollisionComponentPoly>(dep->data.collider);
    ecs->collider.addComponent<RenderComponent>(dep->data.backObj->texPath);

    ecs->collider1.addComponent<PositionComponent>(-5.f, -5.f, dep->data.backObj);
    ecs->collider1.addComponent<RenderComponent>(dep->data.backObj->texPath);

    ecs->sys_manager.addSystem<CollisionSystem>();
    ecs->sys_manager.addSystem<RenderSystem>();
    ecs->sys_manager.addSystem<PhysicsSystem>();

    dep->inputhandler.init(dep->window.getWin(), ecs->player);
    dep->inputhandler.bindKey(GLFW_KEY_W, std::make_shared<MoveUp>());
    dep->inputhandler.bindKey(GLFW_KEY_A, std::make_shared<MoveLeft>());
    dep->inputhandler.bindKey(GLFW_KEY_S, std::make_shared<MoveDown>());
    dep->inputhandler.bindKey(GLFW_KEY_D, std::make_shared<MoveRight>());
    dep->inputhandler.bindKey(GLFW_KEY_LEFT_SHIFT, std::make_shared<MoveFaster>());
    dep->inputhandler.bindKey(GLFW_KEY_F1, std::make_shared<SetFrameUnlimited>());
    dep->inputhandler.bindKey(GLFW_KEY_F2, std::make_shared<setVsync>());
}

void input() {
    dep->inputhandler.update();
    dep->inputhandler.shutdownKey();
    gameloopdata.shouldRenderHitbox = dep->inputhandler.shouldRenderHitbox();
}

void update(float dt) {
    dep->cam.updatePosition(ecs->player.getComponent<PositionComponent>().pos, dep->window);    
    mousePos(&ecs->player.getComponent<InputComponent>());
    ecs->sys_manager.update(dt);
    ecs->ent_manager.update();
}

void render() {
    ecs->sys_manager.render(dep->cam, gameloopdata.shouldRenderHitbox);

    dep->debGui.newFrame();
    dep->debGui.showValue((const char*)(glGetString(GL_VERSION)), gameloopdata.frameTime, 1/gameloopdata.frameTime);
    dep->debGui.showVec("Player Pos", ecs->player.getComponent<PositionComponent>().pos);
    dep->debGui.draw();

    glfwSwapBuffers(dep->window.getWin());
    glfwPollEvents(); 
}

void gameLoop::run() {
    init();

    double currentTime = glfwGetTime();
    const float timeStep = dep->data.physSim->timeStep;
    float accumulator = 0;

    while (!glfwWindowShouldClose(dep->window.getWin())) {
        
        double newTime = glfwGetTime();
        double frameTime = newTime - currentTime;

        if (frameTime > 0.25f) {
            frameTime = 0.25f;
        }

        currentTime = newTime;
        accumulator += frameTime;

        while (accumulator >= timeStep) {
            input();
            update(timeStep);
            accumulator -= timeStep;
        }
            render();

        double endtime = glfwGetTime();
        gameloopdata.frameTime = endtime - currentTime;
    }
    shutDown();
}


void shutDown() {
    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();

    delete ecs;
    glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    dep->window.size().w = width;
    dep->window.size().h = height;
    glViewport(0, 0, width, height);
    dep->cam.updatePosition(ecs->player.getComponent<PositionComponent>().pos, dep->window);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    if(yoffset >= 1) gameloopdata.zoom += 2;
    if(yoffset <= -1) gameloopdata.zoom -= 2;
    if(gameloopdata.zoom <= 1) gameloopdata.zoom = 1;
    if(gameloopdata.zoom >= 250) gameloopdata.zoom = 250;
    dep->cam.setZoom(gameloopdata.zoom);
}