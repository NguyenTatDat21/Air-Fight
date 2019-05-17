#pragma once
#include "object.h"


class vehicle: public object {
    public :
        virtual void update();
        virtual void updateAI(std::vector<object*>& pList, std::vector<object*>& pOther);
};
