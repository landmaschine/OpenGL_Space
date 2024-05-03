#pragma once
#include "Engine/math/math.h"
#include "Engine/RenderEngine/Window/window.h"

class Icamer2D {
    public:
        virtual glm::mat4 projection() = 0;
        virtual glm::mat4 view() = 0;
};

class Camera2D : public Icamer2D {
    public:
        Camera2D() {}

        void init(Window& win) {
            this->screenHeight = win.size().h;
            this->screenWidth = win.size().w;
            position = glm::vec3(0.0f);
            zoom = 50.f;

            shaderCam.loadShader("/home/leonw/Documents/dev/OpenGL_Space/Engine/Camera/camShader.vs",
                                 "/home/leonw/Documents/dev/OpenGL_Space/Engine/Camera/camShader.fs");

            updateProjectionMatrixOrto();
        }

        void updatePosition(glm::vec3 playerPosition, Window& window) {
            glm::vec2 playerScreenPos = glm::vec2(playerPosition.x + window.size().w, playerPosition.y + window.size().h);

            screenWidth = window.size().w;
            screenHeight = window.size().h;

            position.x = playerScreenPos.x - screenWidth;
            position.y = playerScreenPos.y - screenHeight;

            

            updateViewMatrix();
            updateProjectionMatrixOrto();
        }

        void setZoom(float newZoom) {
            zoom = newZoom;
            updateProjectionMatrixOrto();
        }

        void window(Window& win) {
            _window = win;
        }

        glm::mat4 getViewMatrix() const {
            return viewMatrix;
        }

        glm::mat4 getProjectionMatrix() {
            updateProjectionMatrixOrto();
            return projectionMatrix;
        }

        glm::mat4 projection() override {
            return projectionMatrix;
        }

        glm::mat4 view() override {
            return viewMatrix;
        }

    private:
        void updateViewMatrix() {
            viewMatrix = glm::lookAt(glm::vec3(position.x, position.y, zoom),
                         glm::vec3(position.x, position.y, position.z),
                         glm::vec3(0.0f, 1.0f, 0.0f));   
            shaderCam.setMat4("view", viewMatrix);
        }

        void updateProjectionMatrixOrto() {
            float zoomFactor = 1.0f / zoom;
            float halfScreenWidth = (float)screenWidth * 0.5f;
            float halfScreenHeight = (float)screenHeight * 0.5f;
            float left = -halfScreenWidth * zoomFactor;
            float right = halfScreenWidth * zoomFactor;
            float bottom = -halfScreenHeight * zoomFactor;
            float top = halfScreenHeight * zoomFactor;
            projectionMatrix = glm::ortho(left, right, bottom, top, -10000.0f, 10000.0f);
            shaderCam.setMat4("projection", projectionMatrix);
        }

        void updateProjectionMatrixPers(float fov) {
            projectionMatrix = glm::perspective(glm::radians(fov), screenWidth / float(screenHeight), -10.f, 10.f);
            shaderCam.setMat4("projection", projectionMatrix);
        }

        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
        glm::vec3 position;
        Window _window;
        float zoom = 1.0f;
        int screenWidth = 0;
        int screenHeight = 0;
        Shader shaderCam;
};