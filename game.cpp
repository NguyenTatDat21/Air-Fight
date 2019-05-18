#include "game.h"
#include "SFML/Graphics.hpp"
#include "vehicle.h"
#include "fighter.h"
#include "carrier.h"
#include "misc.h"
#include "iostream"
#include "SFML/System.hpp"
#include<string>

game::game() {
    width = sf::VideoMode::getDesktopMode().width;
    height = sf::VideoMode::getDesktopMode().height;
    closed = false;
}

void game::loadTexture() {

    texture.resize(9);
    texture[CARRIER].loadFromFile("carrier.png");
    texture[FIGHTER].loadFromFile("fighter.png");
    texture[INTERCEPTOR].loadFromFile("interceptor.png");
    texture[BOMBER].loadFromFile("bomber.png");
    texture[BULLET].loadFromFile("bullet.png");
    texture[SPARK].loadFromFile("spark.png");
    texture[BOMB].loadFromFile("bomb.png");
    texture[EXPLOSION].loadFromFile("explosion.png");
    texture[MISSILE].loadFromFile("missile.png");
    bgTexture.loadFromFile("background.png");
    font.loadFromFile("arial.ttf");
    text.setFont(font);
    text.setCharacterSize(40);
}


void game::intro() {
    sf::RenderWindow window(sf::VideoMode(width, height), "Air Fight");
    sf::Texture help;
    help.loadFromFile("help.png");
    sf::Sprite sprite;
    sprite.setTexture(help);
    sprite.setScale(width/SCREEN_W, height/SCREEN_H);
    window.draw(sprite);
    window.display();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed :
                    window.close();
                    closed = true;
                    break;
                case sf::Event::KeyPressed :
                    window.close();
                    start();
                    break;
            }
        }
    }
}


void game::start() {
    loadTexture();
    sf::RenderWindow window(sf::VideoMode(width, height), "Air Fight");
    pVehicles.push_back(new carrier(0, sf::Vector2f(width * 0.36f, height * 0.5f), sf::Vector2f(0, 1)));
    pVehicles.push_back(new carrier(1, sf::Vector2f(width * 0.64f, height * 0.5f), sf::Vector2f(0, -1)));
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed :
                    window.close();
                    break;
                case sf::Event::KeyPressed :
                    for (int i = 0; i < playerKey.size(); ++i) {
                        if (event.key.code == playerKey[i]) {
                            playerKeyHold[i] = true;
                        }
                    }
                    break;
                case sf::Event::KeyReleased :
                    for (int i = 0; i < playerKey.size(); ++i) {
                        if (event.key.code == playerKey[i]) {
                            playerKeyHold[i] = false;
                            pVehicles[i]->createVehicle(pVehicles, playerResource[i]);
                            playerResource[i] = 0;
                        }
                    }
                    break;
            }
        }
        for (int i = 0; i < playerKey.size(); ++i) {
            if (playerKeyHold[i]) {
                ++playerResource[i];
            }
        }

        for (auto p : pOther) {
            p->update();
            p->updateGame(pVehicles, pOther);
        }
        for (auto p : pVehicles) {
            p->updateAI(pVehicles, pOther);
            p->update();
        }
        for (auto it = pVehicles.begin(); it < pVehicles.end(); ++it) {
            if ((*it)->dead()) {
                delete (*it);
                pVehicles.erase(it);
            }
        }
        for (auto it = pOther.begin(); it < pOther.end(); ++it) {
            if (!(*it)->onScreen() || (*it)->destroyed) {
                delete (*it);
                pOther.erase(it);
            }
        }
        while (clock.getElapsedTime() < sf::milliseconds(16)) {

        }
        //std::cerr << clock.getElapsedTime().asMilliseconds() << std::endl;
        clock.restart();
        display(window);
    }

}



void game::display(sf::RenderWindow &window) {
    window.clear();
    sf::Sprite sprite;
    drawBG(window);
    for (auto p : pVehicles) {
        sprite = p->getSprite(texture);
        window.draw(sprite);
    }

    for (auto p : pOther) {
        sprite = p->getSprite(texture);
        window.draw(sprite);
    }
    drawResource(window);

    window.display();

}

void game::drawBG(sf::RenderWindow &window) {
    sf::Sprite sprite;
    sprite.setTexture(bgTexture);
    sprite.setScale(width/1024.f, height/768.f);
    sprite.setColor(sf::Color(255, 255, 255, 150));
    window.draw(sprite);
}


void game::drawResource(sf::RenderWindow& window) {
    text.setString(std::to_string(playerResource[0]/40));
    text.setPosition(10, 0);
    text.setColor(pVehicles[0]->getColor());
    window.draw(text);
    text.setString(std::to_string(playerResource[1]/40));
    text.setPosition(SCREEN_W - 100, 0);
    text.setColor(pVehicles[1]->getColor());
    window.draw(text);
}




