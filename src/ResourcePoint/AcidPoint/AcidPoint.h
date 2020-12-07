#pragma once
#include "../ResourcePoint.h"

/**
* Класс кислотной точки
*/
class AcidPoint : public ResourcePoint {
private:
public:
    AcidPoint(std::string &name, std::string &type, std::string path, Colony *colony,
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


