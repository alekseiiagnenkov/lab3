#pragma once

#include <iostream>
#include <vector>
#include "../Cell/Cell.h"

int index(int x, int y, int width);


class Table {
private:
    int width_;
    int height_;
    std::vector<Cell *> cells_;
public:
    //CONSTRUCTORS
    Table(int width, int height, std::vector<Cell *> &cells);


    //GETTERS
    int getWidth() { return this->width_; }

    int getHeight() { return this->height_; }

    std::vector<Cell *> getCells() { return this->cells_; }


    //SETTERS
    void setWidth(int width) { this->width_ = width; }

    void setHeight(int height) { this->height_ = height; }

    void setField(std::vector<Cell *> &field) { this->cells_ = field; }


    //FUNCTION
    Cell *getCell(float x, float y) { return this->cells_[index(int(x), int(y), width_)]; }

    Cell *getCell(sf::Vector2i vector) { return this->cells_[index(vector.x, vector.y, width_)]; }

    std::vector<Object *> getObjects(int x, int y, int width, int height, std::string& color);

    void pushObject(Object *object);

    void update();

    std::vector<Cell *> getCellsObject(Object *object);

    std::vector<Cell *> getNearObjects(Object *object);

    std::vector<Cell *> getSolidCells(Object *object);

    void deleteObject(Object*);
};

