#pragma once
#include <SFML/Graphics.hpp>
#include "wall.h"
#include "character.h"

class Player:public Character{
    public:
        Player(sf::Vector2f size,sf::Color color,sf::Vector2f pos);

        void update();
        // void set_pos();
        BlockType collision_set(Wall& wall);
};