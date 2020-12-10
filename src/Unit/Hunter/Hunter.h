#pragma once

#include"../Unit.h"

/**
* Класс юнита- охотник
*/
class Hunter : public Unit {
private:
    int damage_;
public:
    //CONSTRUCTORS
    Hunter (int level);
    Hunter(std::string name, std::string type, std::string  color,
           int x, int y, int w, int h, int level, int health);


    //GETTERS
    /**
    * Получить урон по юнитам
    */
    int getDamage() { return this->damage_; }


    //SETTERS
    /**
    * Изменить урон
    */
    void setDamage(int damage) {
        if (damage<0)
            throw std::exception();
        this->damage_ = damage; }

    /**
    * Атаковать юнита
    */
    void attackUnit(Unit* U, int a);
};
