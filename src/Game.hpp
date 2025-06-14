#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <random>

#include "Tilemap.hpp"
#include "Tank.hpp"
#include "Bullet.hpp"
#include "Bonus.hpp"

class Game {
public:
    explicit Game(const std::string& assetsDir);
    int  run();
    void nextMap();

private:
    sf::RenderWindow window_;
    sf::Font   font_;
    sf::Text   scoreText_;

    sf::SoundBuffer boomBuf_;
    sf::Sound       boom_;

    std::string mapFile1_ = "maps/level1.txt";
    std::string mapFile2_ = "maps/arena2.txt";
    bool        usingFirst_ = true;
    Tilemap     map_;

    Tank                    t1_;
    Tank                    t2_;
    std::vector<Bullet>     bullets_;
    std::vector<Bonus>      bonuses_;

    unsigned score1_{0}, score2_{0};

    sf::Clock              bonusClk_;
    const float            bonusCD_{10.f};
    std::vector<sf::Vector2f> bonusSpots_;

    void handle();
    void spawnBonus();
    void resetRound();
};