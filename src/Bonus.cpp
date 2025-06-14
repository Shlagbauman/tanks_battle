#include "Bonus.hpp"
#include <unordered_map>

static std::unordered_map<BonusType,sf::Texture> TEX;

Bonus::Bonus(sf::Vector2f p, BonusType t) : type_(t)
{
    if(TEX.empty()){                               // лениво загружаем один раз
        TEX[BonusType::Speed ].loadFromFile("assets/bonus_speed.png");
        TEX[BonusType::Shield].loadFromFile("assets/bonus_shield.png");
    }
    spr_.setTexture(TEX[t]);
    spr_.setScale(0.3f,0.3f);
    spr_.setPosition(p);
}