#pragma once
#include "Engine/math/math.h"
#include "lib/Imgui.h"
#include "GLFW/glfw3.h"

class guiDeb {
    public:
        void Init(GLFWwindow* window) {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;
            ImGui::StyleColorsDark();
            ImGui_ImplGlfw_InitForOpenGL(window, true);
            ImGui_ImplOpenGL3_Init("#version 130");
        }

        void newFrame() {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
        }

        void showVec(std::string name, glm::vec3 _pos) {
            ImGui::Begin(name.c_str());
            ImGui::Text("playerPos: %f, %f", _pos.x, _pos.y);
            ImGui::End();
        }

        void showValue(std::string name, float var) {
            ImGui::Begin(name.c_str());
            ImGui::Text("%s: %f", name.c_str(), var);
            ImGui::End();
        }

        void showValue(std::string name, float var, float var2) {
            ImGui::Begin(name.c_str());
            ImGui::Text("%f", var);
            ImGui::Text("%f", var2);
            ImGui::End();
        }


        void draw() {
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        ~guiDeb() {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }
};