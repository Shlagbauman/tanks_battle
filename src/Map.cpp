#include "Map.hpp"
#include <iostream>

Map::Map() {
    // Загрузим текстуру стены (опционально). Можно заменить цветным прямоугольником.
    if (!m_wallTexture.loadFromFile("assets/tank.png")) {
        // Допустим, нет текстуры — не страшно
        std::cerr << "Failed to load wall texture. Using fallback.\n";
    }
    m_wallSprite.setTexture(m_wallTexture);
    m_wallSprite.setColor(sf::Color::Red);

    // Инициируем сетку стен (простейший статический шаблон)
    m_walls.resize(m_height, std::vector<bool>(m_width, false));

    // Пример: обрамление стенами
    for (int x = 0; x < m_width; x++) {
        m_walls[0][x] = true;
        m_walls[m_height-1][x] = true;
    }
    for (int y = 0; y < m_height; y++) {
        m_walls[y][0] = true;
        m_walls[y][m_width-1] = true;
    }

    // Пример нескольких внутренних стен
    // (В реальном проекте сгенерировать лабиринт)
    m_walls[5][5] = true;
    m_walls[6][5] = true;
}

void Map::draw(sf::RenderWindow& window) {
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            if (m_walls[y][x]) {
                m_wallSprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                window.draw(m_wallSprite);
            }
        }
    }
}

bool Map::isWall(int tx, int ty) const {
    if (ty < 0 || ty >= m_height || tx < 0 || tx >= m_width) {
        // За границами массива считаем стеной
        return true;
    }
    return m_walls[ty][tx];
}