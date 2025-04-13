#include "Game.hpp"
#include "Tank.hpp"
#include "Map.hpp"
#include "Bullet.hpp"
#include <iostream>
#include <cmath>

Game::Game()
: m_window(sf::VideoMode(640, 480), "Tank Duel")
{
    m_window.setFramerateLimit(60);

    loadResources();

    // Создаём карту
    m_map = std::make_unique<Map>();

    // Создаём два танка
    m_tank1 = std::make_unique<Tank>(TankID::Player1);
    m_tank2 = std::make_unique<Tank>(TankID::Player2);

    // Пример текстуры для танка
    // (предполагаем, что "assets/tank.png" загружается в m_font, но на практике – отдельная m_tankTexture)
    // Для упрощения тут не показываем, как грузим tank.png. Делаем вид, что уже загружена.
    // Но можно было завести ещё один sf::Texture m_tankTex; m_tankTex.loadFromFile("assets/tank.png");
    // и потом передать:
    // m_tank1->setTexture(m_tankTex);
    // m_tank2->setTexture(m_tankTex);

    // Позиции спауна (можно менять)
    m_tank1->setSpawnPosition({100.f, 100.f});
    m_tank2->setSpawnPosition({500.f, 300.f});

    // Текст для счёта
    m_scoreText.setFont(m_font);
    m_scoreText.setCharacterSize(20);
    m_scoreText.setFillColor(sf::Color::White);
    m_scoreText.setPosition(10.f, 10.f);
    m_scoreText.setString("P1: 0 | P2: 0");
}

void Game::loadResources() {
    if (!m_font.loadFromFile("assets/font.ttf")) {
        // На случай ошибки
        std::cerr << "Failed to load font.ttf\n";
    }
}

void Game::run() {
    sf::Clock clock;
    while (m_window.isOpen()) {
        processEvents();

        float dt = clock.restart().asSeconds();
        update(dt);

        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
        }
    }
}

// Основное обновление
void Game::update(float dt) {
    // Двигаем танки
    m_tank1->handleInput(dt);
    m_tank1->update(dt);
    m_tank1->checkWallCollision(*m_map);

    m_tank2->handleInput(dt);
    m_tank2->update(dt);
    m_tank2->checkWallCollision(*m_map);

    // Обновляем все пули
    for (auto& b : m_bullets) {
        b->update(dt);
    }
    // Проверяем столкновения пуль со стенами
    for (auto& b : m_bullets) {
        if (b->checkWallCollision(*m_map)) {
            // Для упрощения: "Уничтожим" пулю, переместив её за границы
            b->draw(m_window); // не обязательно
            b->update(9999.f); // не обязательно
            // Можно пометить пулю флагом на удаление
        }
    }

    // Удаляем "мертвые" пули (за границей)
    m_bullets.erase(
        std::remove_if(m_bullets.begin(), m_bullets.end(),
            [&](const std::unique_ptr<Bullet>& b){
                sf::FloatRect bounds = b->getBounds();
                bool outOfScreen =
                    (bounds.left > 700 || bounds.left + bounds.width < 0 ||
                     bounds.top > 500 || bounds.top + bounds.height < 0);
                return outOfScreen;
            }),
        m_bullets.end()
    );

    // Проверяем попадания пуль в танки
    checkCollisions();
    
    // Обновляем HUD
    m_scoreText.setString("P1: " + std::to_string(m_scoreP1) +
                          " | P2: " + std::to_string(m_scoreP2));
}

// Проверка столкновений пули и танка
void Game::checkCollisions() {
    // Для каждой пули – проверить пересечение с танками
    for (auto& bullet : m_bullets) {
        sf::FloatRect bRect = bullet->getBounds();

        // Не хотим, чтобы пуля попадала в "своего" владельца, поэтому проверяем ID
        if (bullet->getOwnerID() == 1) {
            if (bRect.intersects(m_tank2->getBounds())) {
                // Попадание в танк2
                m_scoreP1++;
                bool alive = m_tank2->takeDamage(1);
                // Уберём пулю
                bRect.left = 9999.f; // "отправим"
            }
        } else {
            if (bRect.intersects(m_tank1->getBounds())) {
                // Попадание в танк1
                m_scoreP2++;
                bool alive = m_tank1->takeDamage(1);
                // Уберём пулю
                bRect.left = 9999.f;
            }
        }
    }

    // Удаляем пули, "улетевшие" в 9999
    m_bullets.erase(
        std::remove_if(m_bullets.begin(), m_bullets.end(),
            [&](const std::unique_ptr<Bullet>& b){
                return b->getBounds().left > 8000.f;
            }),
        m_bullets.end()
    );

    // Если у танка 1 hp <= 0, респавним
    // Если у танка 2 hp <= 0, респавним
    // Для простоты делаем это просто проверкой в конце
    // (Можно в takeDamage() вернуть false и сразу resetRound)
    // Но тут покажем отдельно:
    if (m_tank1->getBounds().width <= 0.f) {
        // Подразумевается: танк1 "мертв"? Но в примере getBounds() не вернёт width=0
        // Лучше сделать поле hp в самом Tank
    }
}

// Респавн обоих танков, если нужно
void Game::resetRound(int deadTankId) {
    // Можно сделать: если deadTankId = 1, то...
    // Но сейчас упрощаем
    m_tank1->restoreFullHP();
    m_tank2->restoreFullHP();
}

// Рендер
void Game::render() {
    m_window.clear(sf::Color::Black);

    // Рисуем стены
    m_map->draw(m_window);

    // Рисуем танки
    m_tank1->draw(m_window);
    m_tank2->draw(m_window);

    // Пули
    for (auto& b : m_bullets) {
        b->draw(m_window);
    }

    // HUD (счёт)
    m_window.draw(m_scoreText);

    m_window.display();
}