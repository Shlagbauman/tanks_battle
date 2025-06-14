#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "../src/Tank.hpp"
#include "../src/Bullet.hpp"

TEST_CASE("Tank shield timer counts down")
{
    Tank t({0,0},
           sf::Keyboard::W, sf::Keyboard::S,
           sf::Keyboard::A, sf::Keyboard::D,
           {sf::Keyboard::Space},
           "assets/tank_green.png",
           0);

    t.enableShield(1.f);
    std::vector<Bullet> pool;

    t.update(0.7f, pool);
    REQUIRE( t.shielded() );

    t.update(0.5f, pool);
    REQUIRE_FALSE( t.shielded() );
}

TEST_CASE("Bullet spawns 50 px ahead of tank nose")
{
    sf::Vector2f pos{100.f, 100.f};
    sf::Vector2f dir{  1.f,   0.f};
    Bullet b(pos + dir * 50.f, dir, 42);

    REQUIRE( b.position().x == Catch::Approx(150.f).margin(1.0) );
}