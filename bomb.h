#pragma once

#include"object.h"

class bomb : public object {
    public :
        int time;
        bomb(int _player, sf::Vector2f _pos, sf::Vector2f _vel, sf::Vector2f _facing);
        void update();
        void updateGame(std::vector<object*>& pList, std::vector<object*>& pOther);
};



