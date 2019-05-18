#include "SFML/Graphics.hpp"
#include "object.h"
#include "cmath"
#include "misc.h"

void object::update() {

    pos += vel;
}

void object::updateAI(std::vector<object*>& pList, std::vector<object*>& pOther) {

}

void object::updateGame(std::vector<object*>& pList, std::vector<object*>& pOther) {

}

void object::createVehicle(std::vector<object*>& pList, int resource) {

}

bool object::collision(object* other) {
    return (sqrDist(pos, other->pos) <= other->collisionRadius * other->collisionRadius);
}

double object::getDirection() {
    double dir = (atan(facing.y / facing.x) * 180 / PI) + 90;
    if (facing.x < 0) dir += 180;
    return dir;
}

sf::Vector2f object::getRealSize() {
    return mul(SIZE, scale);
}

sf::Vector2f object::getCenter() {
    return pos + getRealSize() * 0.5f;
}

sf::Vector2f object::getRealPos() {
    sf::Vector2f realSize = getRealSize();

    return pos + (facing * realSize.y + rotate(facing, -90) * realSize.x)  * 0.5f;
}


bool object::onScreen() {
    return (pos.x > 0 && pos.y > 0 && pos.x < SCREEN_W && pos.y < SCREEN_H);
}


sf::Color object::getColor() {
    if (type <= BOMBER) {
        if (player == 0) return sf::Color(255, 150, 125, 255);
        if (player == 1) return sf::Color(150, 255, 125, 255);
    }
    return sf::Color(255, 255, 255, 255);
}

sf::Sprite object::getSprite(std::vector<sf::Texture>& texture) {
    sf::Sprite sprite;
    sprite.setTexture(texture[type]);
    if (animated) sprite.setTextureRect(rect);
    sprite.setScale(scale);
    sprite.setRotation(getDirection());
    sprite.setPosition(getRealPos());
    sprite.setColor(getColor());
    return sprite;
}


object* object::getNearest(std::vector<object*> pList, std::vector<int> typeL) {
    object* nearest = NULL;
    float nearestDist = 10000000;
    for (auto p : pList) {
        if (p->onScreen() && std::find(typeL.begin(), typeL.end(), p->type) != typeL.end() && p->player != player) {
            float dist = sqrDist(pos, p->pos);
            if (dist < nearestDist) {
                nearest = p;
                nearestDist = dist;
            }
        }
    }
    return nearest;
}

bool object::dead() {
    return hitpoint <= 0;
}


void object::turn(float direction) {
    facing = rotate(facing, direction * turnSpeed);
}

void object::goToward(sf::Vector2f targetPos, bool th) {
    sf::Vector2f targetDirection = targetPos - pos;
    if (cross(facing, targetDirection) > 0) {
        turn(1);
    }
    else {
        turn(-1);
    }
    if (th) thrust();
}

void object::thrust() {
    vel += facing * accel;
}


void object::goAway(sf::Vector2f targetPos) {
    sf::Vector2f targetDirection = pos - targetPos;
    if (cross(facing, targetDirection) > 0) {
        turn(1);
    }
    else {
        turn(-1);
    }
    thrust();
}

