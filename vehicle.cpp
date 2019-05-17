#include "vehicle.h"

#include "SFML/System.hpp"
#include "misc.h"



void vehicle::update() {
    vel *= (float) 0.97;
    pos += vel;
}


void vehicle::updateAI(std::vector<object*>& pList, std::vector<object*>& pOther) {

}

