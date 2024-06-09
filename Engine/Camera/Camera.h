#pragma once
#include "Engine/math/math.h"
#include "Engine/RenderEngine/Window/window.h"
#include "Engine/RenderEngine/Shaders/shader.h"

class Icamer2D {
    public:
        virtual glm::mat4 projection() = 0;
        virtual glm::mat4 view() = 0;
};

class Camera2D : public Icamer2D {
    public:
        Camera2D() {}

        void init(Window& win) {
            m_screenHeight = win.size().h;
            m_screenWidth = win.size().w;
            m_position = glm::vec3(0.0f);
            m_zoom = 50.f;

            m_shaderCam.loadShader("/home/leonw/Documents/dev/OpenGL_Space/Engine/Camera/camShader.vs",
                                   "/home/leonw/Documents/dev/OpenGL_Space/Engine/Camera/camShader.fs");

            updateProjectionMatrixOrto();
        }

        void updatePosition(glm::vec3 playerPosition, Window& window);
        void setZoom(float newZoom);
        void window(Window& win);
        glm::mat4 getViewMatrix() const;
        glm::mat4 getProjectionMatrix();
        glm::mat4 projection() override;
        glm::mat4 view() override;

    private:
        void updateViewMatrix();
        void updateProjectionMatrixOrto();
        void updateProjectionMatrixPers(float fov);

        glm::mat4 m_viewMatrix;
        glm::mat4 m_projectionMatrix;
        glm::vec3 m_position;
        Window m_window;
        float m_zoom = 1.0f;
        int m_screenWidth = 0;
        int m_screenHeight = 0;
        Shader m_shaderCam;
};