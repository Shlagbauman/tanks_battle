#include "Tank.hpp"
#include "Bullet.hpp"

#include <unordered_map>
#include <cmath>
#include <algorithm>

static std::unordered_map<std::string, sf::Texture> TEX;

/* ─── основной ctor ─── */
Tank::Tank(sf::Vector2f p,
           sf::Keyboard::Key u, sf::Keyboard::Key d,
           sf::Keyboard::Key l, sf::Keyboard::Key r,
           std::initializer_list<sf::Keyboard::Key> fire,
           const std::string& png)
    : kU_(u), kD_(d), kL_(l), kR_(r), fire_(fire)
{
    body_.setOrigin(16,16);
    body_.setPosition(p);

    sf::Texture& tx = TEX[png];
    if(tx.getSize().x == 0) tx.loadFromFile(png);

    spr_.setTexture(tx);
    spr_.setOrigin(16,16);
    spr_.setScale(0.75f,0.75f);
    spr_.setPosition(p);
}

/* ─── короткий ctor-обёртка ─── */
Tank::Tank(sf::Vector2f p,
           sf::Keyboard::Key u, sf::Keyboard::Key d,
           sf::Keyboard::Key l, sf::Keyboard::Key r,
           sf::Keyboard::Key fire, sf::Color)
    : Tank(p,u,d,l,r,{fire},
           (fire==sf::Keyboard::Space)?"assets/tank_green.png"
                                     :"assets/tank_red.png")
{}

/* ─── служебные ─── */
void Tank::setPosition(sf::Vector2f p){ body_.setPosition(p); spr_.setPosition(p); }

void Tank::respawn(sf::Vector2f p){
    setPosition(p);
    speed_   = 120.f;
    bonusT_  = 0.f;
    shieldT_ = 0.f;
    shotClock_.restart();
}

void Tank::enableShield(float s){ shieldT_ = s; }
void Tank::applyBonus(float f,float d){ speed_=std::min(speed_*f,MAX_SPEED); bonusT_=d; }

/* ─── draw (щит r&asymp;120) ─── */
void Tank::draw(sf::RenderTarget& t,sf::RenderStates s) const
{
    t.draw(spr_,s);
    if(shieldT_>0.f){
        constexpr float R=120.f;
        sf::CircleShape ring(R);
        ring.setOrigin(R,R);
        ring.setPosition(spr_.getPosition());
        ring.setFillColor(sf::Color::Transparent);
        ring.setOutlineColor({120,180,255});
        ring.setOutlineThickness(6.f);
        t.draw(ring,s);
    }
}

/* ─── update ─── */
void Tank::update(float dt,std::vector<Bullet>& bullets)
{
    vel_={};
    if(sf::Keyboard::isKeyPressed(kU_)) vel_.y=-1;
    if(sf::Keyboard::isKeyPressed(kD_)) vel_.y= 1;
    if(sf::Keyboard::isKeyPressed(kL_)) vel_.x=-1;
    if(sf::Keyboard::isKeyPressed(kR_)) vel_.x= 1;

    if(vel_!=sf::Vector2f{}){
        vel_/=std::hypot(vel_.x,vel_.y);
        dir_=vel_;
        /* png &laquo;смотрит&raquo; вверх, но раньше был разворот на 180°. добавляем +180° */
        float ang = std::atan2(dir_.y, dir_.x)*180.f/3.1415926f + 270.f; // +180 к прежним +90
        spr_.setRotation(std::fmod(ang+360.f,360.f));
    }
    body_.move(vel_*speed_*dt);
    spr_.setPosition(body_.getPosition());

    /* стрельба (личный таймер) */
    bool fire=std::any_of(fire_.begin(),fire_.end(),
                 [](auto k){return sf::Keyboard::isKeyPressed(k);});
    if(fire && shotClock_.getElapsedTime().asMilliseconds()>300){
        bullets.emplace_back(body_.getPosition()+dir_*50.f, dir_);
        shotClock_.restart();
    }

    /* таймеры бонусов */
    if(bonusT_>0.f){ bonusT_-=dt; if(bonusT_<=0) speed_=120.f; }
    if(shieldT_>0.f) shieldT_=std::max(shieldT_-dt,0.f);
}