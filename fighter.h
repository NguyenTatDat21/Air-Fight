#pragma once

#include "vehicle.h"
#include "game.h"
#include "SFML/System.hpp"

class fighter : public vehicle
{
    public :

        object* target;
        int maxAmmo;
        bool running = false;
        int reloadTime;
        int ammo;
        int reloading;
        bool oldOnScreen;
        float shotRange;
        float runRange;
        fighter(int player, sf::Vector2f _pos, sf::Vector2f _vel, sf::Vector2f _facing);
        object* getTartget(std::vector<object*> &pVehicles);
        void updateAI(std::vector<object*>& pList, std::vector<object*>& pOther);
        void shoot(std::vector<object*>& pOther);
        void reload();

};
