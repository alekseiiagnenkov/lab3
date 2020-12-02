#pragma once
#include"../Unit.h"


class Cleaner: public Unit {
private:
    int take_;
public:
    //CONSTRUCTORS
    Cleaner (int level);
    Cleaner(std::string name, std::string type, std::string  color,
            int x, int y, int w, int h, int lvl, int health);


    //GETTERS
    int getTake() { return this->take_; }


    //SETTERS
    void setTake(int take) { this->take_ = take; }

    void attackResource(Object* resource);
};
