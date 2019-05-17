#pragma once

#include"object.h"


class explosion : public object {
    public :
        int time;
        explosion(sf::Vector2f _pos, sf::Vector2f _facing, sf::Vector2f _scale);
        void update();
};

