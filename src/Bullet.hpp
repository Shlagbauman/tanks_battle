#pragma once
#include <SFML/Graphics.hpp>

class Bullet : public sf::Drawable {
public:
    Bullet(sf::Vector2f pos, sf::Vector2f dir, int ownerId);
    void update(float dt);

    bool          canHit(int tankId) const noexcept { return life_ > GRACE && owner_ != tankId; }
    sf::FloatRect bounds()   const noexcept         { return shape_.getGlobalBounds(); }
    sf::Vector2f  position() const noexcept         { return shape_.getPosition();   }

private:
    sf::RectangleShape shape_;
    sf::Vector2f dir_;
    int   owner_;
    float life_{0.f};

    static constexpr float SPEED = 500.f;
    static constexpr float GRACE = 0.12f;
    static constexpr float SIZE  = 8.f;

    void draw(sf::RenderTarget& t, sf::RenderStates s) const override
    { t.draw(shape_, s); }
};