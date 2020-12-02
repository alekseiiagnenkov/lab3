#pragma once

#include "../Colony/Colony.h"
#include <string>


class ResourcePoint: public Object {
private:
    std::string name_;
    Colony *colony_;
    int maxHealth_;
    int health_;
    int increase_;

public:
    //CONSTRUCTORS
    ResourcePoint(std::string &name, std::string &type, std::string &path, Colony* colony,
    float x, float y, int width, int height, int health); //level берется из уровня логова



    //GETTERS
    int getMaxHealth() { return this->maxHealth_; }

    int getHealth() { return this->health_; }

    int getIncrease() { return this->increase_; }

    std::string getName() { return this->name_; }

    Colony *getColony() { return this->colony_; }


    //SETTERS
    void setMaxHealth(int maxHealth) { this->maxHealth_=maxHealth; }

    void setHealth(int health) { this->health_=health; }

    void setIncrease(int increase) { this->increase_=increase; }

    void setName(std::string& name) { this->name_ = name; }

    void setColony(Colony *colony) { this->colony_ = colony; }


    //FUNCTIONS
    void takeDamage(int damage, Colony *colony);

    virtual void Repopulate(Colony *colony) = 0;

    virtual void toIncrease(Colony *colony) = 0;
};
