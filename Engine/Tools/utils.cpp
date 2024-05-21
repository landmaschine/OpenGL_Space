#include "utils.h"

glm::vec3 utils::extractTranslation(const glm::mat4& matrix) {
        return glm::vec3(matrix[3][0], matrix[3][1], matrix[3][2]);
    }