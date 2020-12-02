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

std::vector<int> Lair::checkTap(float x, float y, float centerX, float centerY,
                                Stormtrooper *&stormtrooper,
                                Hunter *&hunter,
                                Usual *&usual,
                                Cleaner *&cleaner) {
    int a = 0;
    if (x > float(425 + centerX) && x < float(525 + centerX)) {
        if (y > float(centerY) - 169 && y < float(centerY) - 86) {
            std::cout << "Create stormtrooper" << std::endl;
            stormtrooper = new Stormtrooper("stormtrooper", "unit", this->color, this->x + 100,
                                            this->y + 100,
                                            49,
                                            63, this->getLevel(), -1);
            a = 1;
        } else if (y > centerY - 70 && y < centerY + 13) {
            std::cout << "Create Hunter" << std::endl;
            hunter = new Hunter("hunter", "unit", this->color, this->x + 100, this->y + 100,
                                49,
                                63, this->getLevel(), -1);
            a = 2;
        } else if (y > centerY + 29 && y < centerY + 112) {
            std::cout << "Create usual" << std::endl;
            usual = new Usual("usual", "unit", this->color, this->x + 100, this->y + 100,
                              49,
                              63, this->getLevel(), -1);
            a = 3;
        } else if (y > centerY + 128 && y < centerY + 211) {
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