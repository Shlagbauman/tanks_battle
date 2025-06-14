#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <random>

#include "Tilemap.hpp"
#include "Tank.hpp"
#include "Bullet.hpp"
#include "Bonus.hpp"

/* -------------------------------------------------------
 *  Game &mdash; главный движок цикла и логики
 * -----------------------------------------------------*/
class Game {
public:
    explicit Game(const std::string& assetsDir);   // загрузка ресурсов
    int  run();                                    // игровой цикл
    void nextMap();                                // F1 — переключить карту

private:
    /* окно и HUD */
    sf::RenderWindow window_;
    sf::Font   font_;
    sf::Text   scoreText_;

    /* звук взрыва */
    sf::SoundBuffer boomBuf_;
    sf::Sound       boom_;

    /* карты */
    std::string mapFile1_ = "maps/level1.txt";
    std::string mapFile2_ = "maps/arena2.txt";
    bool        usingFirst_ = true;
    Tilemap     map_;

    /* сущности */
    Tank                    t1_;
    Tank                    t2_;
    std::vector<Bullet>     bullets_;
    std::vector<Bonus>      bonuses_;

    /* счёт */
    unsigned score1_{0}, score2_{0};

    /* спавн бонусов */
    sf::Clock              bonusClk_;
    const float            bonusCD_{10.f};
    std::vector<sf::Vector2f> bonusSpots_;        // задано в ctor

    /* внутренние функции */
    void handle();            // столкновения + бонусы
    void spawnBonus();        // появляется звезда / щит
    void resetRound();        // респавн танков, очистка пуль
};