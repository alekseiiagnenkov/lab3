#include "Cleaner.h"

Cleaner::Cleaner(std::string name, std::string type, std::string  color,
                 int x, int y, int w, int h, int level, int health) : Unit(name, type, color, x, y, w, h, level, health) {
    if(level<0){
        std::cout << "Cleaner[#6] Invalid level " << std::endl;
        throw std::exception();
    }
    this->take_ = 25 + 5 * level;
    this->setLevel(level);
    this->setIntake(5 + level);
    this->setDodge(0.07 * level);
    this->setMaxHealth(30 * level + 70);
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
