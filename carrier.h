#pragma once

#include "vehicle.h"

class carrier : public vehicle {
    public :
        int resource;
        carrier(int _player, sf::Vector2f _pos, sf::Vector2f _facing);
        void update();
        void createVehicle(std::vector<object*>& pList, int resource);
};



