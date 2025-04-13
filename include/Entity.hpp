#pragma once
#include <SFML/Graphics.hpp>

class Entity {
public:
    Entity();
    virtual ~Entity() = default;

    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

    // Прямоугольник для столкновений
    virtual sf::FloatRect getBounds() const = 0;
};