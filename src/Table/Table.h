#pragma once

#include <iostream>
#include <vector>
#include "../Cell/Cell.h"
#include "../../lib/MyContainer/Container.h"

int index(float x, float y, int width);

/**
 * Класс таблица клеток
 */
class Table {
private:
    int width_;
    int height_;
    std::vector<Cell *> cells_;
public:
    //CONSTRUCTORS
    Table(int width, int height, std::vector<Cell *> &cells);


    //GETTERS
    /**
     * Длинна поля в клетках
     */
    int getWidth() { return this->width_; }

    /**
     * Длинна поля в клетках
     */
    int getHeight() { return this->height_; }

    /**
     * Вектор ячеек
     */
    std::vector<Cell *> getCells() { return this->cells_; }


    //SETTERS
    /**
     * Изменить длину поля
     * @param width размер в клетках
     */
    void setWidth(int width) {
        if (width <= 0)
            throw std::exception();
        this->width_ = width;
    }

    /**
     * Изменить высоту поля
     * @param height размер в клетках
     */
    void setHeight(int height) {
        if (height <= 0)
            throw std::exception();
        this->height_ = height;
    }

    /**
     * Изменить массив клеток
     */
    void setField(std::vector<Cell *> &cells) {
        if ((this->width_ * this->height_) != cells.size())
            throw std::exception();
        this->cells_ = cells;
    }


    //FUNCTION
    /**
     * перегружена
     * Получаем клетку по определенных координатам
     */
    Cell *getCell(float x, float y) { return this->cells_[index(x, y, width_)]; }

    /**
     * перегружена
     * Получаем клетку по вектору
     */
    Cell *getCell(sf::Vector2f vector) { return this->cells_[index(vector.x, vector.y, width_)]; }

    /**
     * Получаем объекты в определнной области
     */
    container<Object *> getObjects(float x, float y, int width, int height, std::string &color);

    /**
     * Добавляем объект на поле
     */
    void pushObject(Object *object);

    /**
     * Обновляем положение объектов
     * @param для определение своих и чужих содлат, т.к. ведут они себя по разному
     */
    void update(const std::string &color, sf::RenderWindow *);

    /**
     * Получаем все клетки, которым принадлежит данный объект
     */
    container<Cell *> getCellsObject(Object *object);

    /**
     * Получаем все соседние с объектом объекты
     */
    container<Cell *> getNearObjects(Object *object);

    /**
     * Получаем все клетки твердых обектов, которые находятся радом
     */
    container<Cell *> getSolidCells(Object *object);

    /**
     * Удаляем объект с поля
     */
    void deleteObject(Object *);
};

