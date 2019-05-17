#pragma once
#include<vector>
#include<SFML/System.hpp>
#include<SFML/Graphics.hpp>


enum type {
    CARRIER,
    FIGHTER,
    INTERCEPTOR,
    BOMBER,
    BULLET,
    MISSILE,
    BOMB,
    SPARK,
    EXPLOSION,
};


class object
{
    public:
        bool animated = false;
        sf::IntRect rect;
        int type;
        float turnSpeed;
        float accel;
        int player;
        float hitpoint;
        float collisionRadius;
        bool destroyed = false;
        sf::Vector2f SIZE;
        sf::Vector2f scale;
        sf::Vector2f pos;
        sf::Vector2f vel;
        sf::Vector2f facing;
        double getDirection();
        sf::Vector2f getRealSize();
        sf::Vector2f getRealPos();
        sf::Vector2f getCenter();
        bool onScreen();
        sf::Sprite getSprite(std::vector<sf::Texture>& texture);
        object* getNearest(std::vector<object*> pList, std::vector<int> typeL);
        bool collision(object* other);
        bool dead();
        sf::Color getColor();
        void thrust();
        void turn(float direction);
        void goToward(sf::Vector2f targetPos, bool th = true);
        void goAway(sf::Vector2f targetPos);
        virtual void update();
        virtual void updateAI(std::vector<object*>& pList, std::vector<object*>& pOther);
        virtual void updateGame(std::vector<object*>& pList, std::vector<object*>& pOther);
        virtual void createVehicle(std::vector<object*>& pList, int resource);
};

