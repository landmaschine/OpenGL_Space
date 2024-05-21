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
    void extractConPolygonsFromTextFile(const std::string filename, PolyData* polyData) {
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
                    x /= 64.f;
                    y /= 64.f;
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

    std::vector<float> createVertecis(const PolyData& polydata) {
        std::vector<float> vertices;
        for (const auto& polygon : polydata.Polygons) {
            for (const auto& point : polygon) {
                vertices.push_back(point.x);
                vertices.push_back(point.y);
                vertices.push_back(0.0f);
            }
        }
        return vertices;
    }

    std::vector<unsigned int> createIndices(const PolyData& polyData) {
        std::vector<unsigned int> indices;
        unsigned int offset = 0;
        for (const auto& polygon : polyData.Polygons) {
            unsigned int vertexCount = polygon.size();
            for (unsigned int i = 1; i < vertexCount - 1; ++i) {
                indices.push_back(offset);
                indices.push_back(offset + i);
                indices.push_back(offset + i + 1);
            }
            offset += vertexCount;
        }
        return indices;
    }
};
