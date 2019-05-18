#pragma once
#include "SFML/System.hpp"
#define PI 3.14159265
#define SCREEN_W (float) 1920
#define SCREEN_H (float) 1080
#define NULL nullptr

sf::Vector2f rotate(sf::Vector2f v1, double angle);

sf::Vector2f mul(sf::Vector2f v1, sf:: Vector2f v2);

float sqrDist(sf::Vector2f v1, sf::Vector2f v2);

float cross(sf::Vector2f v1, sf::Vector2f v2);

float dot(sf::Vector2f v1, sf::Vector2f v2);

sf::Vector2f norm(sf::Vector2f v);
