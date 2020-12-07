#pragma once

#include <iostream>
#include <vector>
#include "../Cell/Cell.h"
#include "../../lib/MyContainer/Container.h"

int index(float x, float y, int width);


class Table {
private:
    int width_;
    int height_;
    std::vector<Cell *> cells_;
public:
    //CONSTRUCTORS
    Table(int width, int height, std::vector<Cell *> &cells );


    //GETTERS
    int getWidth() { return this->width_; }

    int getHeight() { return this->height_; }

    std::vector<Cell *> getCells() { return this->cells_; }


    //SETTERS
    void setWidth(int width) { this->width_ = width; }

    void setHeight(int height) { this->height_ = height; }

    void setField(std::vector<Cell *> &field) { this->cells_ = field; }


    //FUNCTION
    Cell *getCell(float x, float y) {
        int ind=index(x,y, width_);
        return this->cells_[ind]; }

    Cell *getCell(sf::Vector2f vector) { return this->cells_[index(vector.x, vector.y, width_)]; }

    container<Object *> getObjects(float x, float y, int width, int height, std::string& color);

    void pushObject(Object *object);

    void update(const std::string& color, sf::RenderWindow *);

    container<Cell *> getCellsObject(Object *object);

    container<Cell *> getNearObjects(Object *object);

    container<Cell *> getSolidCells(Object *object);

    void deleteObject(Object*);
};

