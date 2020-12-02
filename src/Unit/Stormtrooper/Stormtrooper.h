#pragma once

#include"../Unit.h"

class Stormtrooper : public Unit {
private:
    int damage_;
    int take_;
public:
    //CONSTRUCTORS
    Stormtrooper (int level);
    Stormtrooper(std::string name, std::string type, std::string  color,
                 int x, int y, int w, int h, int lvl, int health);


    //GETTERS
    int getDamage() { return this->damage_; }

    int getTake() { return this->take_; }

    //SETTERS
    void setDamage(int damage) { this->damage_ = damage; }

    void setTake(int take) { this->take_ = take; }

    void attackUnit(Unit* U, int a);

    //void attackLair(Lair* L) { U->setHealth(U->getHealth() - this->damage_);}
};