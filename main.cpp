#include <SFML/Graphics.hpp>
#include "config.h"
#include "character.h"
#include "player.h"
#include "wall.h"
#include "enemy.h"
#include <iostream>


int main() {
    sf::RenderWindow window(sf::VideoMode({Config::windowWidth, Config::windowHeight}), "SFML Hello");
    window.setFramerateLimit(60);
    std::vector<Wall> wall;
    for(int i = 0; i < 3; i++){
        Wall rect(sf::Vector2f(50.f,50.f),sf::Color::Green,sf::Vector2f(400+i*50.f,350.f),BlockType::Block_Wall);
        wall.push_back(rect);
    }
    Wall win(sf::Vector2f(50.f,50.f),sf::Color::Yellow,sf::Vector2f(700.f, 550.f),BlockType::Block_Win);

    std::vector<std::vector<bool>> blocked(Config::rows, std::vector<bool>(Config::columns, false));
    std::vector<Wall> q;
    for(int y = 0; y < Config::rows; y++){
        for(int x = 0; x < Config::columns; x++){
            float left = x * Config::CELL.x;
            float top = y * Config::CELL.y;
            float cx = (left + Config::CELL.x / 2);
            float cy = (top + Config::CELL.y / 2);
            sf::Vector2f container(cx, cy);
            Wall invis(sf::Vector2f(Config::CELL),sf::Color::Transparent,sf::Vector2f(left, top),BlockType::Block_Invisible);
            invis.test();
            q.push_back(invis);
            for(int i = 0; i< wall.size();i++){ 
                if (wall[i].wBounds().contains(container)){
                    blocked[y][x] = true;
                }
            }
            if (win.wBounds().contains(container)){
                blocked[y][x] = true;
            }
        }
    }

    Player p(sf::Vector2f(10.f,10.f),sf::Color::Red,sf::Vector2f(200.f,150.f));
    Enemy e(sf::Vector2f(10.f,10.f),sf::Color::Blue,sf::Vector2f(425.f,450.f));
    BlockType type;
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        p.update();
        e.allowed_moves(blocked,p);
        for(int i = 0; i < wall.size();i++){
            type = p.collision_set(wall[i]);
        }
        type = p.collision_set(win);
        if(type == BlockType::Block_Win){
            window.clear(sf::Color(255, 165, 0));
        }else{
            window.clear(sf::Color(40, 40, 50));
        }
        auto intersection = e.Bounds().findIntersection(p.Bounds());
        if(intersection.has_value()){
            window.clear(sf::Color(212, 79, 79));
            std::cout << "kill" << std::endl;
        }
        p.draw(window);
        e.draw(window);
        for(int i = 0; i < wall.size(); i++){
            wall[i].draw(window);
        }
        win.draw(window);
        for(int i = 0; i < q.size(); i++){
            q[i].draw(window);
        }
        window.display();
    }

    return 0;
}