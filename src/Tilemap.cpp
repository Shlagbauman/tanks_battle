#include "Tilemap.hpp"
#include <fstream>
#include <stdexcept>

/* стенка-&laquo;кирпич&raquo; теперь 16 &times; 32 px  */
Tilemap::Tilemap(const std::string& file, sf::Vector2f tile)
{
    std::ifstream f(file);
    if(!f) throw std::runtime_error("cannot open map " + file);

    /* половина толщины по X */
    const sf::Vector2f wallSize{ tile.x * 0.5f, tile.y };

    std::string line; std::size_t y = 0;
    while(std::getline(f, line))
    {
        for(std::size_t x = 0; x < line.size(); ++x)
        {
            if(line[x] == '#')
            {
                sf::RectangleShape w(wallSize);
                w.setFillColor({80, 80, 80});
                w.setPosition(x * tile.x, y * tile.y);
                walls_.push_back(w);
            }
        }
        ++y;
    }
}

bool Tilemap::collides(const sf::FloatRect& r) const noexcept
{
    for(const auto& w : walls_)
        if(w.getGlobalBounds().intersects(r)) return true;
    return false;
}