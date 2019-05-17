#include "interceptor.h"
#include "iostream"
#include "missile.h"
#include "misc.h"
#include "explosion.h"


interceptor::interceptor(int _player, sf::Vector2f _pos, sf::Vector2f _vel, sf::Vector2f _facing) {
    type = INTERCEPTOR;
    player = _player;
    SIZE = {135, 196};
    scale = {0.2, 0.2};
    pos = _pos;
    facing = _facing;
    vel = _vel + facing * 10.f;
    hitpoint = 40;
    collisionRadius = 20;
    turnSpeed = 1;
    accel = 0.11;
    shotRange = 400;
    runRange = 400;
    oldOnScreen = true;
    target = NULL;
    maxAmmo = 1;
    reloadTime = 500;
    reloading = 500;
    ammo = 0;
}

void interceptor::reload() {
    if (reloading == reloadTime) {
        ammo = maxAmmo;
        reloading = 0;
    }
    if (!ammo) ++reloading;
}

object* interceptor::getTartget(std::vector<object*>& pVehicles) {
    object* ret = NULL;
    ret = getNearest(pVehicles, {BOMBER});
    if (ret != NULL) return ret;
    ret = getNearest(pVehicles, {FIGHTER, INTERCEPTOR});
    if (ret != NULL) return ret;
    //ret = getNearest(pVehicles, {CARRIER});
    //if (ret != NULL) return ret;
    return ret;
}


void interceptor::updateAI(std::vector<object*>& pList, std::vector<object*>& pOther) {
    reload();
    if ((oldOnScreen && !onScreen())
        || target == NULL
        || target->dead()
        || (double) rand() / RAND_MAX < 0.005 ) {
        target = getTartget(pList);
    }
    oldOnScreen = onScreen();
    if (target != NULL) {
        sf::Vector2f targetPos = target->pos;
        float dist = sqrDist(pos, targetPos);
        sf::Vector2f toTarget = targetPos - pos;
        if (running) {
            if (dist < runRange * runRange) {
                goAway(targetPos);
            }
            else thrust();
            if (ammo && dist > runRange * runRange) {
                running = false;
            }
        }

        else {
            goToward(targetPos);
            if (dist <= shotRange * shotRange) {
                if (dot(toTarget, facing) > 0) {
                    if (dot(toTarget, facing) * dot(toTarget, facing) > 0.95 * dist) {
                        if (ammo) shoot(pOther);
                    }
                }
            }
            if (!ammo) running = true;
        }
    }
    else thrust();
    if (dead()) {
        pOther.push_back(new explosion(pos, facing, {0.4, 0.4}));
    }
}

void interceptor::shoot(std::vector<object*>& pOther) {
    pOther.push_back(new missile(player, pos + getRealSize().x * rotate(facing, -90) * 0.5f, vel, facing));
    pOther.push_back(new missile(player, pos + getRealSize().x * rotate(facing, 90) * 0.5f, vel, facing));
    --ammo;
}


