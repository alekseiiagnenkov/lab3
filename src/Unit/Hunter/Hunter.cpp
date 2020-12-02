#include "Hunter.h"

Hunter::Hunter(std::string name, std::string type, std::string  color,
               int x, int y, int w, int h, int lvl, int health) : Unit(name, type, color, x, y, w, h, lvl, health) {
    this->damage_=20 + 4 * lvl;
    this->setLevel(lvl);
    this->setIntake(5 + lvl);
    this->setDodge(0.07 * lvl);
    this->setMaxHealth(30 * lvl + 70);
    if(health==-1)
        this->setHealth((this->getMaxHealth()));
    else
        this->setHealth(health);
}

Hunter::Hunter(int lvl) {
    this->damage_=20 + 4 * lvl;
    this->setLevel(lvl);
    this->setIntake(5 + lvl);
    this->setDodge(0.07 * lvl);
    this->setMaxHealth(30 * lvl + 70);
    this->setHealth((this->getMaxHealth()));
}

void Hunter::attackUnit(Unit *U, int a) {
    srand(a);
    if (U != nullptr) {
        if ((float((rand() % 100)) / 100)>= U->getDodge()){
            std::cout << "attack---> " << U->color << std::endl << std::endl;
            U->setHealth(U->getHealth() - this->damage_);
        }
        else {
            std::cout << "dodge " << U->color << std::endl << std::endl;
        }
    }
}
