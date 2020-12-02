#pragma once
#include "../ResourcePoint.h"
class FoodPoint: public ResourcePoint {
private:
public:
    FoodPoint(std::string &name, std::string &type, std::string path, Colony *colony,
    float x, float y, int width, int height, int health);
    void toIncrease(Colony *colony) override;

    void Repopulate(Colony *colony) override;
};

