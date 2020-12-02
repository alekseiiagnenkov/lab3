#include "Cleaner.h"

Cleaner::Cleaner(std::string name, std::string type,std::string  color,
                 int x, int y, int w, int h, int lvl, int health) : Unit(name, type, color, x, y, w, h, lvl, health) {
    this->take_ = 25 + 5 * lvl;
    this->setLevel(lvl);
    this->setIntake(5 + lvl);
    this->setDodge(0.07 * lvl);
    this->setMaxHealth(30 * lvl + 70);
    if(health==-1)
        this->setHealth((this->getMaxHealth()));
    else
        this->setHealth(health);
}

Cleaner::Cleaner(int lvl) {

    this->take_ = 25 + 5 * lvl;
    this->setLevel(lvl);
    this->setIntake(5 + lvl);
    this->setDodge(0.07 * lvl);
    this->setMaxHealth(30 * lvl + 70);
    this->setHealth((this->getMaxHealth()));
}

void Cleaner::attackResource(Object* resource) {

}
