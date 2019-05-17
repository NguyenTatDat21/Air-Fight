#pragma once

#include "object.h"

class missile : public object {
    public :
        bool airOnly;
        object* target;
        int time;
        missile(int _player, sf::Vector2f _pos, sf::Vector2f _vel, sf::Vector2f _facing, bool air = false);
        void updateGame(std::vector<object*>& pList, std::vector<object*>& pOther);
};

