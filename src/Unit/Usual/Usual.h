#pragma once

#include"../Unit.h"

/**
* Класс юнита- обычный
*/
class Usual : public Unit {
private:
    int damage_;
    int take_;
public:
    //CONSTRUCTOR
    Usual(int level);

    Usual(std::string name, std::string type, std::string color,
          int x, int y, int w, int h, int level, int health);


    //GETTERS
    /**
    * Получить урон по юнитам
    */
    int getDamage() { return this->damage_; }

    /**
    * Получить урон по нейтральным ресурсным точкам
    */
    int getTake() { return this->take_; }


    //SETTERS
    /**
    * Изменить урон по юнитам
    */
    void setDamage(int damage) {
        if (damage<0)
            throw std::exception();
        this->damage_ = damage; }

    /**
    * Изменить урон по нейтральным ресурсным точкам
    */
    void setTake(int take) {
        if (take<0)
            throw std::exception();
        this->take_ = take; }

    /**
    * Атаковать юнита
    */
    void attackUnit(Unit *U, int a);
};
