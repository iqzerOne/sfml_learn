#include "wall.h"

Wall::Wall(sf::Vector2f size,sf::Color color,sf::Vector2f pos,BlockType type){
    this->wall.setSize(size);
    this->wall.setFillColor(color);
    this->wall.setPosition(pos);
    this->type = type;
}

void Wall::draw(sf::RenderWindow& window){
    window.draw(wall);
}

sf::FloatRect Wall::wBounds(){
    return wall.getGlobalBounds();
}

BlockType Wall::get_type()const{
    return type;
}

void Wall::test(){
    wall.setOutlineColor(sf::Color::White);
    wall.setOutlineThickness(1.f);
}
