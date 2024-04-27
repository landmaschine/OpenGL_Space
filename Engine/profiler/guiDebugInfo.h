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

        void showVec(std::string name, glm::vec3 _pos) {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin(name.c_str());
            ImGui::Text("playerPos: %f, %f", _pos.x, _pos.y);
            ImGui::End();
            ImGui::Render();
        }

        void showValue(std::string name, float var) {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin(name.c_str());
            ImGui::Text("%s: %f", name.c_str(), var);
            ImGui::End();
            ImGui::Render();
        }


        void draw() {
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }
};