#include "Cell.h"

Cell::Cell(int x, int y, Object *object, int ID) {
    if( ID<0 || x<0 || y<0){
        std::cout<<"Cell[#5] Invalid param"<<std::endl;
        throw std::exception();
    }
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
