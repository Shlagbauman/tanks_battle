#include "Bullet.hpp"
#include <cmath>

Bullet::Bullet(sf::Vector2f pos, sf::Vector2f dir, int ownerId)
    : dir_(dir), owner_(ownerId)
{
    shape_.setSize({SIZE, SIZE});
    shape_.setOrigin(SIZE / 2.f, SIZE / 2.f);
    shape_.setFillColor({255, 220, 20});
    shape_.setPosition(pos);

    float ang = std::atan2(dir_.y, dir_.x) * 180.f / 3.1415926f + 90.f;
    shape_.setRotation(ang);
}

void Bullet::update(float dt)
{
    shape_.move(dir_ * SPEED * dt);
    life_ += dt;
}