#include "Game.hpp"
#include <iostream>

int main(int argc, char** argv) try {
    std::string assets = (argc > 1) ? argv[1] : "assets";
    Game g(assets);
    return g.run();
} catch (const std::exception& e) {
    std::cerr << "Fatal: " << e.what() << '\n';
    return 1;
}