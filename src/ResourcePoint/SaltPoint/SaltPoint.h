#pragma once
#include "../ResourcePoint.h"

/**
* Класс точки соли
*/
class SaltPoint : public ResourcePoint {
private:
public:

    SaltPoint(std::string &name, std::string &type, std::string path, Colony *colony,
    float x, float y, int width, int height, int health);

    /**
    * Добавить ресурсы
    */
    void toIncrease(Colony *colony) override;

    /**
    * Изменить принадлежность
    */
    void Repopulate(Colony *colony) override;
};