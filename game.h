#pragma once
#include "SFML/Graphics.hpp"


#include "object.h"
#include<vector>
#include "vehicle.h"
#include <memory>

class game {
    public :
        game();
        bool closed;
        sf::Font font;
        sf::Text text;
        sf::Texture bgTexture;
        int width, height;
        std::vector<int> playerKey = {sf::Keyboard::A, sf::Keyboard::L};
        std::vector<int> playerResource = {0, 0};
        std::vector<bool> playerKeyHold = {false, false};
        std::vector<object*> pCarrier;
        std::vector<sf::Texture> texture;
        std::vector<object*> pVehicles;
        std::vector<object*> pOther;
        void drawBG(sf::RenderWindow &window);
        void loadTexture();
        void start();
        void display(sf::RenderWindow &window);
        void drawResource(sf::RenderWindow &window);
        void intro();

};
