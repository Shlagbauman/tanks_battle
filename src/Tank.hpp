#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
class Bullet;

class Tank : public sf::Drawable {
public:
    Tank(sf::Vector2f                 pos,
         sf::Keyboard::Key            up,  sf::Keyboard::Key dn,
         sf::Keyboard::Key            lf,  sf::Keyboard::Key rt,
         std::initializer_list<sf::Keyboard::Key> fire,
         const std::string&           png,
         int                          id);

    void update(float dt, std::vector<Bullet>& bullets);

    void respawn    (sf::Vector2f p);
    void setPosition(sf::Vector2f p);
    sf::Vector2f  position() const noexcept { return body_.getPosition(); }
    sf::FloatRect bounds()   const noexcept { return body_.getGlobalBounds(); }

    void enableShield(float s)         { shield_ = s; }
    bool shielded()   const noexcept   { return shield_ > 0.f; }
    void applyBonus(float k,float d)   { speed_ = std::min(speed_ * k, 240.f); bonus_ = d; }

    int id() const noexcept { return id_; }

private:
    sf::RectangleShape body_;
    sf::Sprite         sprite_;
    sf::Vector2f dir_{0,-1}, vel_{};

    sf::Keyboard::Key kU_, kD_, kL_, kR_;
    std::vector<sf::Keyboard::Key> fire_;
    int   id_;
    float speed_{120.f}, bonus_{0.f}, shield_{0.f};
    sf::Clock fireClock_;

    void draw(sf::RenderTarget&, sf::RenderStates) const override;
};