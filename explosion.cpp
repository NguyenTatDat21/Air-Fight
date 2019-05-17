#include "explosion.h"


explosion::explosion(sf::Vector2f _pos, sf::Vector2f _facing, sf::Vector2f _scale) {
    pos = _pos;
    animated = true;
    type = EXPLOSION;
    facing = _facing;
    vel = facing * 0.5f;
    SIZE = {100, 100};
    scale = _scale;
    time = 81;
    rect = sf::IntRect(0, 0, 100, 100);
}

void explosion::update() {
    pos += vel;
    if (time == 0) destroyed = true;
    --time;
    if (rect.left == 800) {
        rect.left = 0;
        rect.top += SIZE.y;
    }
    rect.left += SIZE.x;
}

