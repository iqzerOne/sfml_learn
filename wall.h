#pragma once
#include <SFML/Graphics.hpp>

enum class BlockType{ Block_Wall,Block_Win,Block_Invisible };

class Wall{
    private:
        sf::RectangleShape wall;
        BlockType type;
    public:
        Wall(sf::Vector2f size,sf::Color color,sf::Vector2f pos,BlockType type);

        void draw(sf::RenderWindow& window);
        sf::FloatRect wBounds();
        BlockType get_type()const;
        void test();
        
};