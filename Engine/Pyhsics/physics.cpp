#include "physics.h"

void Movement::calcTransform(glm::mat4& trans, glm::mat4& rotMat, Window& _win, float dt, float& _mass, int& speedMod, glm::vec3& _vel, glm::vec2& _pos) {
    double x = 0;
    double y = 0;
    glfwGetCursorPos(_win.getWin(), &x, &y);

    // Bildschirmhöhe abrufen
    int screenWidth, screenHeight;
    glfwGetWindowSize(_win.getWin(), &screenWidth, &screenHeight);

    // GLFW-Koordinaten in OpenGL-Koordinaten umrechnen (Y-Achse umkehren)
    y = screenHeight - y;

    // Berechne die Mitte des Dreiecks
    glm::vec2 triangleCenter = _pos + glm::vec2(0.5f, 0.5f); // Annahme: Das Dreieck hat eine Breite und Höhe von 1.0

    // Berechne den Vektor von der Mitte des Dreiecks zum Cursor
    glm::vec2 triangleToCursor = glm::vec2(x, y) - triangleCenter;

    // Berechne den Winkel zwischen dem Vektor und der X-Achse
    float cursorangle = atan2(triangleToCursor.y, triangleToCursor.x);

    // Aktualisiere die Translationsmatrix für die Bewegung des Dreiecks
    trans = glm::translate(trans, _vel * glm::vec3(1.f * dt * speedMod, 1.f * dt * speedMod, 0.0f));

    // Aktualisiere die Rotationsmatrix, um das Dreieck um seinen Mittelpunkt zu drehen
    // Die Rotation wird um den Winkel cursorangle um die z-Achse durchgeführt
    rotMat = glm::translate(glm::mat4(1.0f), glm::vec3(triangleCenter, 0.0f)) *
             glm::rotate(glm::mat4(1.0f), cursorangle, glm::vec3(0.0f, 0.0f, 1.0f)) *
             glm::translate(glm::mat4(1.0f), glm::vec3(-triangleCenter, 0.0f));
}
