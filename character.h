#pragma once
#include <SFML/Graphics.hpp>

class Character{
    protected:
        sf::RectangleShape c_rect;
        sf::Vector2f last_pos;
    public:
        Character(sf::Vector2f size,sf::Color color,sf::Vector2f pos);

        void draw(sf::RenderWindow& window);
        sf::FloatRect Bounds()const;
        sf::Vector2f get_pos()const;
        sf::Vector2f get_size()const;
        // void set_pos();
};