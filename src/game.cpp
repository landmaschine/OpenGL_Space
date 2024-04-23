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
    glViewport(0, 0, dep->window.size().w, dep->window.size().h);
    glfwSetFramebufferSizeCallback(dep->window.getWin(), framebuffer_size_callback);
    
    entities->player.addComponent<PositionComponent>();
    entities->player.addComponent<MovementComponent>();
    entities->player.getComponent<MovementComponent>().getWindow(dep->window);
    entities->player.addComponent<RenderComponent>();
    
    dep->inputhandler.init(dep->window.getWin(), entities->player);

    dep->inputhandler.bindKey(GLFW_KEY_W, std::make_shared<MoveUp>());
    dep->inputhandler.bindKey(GLFW_KEY_S, std::make_shared<MoveDown>());
    dep->inputhandler.bindKey(GLFW_KEY_A, std::make_shared<MoveLeft>());
    dep->inputhandler.bindKey(GLFW_KEY_D, std::make_shared<MoveRight>());
    dep->inputhandler.bindKey(GLFW_KEY_LEFT_SHIFT, std::make_shared<MoveFaster>());
    dep->inputhandler.bindKey(GLFW_KEY_F2, std::make_shared<setVsync>());
    dep->inputhandler.bindKey(GLFW_KEY_F1, std::make_shared<SetFrameUnlimited>());

    dep->renderer.shaderInit();
    dep->renderer.setProjectionOrto();
    

    entities->player.getComponent<RenderComponent>().getShaderID(dep->renderer.shaderID());
}

void input() {
    dep->inputhandler.update();
    dep->inputhandler.shutdownKey();
}

void update(float dt) {
    entities->player.getComponent<MovementComponent>().frameTime(dt);
    entities->player.getComponent<RenderComponent>().rotTransforms() = entities->player.getComponent<MovementComponent>().rotTransform();
    entities->player.getComponent<RenderComponent>().transform() = entities->player.getComponent<MovementComponent>().transform();
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
    glViewport(0, 0, width, height);
}