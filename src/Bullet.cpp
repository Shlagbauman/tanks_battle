#include "Bullet.hpp"
#include "Map.hpp"
#include <cmath>

Bullet::Bullet(int ownerID, const sf::Texture& tex, sf::Vector2f pos, float angle)
: m_ownerID(ownerID)
{
    m_sprite.setTexture(tex);
    m_sprite.setOrigin(16.f, 16.f); // пусть текстура 32x32
    m_sprite.setPosition(pos);
    m_sprite.setRotation(angle);
}

void Bullet::update(float dt) {
    float angleRad = m_sprite.getRotation() * 3.14159f / 180.f;
    sf::Vector2f dir(std::cos(angleRad), std::sin(angleRad));
    m_sprite.move(dir * m_speed * dt);
}

void Bullet::draw(sf::RenderWindow &window) {
    window.draw(m_sprite);
}

sf::FloatRect Bullet::getBounds() const {
    return m_sprite.getGlobalBounds();
}

bool Bullet::checkWallCollision(const Map &map) {
    sf::FloatRect bounds = getBounds();
    // Проверяем тайловые координаты
    int tx_left   = int(bounds.left) / Map::TILE_SIZE;
    int tx_right  = int(bounds.left + bounds.width)  / Map::TILE_SIZE;
    int ty_top    = int(bounds.top)  / Map::TILE_SIZE;
    int ty_bottom = int(bounds.top + bounds.height) / Map::TILE_SIZE;

    // Если хоть в одном — стена
    if (map.isWall(tx_left, ty_top)   || map.isWall(tx_right, ty_top) ||
        map.isWall(tx_left, ty_bottom)|| map.isWall(tx_right, ty_bottom))
    {
        // Пуля столкнулась
        return true;
    }
    return false;
}