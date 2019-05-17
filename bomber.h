#pragma once
#include "vehicle.h"

class bomber : public vehicle {

    public :
        object* target;
        object* airTarget;
        int bombLoaded;
        float bombRange;
        bool running = false;
        int bombReloadTime;
        int bombReloading;
        bool oldOnScreen;
        float shotRange;
        float runRange;
        int ammo = 0;
        int maxAmmo;
        int gunRange;
        int gunReloading;
        int gunReloadTime;
        bomber(int _player, sf::Vector2f _pos, sf::Vector2f _vel, sf::Vector2f _facing);
        //object* getTartget(std::vector<object*> &pVehicles);
        void updateAI(std::vector<object*>& pList, std::vector<object*>& pOther);
        void dropBomb(std::vector<object*>& pOther);
        void reload();
        void shoot(std::vector<object*>& pOther, sf::Vector2f toTarget);
};
