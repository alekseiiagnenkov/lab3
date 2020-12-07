#pragma once

#include"../Unit.h"

/**
* Класс юнита- чистильщик
*/
class Cleaner : public Unit {
private:
    int take_;
public:
    //CONSTRUCTORS
    Cleaner(int level);

    Cleaner(std::string name, std::string type, std::string color,
            int x, int y, int w, int h, int lvl, int health);


    //GETTERS
    /**
    * Получить урон по ресурсам
    */
    int getTake() { return this->take_; }


    //SETTERS
    /**
    * Изменить урон по ресурсам
    */
    void setTake(int take) { this->take_ = take; }
};
