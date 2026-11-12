#pragma once
#include <SFML/Graphics.hpp>
#include "player.h"
#include "character.h"


// enum class avoiDir{ None,Left,Right };


class Enemy:public Character{
    private:
        std::vector<std::pair<int,int>> path;
        sf::Vector2f last_position_player;
        std::pair<int,int> last_position_enemy;
    public:
        Enemy(sf::Vector2f size,sf::Color color,sf::Vector2f pos);

        void allowed_moves(std::vector<std::vector <bool>>& map_bool,Player& p);
};

bool check_move(int y,int x,std::vector<std::vector <bool>>& map_bool);
std::pair<int,int> install_cell(sf::Vector2f position,Character& obj);
std::vector<std::pair<int,int>> build_bfs(int pos_enemy_y,int pos_enemy_x,int pos_pl_y,int pos_pl_x,std::vector<std::vector <bool>>& map_bool);
void move_enemy_bfs(sf::RectangleShape& c_rect, sf::Vector2f next_move);
void cuthing_player(Player& p, sf::RectangleShape& c_rect);
