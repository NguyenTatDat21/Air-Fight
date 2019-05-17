#pragma once
#include "object.h"

class smoke : public object {
    public :
        int time;
        smoke(sf::Vector2f _pos, sf::Vector2f _facing);
        void update();
};
