#include "Colony.h"

Colony::Colony(int acid, int salt, int food, Lair *lair, std::string &color, Army *army) {
    this->acid_ = acid;
    this->food_ = food;
    this->salt_ = salt;
    this->lair_ = lair;
    this->army_ = army;
    this->color_ = color;
    this->TR = new TableOfResource;
}

void Colony::drawTableOfResource(sf::RenderWindow *window, sf::Font &font) {
    this->getTableOfResource()->draw(this->salt_, this->acid_, this->food_, this->getArmy()->size(), window,
                                     font);
}

bool Colony::wasteResources(container<int> waste) {
    if (!((this->salt_ - waste[0]) < 0 || (this->acid_ - waste[1]) < 0 || (this->food_ - waste[2]) < 0)) {
        this->salt_ -= waste[0];
        this->acid_ -= waste[1];
        this->food_ -= waste[2];
        return true;
    } else
        return false;
}