#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

// Простая карта с фиксированными стенами
class Map {
public:
    Map();

    // Нарисовать стены
    void draw(sf::RenderWindow& window);

    // Проверка стены по координатам
    bool isWall(int x, int y) const;

    // Размер карты в тайлах
    int getWidth() const  { return m_width; }
    int getHeight() const { return m_height; }

    // Размер одного тайла в пикселях
    static constexpr int TILE_SIZE = 32;

private:
    int m_width = 20;   // число тайлов по X
    int m_height = 15;  // число тайлов по Y

    std::vector<std::vector<bool>> m_walls; // true = стена
    
    sf::Texture m_wallTexture;
    sf::Sprite  m_wallSprite;
};  