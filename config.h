#pragma once
#include <SFML/Graphics.hpp>

namespace Config {
    inline unsigned int windowWidth = 800;
    inline unsigned int windowHeight = 600;
    inline sf::Vector2f SpeedEnemy = {2.f, 2.f};
    inline sf::Vector2f CELL = {25.f, 25.f};
    inline int columns = Config::windowWidth / Config::CELL.x;
    inline int rows = Config::windowHeight / Config::CELL.y;
}