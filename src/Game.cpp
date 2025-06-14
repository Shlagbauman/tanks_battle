#include "Game.hpp"
#include <random>
#include <stdexcept>

Game::Game(const std::string& a)
    : map_("maps/level1.txt")
    , window_({1024,768}, "Tanks2D")
    , t1_({ 96,  96}, sf::Keyboard::W,  sf::Keyboard::S,
                    sf::Keyboard::A,  sf::Keyboard::D,
                    {sf::Keyboard::Space},
                    a + "/tank_green.png", 0)
    , t2_({928, 672}, sf::Keyboard::Up,   sf::Keyboard::Down,
                    sf::Keyboard::Left, sf::Keyboard::Right,
                    {sf::Keyboard::RControl, sf::Keyboard::LControl, sf::Keyboard::Enter},
                    a + "/tank_red.png",   1)
{
    if(!font_.loadFromFile(a + "/OpenSans-Regular.ttf"))
        throw std::runtime_error("font not found");
    scoreText_.setFont(font_);
    scoreText_.setCharacterSize(24);
    scoreText_.setPosition(10.f, 10.f);

    boomBuf_.loadFromFile(a + "/explosion.wav");
    boom_.setBuffer(boomBuf_);
    boom_.setVolume(45.f);

    bonusSpots_ = {{512,384},{512,256},{512,512},{320,384},{704,384}};
    bonuses_.emplace_back(bonusSpots_[0], BonusType::Speed);
}

int Game::run()
{
    sf::Clock frame;
    while(window_.isOpen())
    {
        sf::Event e;
        while(window_.pollEvent(e)){
            if(e.type==sf::Event::Closed) window_.close();
            if(e.type==sf::Event::KeyPressed && e.key.code==sf::Keyboard::F1)
                nextMap();
        }

        float dt = frame.restart().asSeconds();

        auto old1 = t1_.position();  t1_.update(dt, bullets_);
        if(map_.collides(t1_.bounds())) t1_.setPosition(old1);

        auto old2 = t2_.position();  t2_.update(dt, bullets_);
        if(map_.collides(t2_.bounds())) t2_.setPosition(old2);

        for(auto& b : bullets_) b.update(dt);

        handle();

        if(bonuses_.empty() && bonusClk_.getElapsedTime().asSeconds()>bonusCD_)
            spawnBonus();

        window_.clear();
        window_.draw(map_);
        for(auto& b : bullets_) window_.draw(b);
        window_.draw(t1_); window_.draw(t2_);
        for(auto& bo : bonuses_) window_.draw(bo);

        scoreText_.setString(std::to_string(score1_) + " : " + std::to_string(score2_));
        window_.draw(scoreText_);
        window_.display();
    }
    return 0;
}


void Game::handle()
{
    for(std::size_t i = 0; i < bullets_.size(); )
    {
        auto& b = bullets_[i];

        if(map_.collides(b.bounds())) {
            bullets_.erase(bullets_.begin()+i);
            continue;
        }

        bool hit = false;
        if(b.bounds().intersects(t1_.bounds()) && !t1_.shielded()){
            ++score2_; hit = true;
        }
        else if(b.bounds().intersects(t2_.bounds()) && !t2_.shielded()){
            ++score1_; hit = true;
        }

        if(hit){
            boom_.play();
            bullets_.clear();
            resetRound();
            break;
        } else {
            ++i;
        }
    }

    for(auto it = bonuses_.begin(); it != bonuses_.end(); )
    {
        bool picked = false;
        if(it->bounds().intersects(t1_.bounds())){
            if(it->type() == BonusType::Speed ) t1_.applyBonus(1.5f,5.f);
            if(it->type() == BonusType::Shield) t1_.enableShield(3.f);
            picked = true;
        }
        if(it->bounds().intersects(t2_.bounds())){
            if(it->type() == BonusType::Speed ) t2_.applyBonus(1.5f,5.f);
            if(it->type() == BonusType::Shield) t2_.enableShield(3.f);
            picked = true;
        }
        if(picked) it = bonuses_.erase(it);
        else       ++it;
    }
}

void Game::spawnBonus()
{
    static std::mt19937 rng{ std::random_device{}() };
    std::uniform_int_distribution<size_t> spot(0, bonusSpots_.size()-1);
    std::uniform_int_distribution<int> kind(0,1);
    BonusType t = (kind(rng)==0) ? BonusType::Speed : BonusType::Shield;
    bonuses_.emplace_back(bonusSpots_[ spot(rng) ], t);
    bonusClk_.restart();
}

void Game::nextMap()
{
    usingFirst_ = !usingFirst_;
    map_ = Tilemap(usingFirst_ ? mapFile1_ : mapFile2_);
    resetRound();
}

void Game::resetRound()
{
    t1_.respawn({ 96,  96});
    t2_.respawn({928, 672});
    bullets_.clear();
}