#include "bullet.h"
#include "spark.h"

bullet::bullet(int _player, sf::Vector2f _pos, sf::Vector2f _vel, sf::Vector2f _facing, bool air) {
    airOnly = air;
    type = BULLET;
    hitpoint = 1;
    player = _player;
    pos = _pos;
    vel = _vel + _facing * 15.f;
    facing = _facing;
    scale = {0.1, 0.5};
    SIZE = {10, 17};
}


void bullet::updateGame(std::vector<object*>& pList, std::vector<object*>& pOther) {
    for (auto p : pList) {
        if (player != p->player && collision(p) && !(airOnly && p->type == CARRIER)) {
            p->hitpoint -= hitpoint;
            destroyed = true;
            pOther.push_back(new spark(pos, -facing));
            break;
        }

    }
}
