#pragma once
#include <iostream>
#include <chrono>

#include <fmt/core.h>

void printFPS(double dt) {
    fmt::println("FPS: {:f}", 1/dt);
}

template<typename... Fs>
void measureFunctionTime(Fs&&... func) {
    auto start = std::chrono::high_resolution_clock::now();
    (func(), ...);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    fmt::println("{:}", elapsed.count());
}

template<typename... Fs>
void measureFPS(Fs&&... func) {
    auto start = std::chrono::high_resolution_clock::now();
    (func(), ...);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    fmt::println("{:f}", 1/elapsed.count());
}