#include "fighter.h"
#include "iostream"
#include "bullet.h"
#include "misc.h"
#include "explosion.h"


fighter::fighter(int _player, sf::Vector2f _pos, sf::Vector2f _vel, sf::Vector2f _facing) {
    type = FIGHTER;
    player = _player;
    SIZE = {179, 196};
    scale = {0.1, 0.1};
    pos = _pos;
    facing = _facing;
    vel = _vel + facing * 12.f;
    hitpoint = 20;
    collisionRadius = 13;
    turnSpeed = 1.43;
    accel = 0.12;
    shotRange = 200;
    runRange = 200;
    oldOnScreen = true;
    target = NULL;
    maxAmmo = 8;
    reloadTime = 200;
    reloading = 200;
    ammo = 0;
}

void fighter::reload() {
    if (reloading == reloadTime) {
        ammo = maxAmmo;
        reloading = 0;
    }
    if (!ammo) ++reloading;
}

object* fighter::getTartget(std::vector<object*>& pVehicles) {
    object* ret = NULL;
    ret = getNearest(pVehicles, {INTERCEPTOR});
    if (ret != NULL) return ret;
    ret = getNearest(pVehicles, {FIGHTER, BOMBER});
    if (ret != NULL) return ret;
    ret = getNearest(pVehicles, {CARRIER});
    if (ret != NULL) return ret;
    return ret;
}


void fighter::updateAI(std::vector<object*>& pList, std::vector<object*>& pOther) {
    reload();
    if ((oldOnScreen && !onScreen())
        || target == NULL
        || target->dead()
        || (double) rand() / RAND_MAX < 0.005 ) {
        target = getTartget(pList);
    }
    oldOnScreen = onScreen();
    if (target != NULL) {
        sf::Vector2f targetPos = target->pos + target->vel * 12.f;
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
                    if (dot(toTarget, facing) * dot(toTarget, facing) > 0.97 * dist) {
                        if (ammo) shoot(pOther);
                    }
                }
            }
            if (!ammo) running = true;
        }
    }
    if (dead()) {
        pOther.push_back(new explosion(pos, facing, {0.2, 0.2}));
    }
}

void fighter::shoot(std::vector<object*>& pOther) {
    pOther.push_back(new bullet(player, pos , vel, facing));
    --ammo;
}


