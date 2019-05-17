#pragma once

#include "object.h"

class bullet : public object {
    public :
        bool airOnly;
        bullet(int _player, sf::Vector2f _pos, sf::Vector2f _vel, sf::Vector2f _facing, bool air = false);
        void updateGame(std::vector<object*>& pList, std::vector<object*>& pOther);
};

