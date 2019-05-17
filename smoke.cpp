#include "smoke.h"


smoke::smoke(sf::Vector2f _pos, sf::Vector2f _facing) {
    type = SMOKE;
    pos = _pos;
    facing = _facing;
    time = 100;
    scale = {0.02, 0.02};
    SIZE = {256, 256};
}

void smoke::update() {
    --time;
    if (time == 0) destroyed = true;
}
