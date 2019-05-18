#include "carrier.h"
#include "fighter.h"
#include "bomber.h"
#include "interceptor.h"
#include "explosion.h"


carrier::carrier(int _player, sf::Vector2f _pos, sf::Vector2f _facing) {
    type = CARRIER;
    player = _player;
    pos = _pos;
    facing = _facing;
    hitpoint = 1500;
    accel = 0.0025;
    turnSpeed = 0.016;
    resource = 0;
    collisionRadius = 60;
    SIZE = {185, 318};
    scale = {0.7, 0.8};
}

void carrier::update() {
    thrust();
    turn(-1);
    vel *= (float) 0.97;
    pos += vel;
}


void carrier::updateAI(std::vector<object*> &pList, std::vector<object*> &pOther) {
    if (dead()) {
        pOther.push_back(new explosion(pos, facing, {1.5, 1.5}));
    }
}

void carrier::createVehicle(std::vector<object*>& pList, int resource) {
    if ((resource / 40) >= 10) {
        pList.push_back(new bomber(player, pos, vel, facing));
        return;
    }
    if ((resource / 40) >= 5) {
        pList.push_back(new interceptor(player, pos, vel, facing));
        return;
    }
    if ((resource / 40) >= 1) {
        pList.push_back(new fighter(player, pos, vel, facing));
        return;
    }
}
