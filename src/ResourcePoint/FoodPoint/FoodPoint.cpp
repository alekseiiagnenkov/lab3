#include "FoodPoint.h"

FoodPoint::FoodPoint(std::string &name, std::string &type, std::string path, Colony *colony, float x, float y, int width, int height,
                     int health):ResourcePoint(name, type, path, colony, x, y, width, height, health){

}

void FoodPoint::toIncrease(Colony *colony) {
    colony->setFood(colony->getFood() + this->getIncrease());
}

void FoodPoint::Repopulate(Colony *colony) {
    this->toIncrease(colony);
    this->setHealth(this->getMaxHealth());
    this->moveX=rand()%3200;
    this->moveY=rand()%3200;
}

