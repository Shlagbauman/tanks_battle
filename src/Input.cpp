#include "Input.hpp"

// Игрок 1: WASD + Space
InputConfig player1Config {
    sf::Keyboard::W,
    sf::Keyboard::S,
    sf::Keyboard::A,
    sf::Keyboard::D,
    sf::Keyboard::Space
};

// Игрок 2: стрелки + RCtrl
InputConfig player2Config {
    sf::Keyboard::Up,
    sf::Keyboard::Down,
    sf::Keyboard::Left,
    sf::Keyboard::Right,
    sf::Keyboard::RControl
};