#include "bomb.h"
#include "explosion.h"
#include "misc.h"

bomb::bomb(int _player, sf::Vector2f _pos, sf::Vector2f _vel, sf::Vector2f _facing) {
    type = BOMB;
    hitpoint = 100;
    player = _player;
    pos = _pos;
    vel = _vel;
    facing = _facing;
    scale = {0.1, 0.1};
    SIZE = {144, 341};
    time = 300;
}


void bomb::update() {
    vel *= 0.994f;
    pos += vel;
    scale = mul(scale, sf::Vector2f(0.9985, 0.9975));
    --time;
    if (time == 0) destroyed = true;
}

void bomb::updateGame(std::vector<object*>& pList, std::vector<object*>& pOther) {
    if (destroyed) {
        for (auto p : pList) {
            if (p->type == CARRIER) {
                if (player != p->player && collision(p)) {
                    p->hitpoint -= hitpoint;
                    pOther.push_back(new explosion(pos, facing, {0.6, 0.6}));
                    break;
                }
            }
        }

    }
}
