#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <fmt/core.h>

class Shader
{
public:
    unsigned int ID;

    Shader() {}
    void loadShader(const char* vertexPath, const char* fragmentPath);

    void use() {glUseProgram(ID);};

    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;

    private:
        void checkCompileErrors(unsigned int shader, std::string type);
};