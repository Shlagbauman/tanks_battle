#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Bullet;

/* ─────────── Tank ─────────── */
class Tank : public sf::Drawable {
public:
    Tank(sf::Vector2f pos,
         sf::Keyboard::Key up,   sf::Keyboard::Key down,
         sf::Keyboard::Key left, sf::Keyboard::Key right,
         std::initializer_list<sf::Keyboard::Key> fireKeys,
         const std::string& pngPath);

    /* упрощённый ctor — одна кнопка &laquo;огонь&raquo; */
    Tank(sf::Vector2f pos,
         sf::Keyboard::Key up,   sf::Keyboard::Key down,
         sf::Keyboard::Key left, sf::Keyboard::Key right,
         sf::Keyboard::Key fireKey,
         sf::Color dummy = {});

    /* состояние / сервис */
    sf::FloatRect bounds()   const noexcept { return body_.getGlobalBounds(); }
    sf::Vector2f  position() const noexcept { return body_.getPosition();    }
    bool          shielded() const noexcept { return shieldT_ > 0.f; }

    void setPosition (sf::Vector2f p);
    void respawn     (sf::Vector2f p);
    void enableShield(float seconds);               // +щит
    void applyBonus  (float factor,float duration); // +скорость
    void update(float dt, std::vector<Bullet>& bullets);

private:
    /* константы */
    static constexpr float MAX_SPEED = 240.f;

    /* графика / физика */
    sf::RectangleShape body_{{32.f,32.f}};
    sf::Sprite         spr_;
    sf::Vector2f       vel_, dir_{0.f,-1.f};
    float              speed_{120.f}, bonusT_{0.f}, shieldT_{0.f};

    /* управление */
    sf::Keyboard::Key             kU_,kD_,kL_,kR_;
    std::vector<sf::Keyboard::Key> fire_;
    sf::Clock                     shotClock_;      // независимый таймер выстрела

    /* отрисовка */
    void draw(sf::RenderTarget& t, sf::RenderStates s) const override;
};