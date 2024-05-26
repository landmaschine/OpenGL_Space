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

    ecs->player.addComponent<PositionComponent>(dep->data.player);
    ecs->player.addComponent<MovementComponent>(dep->data.player);
    ecs->player.addComponent<CollisionComponentPoly>(dep->data.player);
    ecs->player.addComponent<RenderComponent>(dep->data.player->texPath);

    ecs->collider.addComponent<PositionComponent>(5.f, 5.f, dep->data.backObj);
    ecs->collider.addComponent<CollisionComponentPoly>(dep->data.backObj);
    ecs->collider.addComponent<RenderComponent>(dep->data.backObj->texPath);

    ecs->collider1.addComponent<PositionComponent>(-5.f, -5.f, dep->data.backObj);
    ecs->collider1.addComponent<CollisionComponentPoly>(dep->data.backObj);
    ecs->collider1.addComponent<RenderComponent>(dep->data.backObj->texPath);

    //ecs->collider2.addComponent<PositionComponent>(5.f, -5.f, dep->data.backObj);
    //ecs->collider2.addComponent<CollisionComponentPoly>(dep->data.backObj);
    //ecs->collider2.addComponent<RenderComponent>(dep->data.backObj->texPath);

    ecs->sys_manager.addSystem<CollisionSystem>();
    ecs->sys_manager.addSystem<RenderSystem>();

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
    auto& playerMovement = ecs->player.getComponent<MovementComponent>();
    dep->cam.updatePosition(playerMovement.pos, dep->window);
    Physics::Movement().calcBehaviour(&ecs->player.getComponent<MovementComponent>(), dt);
    
    mousePos(&playerMovement);
    ecs->ent_manager.update();
    ecs->sys_manager.update(dt);
}

void render() {
    ecs->sys_manager.render(dep->cam, gameloopdata.shouldRenderHitbox);

    dep->debGui.newFrame();
    dep->debGui.showValue((const char*)(glGetString(GL_VERSION)), gameloopdata.frameTime, 1/gameloopdata.frameTime);
    dep->debGui.showVec("Player Pos", ecs->player.getComponent<MovementComponent>().pos);
    dep->debGui.showVec("player Vel", ecs->player.getComponent<MovementComponent>().velocity);
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

    delete ecs;
    glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    dep->window.size().w = width;
    dep->window.size().h = height;
    glViewport(0, 0, width, height);
    dep->cam.updatePosition(ecs->player.getComponent<MovementComponent>().pos, dep->window);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    if(yoffset >= 1) gameloopdata.zoom += 2;
    if(yoffset <= -1) gameloopdata.zoom -= 2;
    if(gameloopdata.zoom <= 1) gameloopdata.zoom = 1;
    if(gameloopdata.zoom >= 250) gameloopdata.zoom = 250;
    dep->cam.setZoom(gameloopdata.zoom);
}