#include "ResourcePoint.h"

ResourcePoint::ResourcePoint(std::string &name, std::string &type, std::string& path, Colony *colony,
                             float x, float y, int width, int height, int health) : Object(name, type, path, x, y, width, height) {
    this->name_ = name;
    this->increase_ = 50;
    this->maxHealth_ = 500;
    if (health == -1) {
        this->health_ = this->maxHealth_;
    }
    else {
        this->health_ = health;
    }
    this->colony_ = colony;
}

void ResourcePoint::takeDamage(int damage, Colony *colony) {
    this->health_ = this->health_ - damage;
    if (this->health_ <= 0) {
        this->Repopulate(colony);
    }
}

