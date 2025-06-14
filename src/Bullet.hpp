#pragma once
#include <SFML/Graphics.hpp>

/**
 * @class Bullet
 * @brief Простая пуля: летит по dir со скоростью 500 px/s.
 */
class Bullet : public sf::Drawable {
public:
    Bullet(sf::Vector2f pos, sf::Vector2f dir);

    void              update(float dt);
    sf::FloatRect     bounds()     const noexcept { return spr_.getGlobalBounds(); }
    sf::Vector2f      getPosition() const noexcept;          ///< центр спрайта

private:
    sf::Sprite spr_;
    sf::Vector2f dir_;
    static inline sf::Texture tex_;

    void draw(sf::RenderTarget& t, sf::RenderStates s) const override
    { t.draw(spr_, s); }
};