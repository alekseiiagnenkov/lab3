#include "AcidPoint.h"

AcidPoint::AcidPoint(std::string &name, std::string &type, std::string path, Colony *colony, float x, float y, int width, int height,
                     int health):ResourcePoint(name, type, path, colony, x, y, width, height, health){

}

void AcidPoint::Repopulate(Colony *colony) {
    this->setColony(colony);
    this->color = colony->getColor();
    this->setHealth(this->getMaxHealth());
    colony->setResource(this);
}

void AcidPoint::toIncrease(Colony *colony) {
    colony->setAcid(colony->getAcid() + this->getIncrease());
}
