#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Tilemap : public sf::Drawable {
public:
    explicit Tilemap(const std::string& filename, sf::Vector2f tileSize = {32.f, 32.f});
    bool collides(const sf::FloatRect& rect) const noexcept;

private:
    std::vector<sf::RectangleShape> walls_;
    void draw(sf::RenderTarget& rt, sf::RenderStates st) const override {
        for (auto const& w : walls_) rt.draw(w, st);
    }
};
