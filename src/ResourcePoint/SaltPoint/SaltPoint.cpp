#include "SaltPoint.h"

SaltPoint::SaltPoint(std::string &name, std::string &type, std::string path, Colony *colony, float x, float y, int width, int height,
                     int health):ResourcePoint(name, type, path, colony, x, y, width, height, health){

}

void SaltPoint::Repopulate(Colony *colony) {
    this->setColony(colony);
    this->color = colony->getColor();
    this->setHealth(this->getMaxHealth());
    colony->setResource(this);
}

void SaltPoint::toIncrease(Colony *colony) {
    colony->setSold(colony->getSold() + this->getIncrease());
}
