#include "Cell.h"

Cell::Cell(int x, int y, Object *object, int ID) {
    this->x_ = x;
    this->y_ = y;
    if (ID == 9)
        this->type_ = "solid";
    else
        this->type_ = "free";
    if (object != nullptr)
        this->objects_.push_back(object);
}

void Cell::deleteObject(Object *object) {
    for (int i = 0; i < this->objects_.size(); i++)
        if (this->objects_[i] == object) {
            auto begin = this->objects_.cbegin();
            this->objects_.erase(i + begin);
        }
}

void Cell::deleteLastObject() {
    this->objects_.pop_back();
}
