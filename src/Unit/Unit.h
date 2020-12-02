#pragma once

#include "../Object/Object.h"
#include <string>

class Unit: public Object {
private:
    std::string name_="";
    int level_;
    int maxHealth_;
    int health_;
    bool state_; //0-свободен, 1- занят
    int intake_;
    float dodge_;

public:

    //CONSTRUCTORS
    Unit(){}
    Unit(std::string &name, std::string &type, std::string& color,
         int x, int y, int width, int height, int lvl, int health); //level берется из уровня логова


    //GETTERS
    int getMaxHealth() { return this->maxHealth_; }

    int getHealth() { return this->health_; }

    bool getState() { return this->state_; }

    double getDodge() { return this->dodge_; }

    int getLevel() { return this->level_; }

    int getIntake() { return this->intake_; }

    std::string getName() { return this->name_; }


    //SETTERS
    void setMaxHealth(int maxHealth) { this->maxHealth_ = maxHealth; }

    void setHealth(int health) { this->health_ = health; }

    void setState(bool state) { this->state_ = state; }

    void setDodge(double dodge) { this->dodge_ = dodge; }

    void setIntake(int intake) { this->intake_ = intake; }

    void setLevel(int level) { this->level_ = level; }

    void setName(std::string& name) { this->name_ = name; }
};

