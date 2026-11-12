#include "character.h"

Character::Character(sf::Vector2f size,sf::Color color,sf::Vector2f pos){
    this->c_rect.setSize(size);
    this->c_rect.setFillColor(color);
    this->c_rect.setPosition(pos);
}

sf::Vector2f Character::get_pos()const{
    return c_rect.getPosition();
}

void Character::draw(sf::RenderWindow& window){
    window.draw(c_rect);
}
sf::FloatRect Character::Bounds()const{
    return c_rect.getGlobalBounds();
}

sf::Vector2f Character::get_size()const{
    return c_rect.getSize();
}
// void Character::set_pos(){
//     c_rect.setPosition(last_pos);
// }