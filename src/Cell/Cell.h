#pragma once

#include "../Object/Object.h"
//#include "../../lib/MyContainer/Container.h"

class Cell {
private:
    std::vector<Object *> objects_;
    std::string type_;
    int x_;
    int y_;
    int size_ = 32;
public:
    //CONSTRUCTORS
    Cell(int x, int y, Object *object, int type);

    //Cell(int x, int y, std::vector<Object *> objects, int type);

    //GETTERS
    //Object *getObject() { return this->object_; }

    int getX() { return this->x_; }

    int getY() { return this->y_; }

    int getSize() { return this->size_; }

    std::string getType() { return this->type_; }

    std::vector<Object *>& getObjects() { return this->objects_; }


    //SETTERS
    void setObject(Object *object) {
        if (object != nullptr)
            this->objects_.push_back(object);
        if(object->type=="resource"){
            this->type_=object->type;
        }
    }

//    void setObjects(std::vector<Object *>& objects) {
//        this->objects_ = objects;
//    }

    void deleteObject(Object *object);

    void deleteLastObject();

};