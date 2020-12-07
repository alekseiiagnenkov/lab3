#pragma once

#include"../Unit.h"

/**
* Класс юнита- штурмовик
*/
class Stormtrooper : public Unit {
private:
    int damage_;
public:
    //CONSTRUCTORS
    Stormtrooper(int level);

    Stormtrooper(std::string name, std::string type, std::string color,
                 int x, int y, int w, int h, int lvl, int health);


    //GETTERS
    /**
    * Получить урон юнитам и логовам
    */
    int getDamage() { return this->damage_; }

    //SETTERS
    /**
    * Изменить урон
    */
    void setDamage(int damage) { this->damage_ = damage; }

    /**
    * Атаковать юнита
    */
    void attackUnit(Unit *U, int a);
};