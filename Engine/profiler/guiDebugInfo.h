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

        void showVec(const char* name, glm::vec3 _pos) {
            ImGui::Begin(name);
            ImGui::Text("playerPos: %f, %f, %f", _pos.x, _pos.y, _pos.z);
            ImGui::End();
        }

         void showVec(const char* name, glm::vec2 _pos) {
            ImGui::Begin(name);
            ImGui::Text("playerPos: %f, %f", _pos.x, _pos.y);
            ImGui::End();
        }

        void showValue(const char* name, float var) {
            ImGui::Begin(name);
            ImGui::Text("%s: %f", name, var);
            ImGui::End();
        }

        void showBool(const char* name, bool var) {
            ImGui::Begin(name);
            ImGui::Text("%s: %d", name, var);
            ImGui::End();
        }

        void showValue(const char* name, float var, float var2) {
            ImGui::Begin(name);
            ImGui::Text("%f ms", var);
            ImGui::Text("%f fps", var2);
            ImGui::End();
        }
        
        void showValue(const char* name, glm::vec4 val) {
            ImGui::Begin(name);
            ImGui::Text("%f", val.x);
            ImGui::Text("%f", val.y);
            ImGui::Text("%f", val.z);
            ImGui::Text("%f", val.w);
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