#pragma once
#include <iostream>
#include <chrono>

#include <fmt/core.h>
#include "guiDebugInfo.h"

template<typename... Fs>
double measureFunctionTime(Fs&&... func) {
    auto start = std::chrono::high_resolution_clock::now();
    (func(), ...);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    return elapsed.count();
}

template<typename... Fs>
double measureFPS(Fs&&... func) {
    auto start = std::chrono::high_resolution_clock::now();
    (func(), ...);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    return 1 / elapsed.count();
}