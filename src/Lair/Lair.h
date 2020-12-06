#pragma once

#include "SFML/Graphics.hpp"
#include "../Object/Object.h"
#include "../TableOfUnits/TableOfUnits.h"
#include "../../lib/MyContainer/Container.h"


class Lair : public Object {
private:
    bool open_ = false;
    int level_;
    int maxHealth_;
    int health_;
    TableOfUnits *TU;
public:

    //CONSTRUCTORS
    Lair(std::string name, std::string type, std::string color,
         float x, float y, int w, int h, int lvl, int health);


    //GETTERS
    int getLevel() { return this->level_; }

    int getMaxHealth() { return this->maxHealth_; }

    int getHealth() { return this->health_; }

    bool getOpen() { return this->open_; }

    TableOfUnits *getTableOfUnits() { return this->TU; }

    //SETTERS
    void setLevel(int level) { this->level_ = level; }

    void setMaxHealth(int maxHealth) { this->maxHealth_ = maxHealth; }

    void setHealth(int health) { this->health_ = health; }

    void setOpen(bool b) { this->open_ = b; }

    //FUNCTION
    void levelUp() { setLevel(getLevel() + 1); }

    void drawTableOfUnits(sf::RenderWindow *window, sf::Font &font);

    container<int> checkTap(float x, float y,
                              Stormtrooper *&stormtrooper,
                              Hunter *&hunter,
                              Usual *&usual,
                              Cleaner *&cleaner);


};