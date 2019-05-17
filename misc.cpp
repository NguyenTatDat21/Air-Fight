#include "misc.h"
#include<cmath>
#include<iostream>

sf::Vector2f rotate(sf::Vector2f v1, double angle) {
    double cosF = cos(angle * PI / 180);
    double sinF = sin(angle * PI / 180);
    sf::Vector2f v2(v1.x * cosF - v1.y * sinF, v1.x * sinF + v1.y * cosF);
    return v2;
}



sf::Vector2f mul(sf::Vector2f v1, sf:: Vector2f v2) {
    return sf::Vector2f(v1.x * v2.x, v1.y * v2.y);
}


float sqrDist(sf::Vector2f v1, sf::Vector2f v2) {
    sf::Vector2f v3 = v2 - v1;
    return v3.x * v3.x + v3.y * v3.y;
}


float cross(sf::Vector2f v1, sf::Vector2f v2) {
    return v1.x * v2.y - v1.y * v2.x;
}


float dot(sf::Vector2f v1, sf::Vector2f v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

sf::Vector2f norm(sf::Vector2f v) {
    float dist = sqrDist(v, sf::Vector2f(0, 0));
    return v / (float) sqrt(dist);
}
