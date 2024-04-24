#include "GameDependencies.h"
#include "game.h"

void init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    dep->window.createWindow(800, 600);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fmt::println("Failed to init GLAD!");
    }

    dep->renderer.init();
    glfwSetFramebufferSizeCallback(dep->window.getWin(), framebuffer_size_callback);
    glfwSetCursorPosCallback(dep->window.getWin(), cusor_position_callback);
    glViewport(0, 0, dep->window.size().w, dep->window.size().h);

    entities->player.addComponent<PositionComponent>();
    entities->player.addComponent<MovementComponent>();
    entities->player.getComponent<MovementComponent>().getWindow(dep->window);
    entities->player.addComponent<RenderComponent>();
    entities->player.getComponent<RenderComponent>().getShaderID(dep->renderer.shaderID());
    
    dep->inputhandler.init(dep->window.getWin(), entities->player);
    dep->inputhandler.bindKey(GLFW_KEY_W, std::make_shared<MoveUp>());
    dep->inputhandler.bindKey(GLFW_KEY_S, std::make_shared<MoveDown>());
    dep->inputhandler.bindKey(GLFW_KEY_A, std::make_shared<MoveLeft>());
    dep->inputhandler.bindKey(GLFW_KEY_D, std::make_shared<MoveRight>());
    dep->inputhandler.bindKey(GLFW_KEY_LEFT_SHIFT, std::make_shared<MoveFaster>());
    dep->inputhandler.bindKey(GLFW_KEY_F2, std::make_shared<setVsync>());
    dep->inputhandler.bindKey(GLFW_KEY_F1, std::make_shared<SetFrameUnlimited>());

    dep->renderer.setProjectionOrto(dep->window);
}

void input() {
    dep->inputhandler.update();
    dep->inputhandler.shutdownKey();
}

void update(float dt) {
    entities->player.getComponent<MovementComponent>().frameTime(dt);
    entities->player.getComponent<RenderComponent>().rotTransforms() = entities->player.getComponent<MovementComponent>().rotTransform();
    entities->player.getComponent<RenderComponent>().transform() = entities->player.getComponent<MovementComponent>().transform();
    entities->player.getComponent<MovementComponent>().Pos() = entities->player.getComponent<RenderComponent>().Pos();
    
    dep->renderer.setProjectionOrto(dep->window);
    entities->manager.update();
}

void render() {
    dep->renderer.render();
    entities->manager.draw();
    
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
        double frameTime = newTime - currentTime;

        if(frameTime > 0.25f) {frameTime = 0.25f;}

        currentTime = newTime;
        accumulator += frameTime;

        while(accumulator >= timeStep) {
            //measureFPS([&]() {input();}, [&](){update(frameTime);}, [&](){render();});
            input();
            update(frameTime);
            render(); 

            accumulator -= frameTime;
        }
        //printFPS(frameTime);
    }
    shutDown();
}

void shutDown() {
    delete dep;
    glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    dep->window.size().w = width;
    dep->window.size().h = height;

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    int posX = (screenWidth - width) / 2;
    int posY = (screenHeight - height) / 2;

    glfwSetWindowPos(window, posX, posY);

    glViewport(0, 0, dep->window.size().w, dep->window.size().h);
    dep->renderer.setProjectionOrto(dep->window);
}

void cusor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    float center_x = static_cast<float>(width) / 2.0f;
    float center_y = static_cast<float>(height) / 2.0f;

    float x_window = static_cast<float>(xpos) - center_x;
    float y_window = center_y - static_cast<float>(ypos);

    entities->player.getComponent<MovementComponent>().mouseX(x_window);
    entities->player.getComponent<MovementComponent>().mouseY(y_window);

    fmt::print("x: {:} ", x_window);
    fmt::println(" y: {:}", y_window);
}