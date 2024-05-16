#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Engine/math/math.h"

struct Polygon {
    std::vector<glm::vec2> points;
};

class XML {
    public:
        std::vector<Polygon> extractPolyFromXML(const std::string& filePath) {
        std::vector<Polygon> polygons;
            std::ifstream file(filePath);
            std::string line;
            while (std::getline(file, line)) {
                if (line.find("<polygon") != std::string::npos) {
                    Polygon polygon;
                    while (std::getline(file, line) && line.find("</polygon>") == std::string::npos) {
                        if (line.find("<vertex") != std::string::npos) {
                            glm::vec2 point;
                            size_t pos = line.find("x=\"") + 3;
                            point.x = std::stof(line.substr(pos, line.find("\"", pos) - pos));
                            pos = line.find("y=\"") + 3;
                            point.y = std::stof(line.substr(pos, line.find("\"", pos) - pos));
                            polygon.points.push_back(point);
                        }
                    }
                    polygons.push_back(polygon);
                }
            }
            return polygons;
        }
};