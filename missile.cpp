#include "missile.h"
#include "explosion.h"
#include "smoke.h"

missile::missile(int _player, sf::Vector2f _pos, sf::Vector2f _vel, sf::Vector2f _facing, bool air) {
    airOnly = true;
    turnSpeed = 1;
    accel = 0.12;
    type = MISSILE;
    hitpoint = 75;
    player = _player;
    pos = _pos;
    vel = _vel + 8.f * _facing;
    facing = _facing;
    scale = {0.02, 0.02};
    SIZE = {118, 180};
    target = NULL;
    time = 0;
}


void missile::updateGame(std::vector<object*>& pList, std::vector<object*>& pOther) {
    vel = vel * 0.97f;
    ++time;
    if (time > 30) if (target == NULL || target->dead()) target = getNearest(pList, {BOMBER, INTERCEPTOR, FIGHTER});
    if (target != NULL) {
        sf::Vector2f targetPos = target->pos;
        goToward(targetPos);
    }
    else thrust();
    if (time > 300) {
        destroyed = true;
        pOther.push_back(new explosion(pos, facing, {0.2, 0.2}));
    }
    for (auto p : pList) {
        if (player != p->player && collision(p) && !(airOnly && p->type == CARRIER)) {
            p->hitpoint -= hitpoint;
            destroyed = true;
            pOther.push_back(new explosion(pos, facing, {0.2, 0.2}));
            break;
        }
    }
}
