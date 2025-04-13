#include "Tank.hpp"
#include "Bullet.hpp"
#include "Map.hpp"
#include "Input.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <cmath>

Tank::Tank(TankID id)
: m_id(id)
{
    // Выставим какие-то базовые параметры спрайта
    m_sprite.setOrigin(16.f, 16.f); // чтобы центр вращения был по центру
}

void Tank::setTexture(const sf::Texture &texture) {
    m_sprite.setTexture(texture);
}

void Tank::setSpawnPosition(const sf::Vector2f& pos) {
    m_spawnPos = pos;
    m_sprite.setPosition(pos);
}

void Tank::handleInput(float dt) {
    // Выбираем раскладку
    const InputConfig& cfg = (m_id == TankID::Player1) ? player1Config : player2Config;

    // Движение вперёд/назад
    if (sf::Keyboard::isKeyPressed(cfg.up)) {
        float angleRad = m_sprite.getRotation() * 3.14159f / 180.f;
        sf::Vector2f dir(std::cos(angleRad), std::sin(angleRad));
        m_sprite.move(dir * m_speed * dt);
    }
    if (sf::Keyboard::isKeyPressed(cfg.down)) {
        float angleRad = m_sprite.getRotation() * 3.14159f / 180.f;
        sf::Vector2f dir(std::cos(angleRad), std::sin(angleRad));
        m_sprite.move(-dir * m_speed * dt);
    }
    // Поворот
    if (sf::Keyboard::isKeyPressed(cfg.left)) {
        m_sprite.rotate(-m_rotationSpeed * dt);
    }
    if (sf::Keyboard::isKeyPressed(cfg.right)) {
        m_sprite.rotate(m_rotationSpeed * dt);
    }
    // Стрельба
    m_fireTimer += dt;
    if (sf::Keyboard::isKeyPressed(cfg.fire)) {
        if (m_fireTimer >= m_fireCooldown) {
            // создаём пулю
            m_fireTimer = 0.f; 
        }
    }
}

void Tank::update(float dt) {
    // Просто никаких действий, кроме handleInput
}

// Проверка столкновений со стенами
void Tank::checkWallCollision(const Map& map) {
    sf::FloatRect bounds = getBounds();

    // Вычислим текущую "ячейку" карты
    int tileX_left   = int(bounds.left)            / Map::TILE_SIZE;
    int tileX_right  = int(bounds.left+bounds.width) / Map::TILE_SIZE;
    int tileY_top    = int(bounds.top)             / Map::TILE_SIZE;
    int tileY_bottom = int(bounds.top+bounds.height) / Map::TILE_SIZE;

    // Если в любой из 4 углов — стена, отбрасываем назад
    if (map.isWall(tileX_left, tileY_top)    ||
        map.isWall(tileX_right, tileY_top)   ||
        map.isWall(tileX_left, tileY_bottom) ||
        map.isWall(tileX_right, tileY_bottom))
    {
        // Откатим позицию
        m_sprite.setPosition(m_sprite.getPosition() - sf::Vector2f(0.5f, 0.5f));
    }
}

std::unique_ptr<Bullet> Tank::shoot() {
    // Создадим пулю, учитывая угол
    float angleRad = m_sprite.getRotation() * 3.14159f / 180.f;
    sf::Vector2f dir(std::cos(angleRad), std::sin(angleRad));

    // Стартовая позиция пули - чуть впереди танка
    sf::Vector2f startPos = m_sprite.getPosition() + dir * 20.f;

    // ownerID: 1 для Player1, 2 для Player2
    int owner = (m_id == TankID::Player1) ? 1 : 2;

    // Тут предполагается, что где-то лежит текстура для пули
    static sf::Texture bulletTex;
    static bool loaded = false;
    if (!loaded) {
        bulletTex.loadFromFile("assets/tank.png"); // условно
        loaded = true;
    }

    auto bullet = std::make_unique<Bullet>(owner, bulletTex, startPos, m_sprite.getRotation());
    return bullet;
}

void Tank::draw(sf::RenderWindow &window) {
    window.draw(m_sprite);
}

sf::FloatRect Tank::getBounds() const {
    // Возвращаем глобальные границы
    return m_sprite.getGlobalBounds();
}

bool Tank::takeDamage(int dmg) {
    m_hp -= dmg;
    if (m_hp <= 0) {
        // Респавним
        m_sprite.setPosition(m_spawnPos);
        m_hp = 3;
        return false; // "умер"
    }
    return true; // ещё жив
}

void Tank::restoreFullHP() {
    m_hp = 3;
    m_sprite.setPosition(m_spawnPos);
    // Можно сбросить угол и т.д.
    m_sprite.setRotation(0.f);
}