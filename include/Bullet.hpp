#pragma once
#include "Entity.hpp"
#include <SFML/Graphics.hpp>

class Map;

class Bullet : public Entity {
public:
    Bullet(int ownerID, const sf::Texture& tex, sf::Vector2f pos, float angle);

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    
    sf::FloatRect getBounds() const override;

    // Проверка столкновения со стенами
    bool checkWallCollision(const Map& map);

    // Кто выпустил пулю (чтобы начислять очки)
    int getOwnerID() const { return m_ownerID; }

private:
    int m_ownerID;
    sf::Sprite m_sprite;
    float m_speed = 250.f;
};