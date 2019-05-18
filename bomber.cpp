#include "bomber.h"
#include "bomb.h"
#include "bullet.h"
#include "misc.h"
#include "explosion.h"
#include<iostream>


bomber::bomber(int _player, sf::Vector2f _pos, sf::Vector2f _vel, sf::Vector2f _facing) {
    type = BOMBER;
    player = _player;
    SIZE = {291, 288};
    scale = {0.4, 0.25};
    pos = _pos;
    facing = _facing;
    vel = _vel + facing * 5.f;
    hitpoint = 250;
    collisionRadius = 30;
    turnSpeed = 0.10;
    accel = 0.019;
    bombRange = 45;
    bombReloading = 0;
    bombReloadTime = 1000;
    bombLoaded = 1;
    ammo = 0;
    maxAmmo = 3;
    gunRange = 115;
    gunReloading = -100;
    gunReloadTime = 5;
    target = NULL;
    airTarget = NULL;
}


void bomber::updateAI(std::vector<object*>& pList, std::vector<object*>& pOther) {
    reload();
    target = getNearest(pList, {CARRIER});
    if (target != NULL) {
        sf::Vector2f targetPos = target->pos + target->vel * 60.f;
        float dist = sqrDist(pos, targetPos);
        if (running) {
            thrust();
            if (bombLoaded) running = false;
        }
        else {
            goToward(targetPos);
            if (bombLoaded) {
                if (dist < bombRange * bombRange) {
                    dropBomb(pOther);
                    bombLoaded = 0;
                }
            }
            else {
                running = true;

            }
        }
    }
    airTarget = getNearest(pList, {FIGHTER, INTERCEPTOR, BOMBER});
    if (airTarget != NULL) {
        sf::Vector2f targetPos = airTarget->pos + airTarget->vel * 6.f;
        sf::Vector2f toTarget = targetPos - pos;
        float dist = sqrDist(pos, targetPos);
        if (dist <= gunRange * gunRange) {
            if (ammo) {
                shoot(pOther, toTarget);
            }
        }
    }
    if (dead()) {
        pOther.push_back(new explosion(pos, facing, {0.5, 0.5}));
    }
}


void bomber::dropBomb(std::vector<object*>& pOther) {
    pOther.push_back(new bomb(player, pos - facing * 0.7f * getRealSize().y, vel, facing));
}


void bomber::reload() {
    if (bombReloading == bombReloadTime) {
        bombLoaded = 1;
        bombReloading = 0;
    }
    if (!bombLoaded) ++bombReloading;
    if (gunReloading == gunReloadTime) {
        ammo = maxAmmo;
        gunReloading = 0;
    }
    if (!ammo) ++gunReloading;

}

void bomber::shoot(std::vector<object*>& pOther, sf::Vector2f toTarget) {
    pOther.push_back(new bullet(player, pos , vel, norm(toTarget), true));
    --ammo;
}


