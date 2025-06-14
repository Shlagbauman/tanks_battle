#include "Tank.hpp"
#include "Bullet.hpp"
#include <unordered_map>
#include <cmath>

namespace { std::unordered_map<std::string, sf::Texture> cache; }

Tank::Tank(sf::Vector2f p,
           sf::Keyboard::Key up,  sf::Keyboard::Key dn,
           sf::Keyboard::Key lf,  sf::Keyboard::Key rt,
           std::initializer_list<sf::Keyboard::Key> fireKeys,
           const std::string& png,
           int id)
    : kU_(up), kD_(dn), kL_(lf), kR_(rt), fire_(fireKeys), id_(id)
{
    body_.setSize({32,32});
    body_.setOrigin(16,16);
    body_.setPosition(p);

    sf::Texture& tx = cache[png];
    if(tx.getSize().x == 0) tx.loadFromFile(png);

    sprite_.setTexture(tx);
    sprite_.setOrigin(16,16);
    sprite_.setScale(0.75f, 0.75f);
    sprite_.setPosition(p);
}

void Tank::setPosition(sf::Vector2f p){ body_.setPosition(p); sprite_.setPosition(p); }

void Tank::respawn(sf::Vector2f p){
    setPosition(p);
    speed_ = 120.f; bonus_ = shield_ = 0.f;
    fireClock_.restart();
}

void Tank::update(float dt, std::vector<Bullet>& pool)
{
    vel_ = {};
    if(sf::Keyboard::isKeyPressed(kU_)) vel_.y = -1;
    if(sf::Keyboard::isKeyPressed(kD_)) vel_.y =  1;
    if(sf::Keyboard::isKeyPressed(kL_)) vel_.x = -1;
    if(sf::Keyboard::isKeyPressed(kR_)) vel_.x =  1;

    if(vel_ != sf::Vector2f{}){
        vel_ /= std::hypot(vel_.x, vel_.y);
        dir_  = vel_;
        float ang = std::atan2(dir_.y, dir_.x)*180.f/3.1415926f + 90.f + 180.f;
        sprite_.setRotation(ang);
    }

    body_.move(vel_ * speed_ * dt);
    sprite_.setPosition(body_.getPosition());

    bool fire=false; for(auto k:fire_) fire |= sf::Keyboard::isKeyPressed(k);
    if(fire && fireClock_.getElapsedTime().asMilliseconds()>300){
        pool.emplace_back(body_.getPosition()+dir_*70.f, dir_, id_);
        fireClock_.restart();
    }

    if(bonus_  > 0.f){ bonus_  -= dt; if(bonus_  <= 0.f) speed_ = 120.f; }
    if(shield_ > 0.f)  shield_ -= dt;
}

void Tank::draw(sf::RenderTarget& t, sf::RenderStates s) const
{
    t.draw(sprite_, s);
    if(shield_ > 0.f){
        sf::CircleShape ring(26); ring.setOrigin(26,26);
        ring.setPosition(sprite_.getPosition());
        ring.setFillColor(sf::Color::Transparent);
        ring.setOutlineThickness(4);
        ring.setOutlineColor({120,180,255});
        t.draw(ring, s);
    }
}