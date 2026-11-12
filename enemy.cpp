#include "enemy.h"
#include <iostream>
#include "config.h"


Enemy::Enemy(sf::Vector2f size,sf::Color color,sf::Vector2f pos):Character(size, color, pos){
    last_position_enemy = install_cell(pos,*this);
}

bool check_move(int y,int x,std::vector<std::vector <bool>>& map_bool){
    if(y < 0 || y >= Config::rows){
        return true;
    }
    if(x < 0 || x >= Config::columns){
        return true;
    }
    return map_bool[y][x];
}

std::pair<int,int> install_cell(sf::Vector2f position,Character& obj){
    int pos_x = static_cast<int>((position.x + obj.get_size().x / 2.f) / Config::CELL.x);
    int pos_y = static_cast<int>((position.y + obj.get_size().y / 2.f) / Config::CELL.y);
    if (pos_x < 0)  pos_x = 0;
    if (pos_y < 0)  pos_y = 0;
    if (pos_x >= Config::columns)   pos_x = Config::columns - 1;
    if (pos_y >= Config::rows)  pos_y = Config::rows - 1;
    return {pos_y,pos_x};
}

std::vector<std::pair<int,int>> build_bfs(int pos_enemy_y,int pos_enemy_x,int pos_pl_y,int pos_pl_x,std::vector<std::vector <bool>>& map_bool){
    std::vector<std::vector<bool>> visited(
        Config::rows, std::vector<bool>(Config::columns, false)
    );
    std::pair<int,int> coordinates = {pos_enemy_y,pos_enemy_x};
    std::vector<std::vector<std::pair<int,int>>> parent(
        Config::rows, std::vector<std::pair<int,int>>(Config::columns, {-1,-1})
    );
    std::vector<std::pair<int,int>> queue;

    queue.push_back(coordinates);
    visited[pos_enemy_y][pos_enemy_x] = true;
    bool bfs = false;

    while(!queue.empty()){
        coordinates = queue[0];
        queue.erase(queue.begin());
        auto [y, x] = coordinates;
        if(y == pos_pl_y && x == pos_pl_x){
            bfs = true;
            break;
        }
        if(!check_move(y-1,x,map_bool)){//вверх
            if(!visited[y-1][x]){
                visited[y-1][x] = true;
                parent[y-1][x] = {y,x};
                queue.push_back({y-1,x});
            }
        }
        if(!check_move(y+1,x,map_bool)){//вниз
            if(!visited[y+1][x]){
                visited[y+1][x] = true;
                parent[y+1][x] = {y,x};
                queue.push_back({y+1,x});
            }
        }
        if(!check_move(y,x-1,map_bool)){//лево
            if(!visited[y][x-1]){
                visited[y][x-1] = true;
                parent[y][x-1] = {y,x};
                queue.push_back({y,x-1});
            }
        }
        if(!check_move(y,x+1,map_bool)){//право
            if(!visited[y][x+1]){
                visited[y][x+1] = true;
                parent[y][x+1] = {y,x};
                queue.push_back({y,x+1});
            }
        }
    }

    std::vector<std::pair<int,int>> path;
    if(bfs){
        std::pair<int,int> current_pos = {pos_pl_y,pos_pl_x};
        path.push_back({pos_pl_y,pos_pl_x});
        while(parent[current_pos.first][current_pos.second] != std::pair<int,int> {pos_enemy_y,pos_enemy_x}){
            path.push_back(parent[current_pos.first][current_pos.second]);
            auto[y,x]= parent[current_pos.first][current_pos.second]; 
            current_pos = {y,x};
        }
        std::reverse(path.begin(), path.end());
    }
    return path;
}

void move_enemy_bfs(sf::RectangleShape& c_rect, sf::Vector2f next_move){
    if(next_move.x < c_rect.getPosition().x + c_rect.getSize().x / 2.f){
        c_rect.move(sf::Vector2f(-Config::SpeedEnemy.x,0.f));
    }
    if(next_move.x > c_rect.getPosition().x + c_rect.getSize().x / 2.f){
        c_rect.move(sf::Vector2f(Config::SpeedEnemy.x,0.f));
    }
    if(next_move.y < c_rect.getPosition().y + c_rect.getSize().y / 2.f){
        c_rect.move(sf::Vector2f(0.f,-Config::SpeedEnemy.y));
    }
    if(next_move.y > c_rect.getPosition().y + c_rect.getSize().y / 2.f){
        c_rect.move(sf::Vector2f(0.f,Config::SpeedEnemy.y));
    }
}

void cuthing_player(Player& p, sf::RectangleShape& c_rect){
    sf::Vector2f last_pos_player = p.get_pos();
    if(last_pos_player.x < c_rect.getPosition().x){
        c_rect.move(sf::Vector2f(-Config::SpeedEnemy.x,0.f));
    }
    if(last_pos_player.x > c_rect.getPosition().x){
        c_rect.move(sf::Vector2f(Config::SpeedEnemy.x,0.f));
    }

    if(last_pos_player.y < c_rect.getPosition().y){
        c_rect.move(sf::Vector2f(0.f,-Config::SpeedEnemy.y));
    }
    if(last_pos_player.y > c_rect.getPosition().y){
        c_rect.move(sf::Vector2f(0.f,Config::SpeedEnemy.y));
    }
}

void Enemy::allowed_moves(std::vector<std::vector <bool>>& map_bool, Player& p){
    
    auto[pos_enemy_y,pos_enemy_x] = install_cell(c_rect.getPosition(), *this);
    auto[pos_pl_y,pos_pl_x] = install_cell(p.get_pos(), p);
    if(last_position_player != p.get_pos()){
        last_position_player = p.get_pos();
        auto[pos_pl_y,pos_pl_x] = install_cell(p.get_pos(), p);
        path.clear();
        if(pos_enemy_y != pos_pl_y || pos_enemy_x != pos_pl_x){
            path = build_bfs(pos_enemy_y,pos_enemy_x,pos_pl_y,pos_pl_x,map_bool);
        }
    }
    int path_y = last_position_enemy.first;
    int path_x = last_position_enemy.second;
    if(path.size() >= 1){
        if (std::make_pair(pos_enemy_y, pos_enemy_x) != path[0]) {
            std::tie(path_y, path_x) = path[0];
        }else{
           path.erase(path.begin()); 
        }
        
        
    }
    if(pos_enemy_y == pos_pl_y && pos_enemy_x == pos_pl_x){
        path.clear();
        cuthing_player(p, c_rect);
    }
    sf::Vector2f next_move(
    static_cast<float>(path_x) * Config::CELL.x + (Config::CELL.x / 2),
    static_cast<float>(path_y) * Config::CELL.y + (Config::CELL.y / 2)
    );
    if(path.size() != 0){
        move_enemy_bfs(c_rect, next_move);
        auto[pos_enemy_y,pos_enemy_x] = install_cell(c_rect.getPosition(), *this);
        last_position_enemy = {pos_enemy_y,pos_enemy_x};

    }
}

