#pragma once
#include <SFML/Graphics.hpp>

enum class BonusType { Speed, Shield };

class Bonus : public sf::Drawable {
public:
    Bonus(sf::Vector2f pos, BonusType t);

    BonusType     type()   const noexcept { return type_; }
    sf::FloatRect bounds() const noexcept { return spr_.getGlobalBounds(); }

private:
    sf::Sprite spr_;
    BonusType  type_;
    void draw(sf::RenderTarget& t, sf::RenderStates s) const override
    { t.draw(spr_,s); }
};