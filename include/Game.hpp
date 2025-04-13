#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class Tank;
class Bullet;
class Map;

// Класс Game — управляет основным циклом и хранит общий State
class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(float dt);
    void render();

private:
    sf::RenderWindow m_window;
    
    // Для HUD
    sf::Font m_font;
    sf::Text m_scoreText;

    // Два танка
    std::unique_ptr<Tank> m_tank1;
    std::unique_ptr<Tank> m_tank2;

    // Все активные пули
    std::vector<std::unique_ptr<Bullet>> m_bullets;

    // Карта (стены)
    std::unique_ptr<Map> m_map;

    // Счёт
    int m_scoreP1 = 0;
    int m_scoreP2 = 0;

    // Служебные методы
    void loadResources();
    void checkCollisions();
    void resetRound(int deadTankId); // респавн танков
};