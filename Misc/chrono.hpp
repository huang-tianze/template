#include <chrono>
#include <iostream>
int main() {
    auto start = std::chrono::high_resolution_clock::now();
    // bruh
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << elapsed.count() << std::endl;
}