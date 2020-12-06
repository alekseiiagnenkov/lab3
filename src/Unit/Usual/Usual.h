#pragma once

#include"../Unit.h"

class Usual : public Unit {
private:
    int damage_;
    int take_;
public:
    //CONSTRUCTOR
    Usual(int level);

    Usual(std::string name, std::string type, std::string color,
          int x, int y, int w, int h, int lvl, int health);


    //GETTERS
    int getDamage() { return this->damage_; }

    int getTake() { return this->take_; }


    //SETTERS
    void setDamage(int damage) { this->damage_ = damage; }

    void setTake(int take) { this->take_ = take; }

    void attackUnit(Unit *U, int a);
};
