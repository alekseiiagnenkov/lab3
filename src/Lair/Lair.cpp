#include "Lair.h"

Lair::Lair(std::string name, std::string type, std::string color,
           float x, float y, int w, int h, int lvl, int health) : Object(name, type, color, x, y, w, h) {
    this->level_ = lvl;
    this->maxHealth_ = this->level_ * 1000;
    this->health_ = health;
    this->TU = new TableOfUnits;
}

void Lair::drawTableOfUnits(sf::RenderWindow *window, sf::Font &font) {
    this->getTableOfUnits()->draw(this->level_, window, font);
}

container<int> Lair::checkTap(float x, float y,
                                Stormtrooper *&stormtrooper,
                                Hunter *&hunter,
                                Usual *&usual,
                                Cleaner *&cleaner) {
    int a = 0;
    if (x > float(910) && x < float(980)) {
        if (y > float(330) && y < float(410)) {
            std::cout << "Create stormtrooper" << std::endl;
            stormtrooper = new Stormtrooper("stormtrooper", "unit", this->color, this->x + 100,
                                            this->y + 100,
                                            49,
                                            63, this->getLevel(), -1);
            a = 1;
        } else if (y > 430 && y < 510) {
            std::cout << "Create Hunter" << std::endl;
            hunter = new Hunter("hunter", "unit", this->color, this->x + 100, this->y + 100,
                                49,
                                63, this->getLevel(), -1);
            a = 2;
        } else if (y > 530 && y < 610) {
            std::cout << "Create usual" << std::endl;
            usual = new Usual("usual", "unit", this->color, this->x + 100, this->y + 100,
                              49,
                              63, this->getLevel(), -1);
            a = 3;
        } else if (y > 630 && y < 710) {
            std::cout << "Create cleaner" << std::endl;
            cleaner = new Cleaner("cleaner", "unit", this->color, this->x + 100, this->y + 100,
                                  49,
                                  63, this->getLevel(), -1);
            a = 4;
        }
        this->setOpen(false);
    }
    return this->getTableOfUnits()->getCost(a);
}

void Lair::levelUp() {
    setLevel(getLevel() + 1);
    this->maxHealth_ = this->level_ * 1000;
    this->health_ = this->maxHealth_;
}