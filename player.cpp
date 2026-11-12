#include "player.h"
#include "config.h"



Player::Player(sf::Vector2f size,sf::Color color,sf::Vector2f pos):Character(size,color,pos){
}

void Player::update(){
    last_pos = c_rect.getPosition();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
        if(c_rect.getPosition().x > 0){
            c_rect.move(sf::Vector2f(-5.f,0.f));
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
        if(c_rect.getPosition().x < (Config::windowWidth - c_rect.getSize().x)){
            c_rect.move(sf::Vector2f(5.f,0.f));
        } 
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
        if(c_rect.getPosition().y > 0){
            c_rect.move(sf::Vector2f(0.f,-5.f));
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
        if(c_rect.getPosition().y < (Config::windowHeight - c_rect.getSize().y)){
            c_rect.move(sf::Vector2f(0.f,5.f));
        }
    }
}


BlockType Player::collision_set(Wall& obj){
    auto intersection = obj.wBounds().findIntersection(Bounds());
    if(obj.get_type() == BlockType::Block_Wall){
        if(intersection.has_value()){
            c_rect.setPosition(last_pos);
            return obj.get_type();
        }
    }
    if(obj.get_type() == BlockType::Block_Win){
        if(intersection.has_value()){
            return obj.get_type();
        }
    }
    return BlockType::Block_Wall;
}