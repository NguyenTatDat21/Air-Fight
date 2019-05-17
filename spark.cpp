#include "spark.h"


spark::spark(sf::Vector2f _pos, sf::Vector2f _facing) {
    pos = _pos;
    type = SPARK;
    facing = _facing;
    vel = -facing;
    SIZE = {829, 964};
    scale = {0.03, 0.02};
    time = 5;
}

void spark::update() {
    pos += vel;
    if (time == 0) destroyed = true;
    --time;
}
