#pragma once
#include "object.h"

class spark : public object {
    public :
        int time;
        spark(sf::Vector2f _pos, sf::Vector2f _facing);
        void update();
};

