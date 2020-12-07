#pragma once
#include "../ResourcePoint.h"

/**
 * Класс точки еды
 */
class FoodPoint: public ResourcePoint {
private:
public:
    FoodPoint(std::string &name, std::string &type, std::string path, Colony *colony,
    float x, float y, int width, int height, int health);

    /**
    * Добавить ресурсы логову
    */
    void toIncrease(Colony *colony) override;

    /**
    * Изменение положегия на карте
    */
    void Repopulate(Colony *colony) override;
};

