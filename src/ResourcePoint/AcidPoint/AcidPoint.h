#pragma once
#include "../ResourcePoint.h"

class AcidPoint : public ResourcePoint {
private:
public:
    AcidPoint(std::string &name, std::string &type, std::string path, Colony *colony,
    float x, float y, int width, int height, int health);

    void toIncrease(Colony *colony) override;

    void Repopulate(Colony *colony) override;
};


