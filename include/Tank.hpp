#pragma once
#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class Bullet;
class Map;

enum class TankID {
    Player1,
    Player2
};

class Tank : public Entity {
public:
    Tank(TankID id);

    void setTexture(const sf::Texture& texture);

    // Обработка ввода/движения
    void handleInput(float dt);
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

    // Позиция респавна
    void setSpawnPosition(const sf::Vector2f& pos);

    // Проверка столкновений со стенами
    void checkWallCollision(const Map& map);

    // Стрельба
    std::unique_ptr<Bullet> shoot();

    // Геттеры
    sf::FloatRect getBounds() const override;
    TankID getID() const { return m_id; }

    // Уменьшаем HP, возвращаем осталось ли здоровье
    bool takeDamage(int dmg);

    // Сброс hp в максимум
    void restoreFullHP();

private:
    TankID m_id;
    sf::Sprite m_sprite;
    float m_speed = 100.f;
    float m_rotationSpeed = 120.f; // град/сек
    int   m_hp = 3;

    sf::Vector2f m_spawnPos; // для респавна

    // Контроль перезарядки
    float m_fireCooldown = 0.3f;
    float m_fireTimer    = 0.f;
};