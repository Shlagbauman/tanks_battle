#include "Bullet.hpp"

Bullet::Bullet(sf::Vector2f pos, sf::Vector2f dir) : dir_(dir)
{
    if(tex_.getSize().x == 0)
        tex_.loadFromFile("assets/bullet.png");          // 1&times;1 px или любой

    spr_.setTexture(tex_);
    spr_.setOrigin(tex_.getSize().x / 2.f, tex_.getSize().y / 2.f);
    spr_.setPosition(pos);
}

void Bullet::update(float dt)
{
    spr_.move(dir_ * 500.f * dt);
}

sf::Vector2f Bullet::getPosition() const noexcept
{
    return spr_.getPosition();
}