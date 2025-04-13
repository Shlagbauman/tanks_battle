#pragma once
#include <SFML/Window/Keyboard.hpp>

// Удобная структура для хранения схемы клавиш
struct InputConfig {
    sf::Keyboard::Key up;
    sf::Keyboard::Key down;
    sf::Keyboard::Key left;
    sf::Keyboard::Key right;
    sf::Keyboard::Key fire;
};

// Глобально объявим 2 схемы управления
extern InputConfig player1Config;
extern InputConfig player2Config;