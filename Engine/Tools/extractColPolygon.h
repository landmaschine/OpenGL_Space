#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <glm/glm.hpp>

struct PolyData {
    std::vector<std::vector<glm::vec2>> Polygons;
};

class PolyFromTxt {
public:
    void extractHullPolygonsFromTextFile(const std::string filename, PolyData* polyData) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        std::string line;
        bool found = false;

        while (std::getline(file, line)) {
            if (line.find("Convex sub polygons:") != std::string::npos) {
                found = true;
                break;
            }
        }

        if (!found) {
            std::cerr << "Convex sub polygons not found in file: " << filename << std::endl;
            return;
        }

        while (std::getline(file, line)) {
            if (line.empty())
                continue;

            std::istringstream iss(line);
            char discard;
            std::vector<glm::vec2> polygonPoints;
            while (iss >> discard) {
                if (discard == '(') {
                    float x, y;
                    iss >> x >> discard >> y >> discard;
                    polygonPoints.emplace_back(x, y);
                }
            }
            polyData->Polygons.push_back(polygonPoints);
        }

        file.close();
    }

    void print(PolyData poly) {
        for (size_t i = 0; i < poly.Polygons.size(); ++i) {
            std::cout << "Polygon " << i + 1 << ":" << std::endl;
            for (const auto& point : poly.Polygons[i]) {
                std::cout << "(" << point.x << ", " << point.y << ")" << std::endl;
            }
            std::cout << std::endl;
        }
    }
};
