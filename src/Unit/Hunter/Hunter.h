#pragma once

#include"../Unit.h"

class Hunter : public Unit {
private:
    int damage_;
public:
    //CONSTRUCTORS
    Hunter (int level);
    Hunter(std::string name, std::string type, std::string  color,
           int x, int y, int w, int h, int lvl, int health);


    //GETTERS
    int getDamage() { return this->damage_; }


    //SETTERS
    void setDamage(int damage) { this->damage_ = damage; }

    void attackUnit(Unit* U, int a);
};
