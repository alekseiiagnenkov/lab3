#pragma once

#include "../Object/Object.h"

/**
 * Класс клетки поля.
 * Создан для удобной работы с полем, столкновений с лавой, поиска объектов
 */
class Cell {
private:
    std::vector<Object *> objects_;
    std::string type_;
    int x_;
    int y_;
    int const size_ = 32;
public:

    Cell(int x, int y, Object *object, int ID);

    /**
    * Координата Х данной клетки
    */
    int getX() { return this->x_; }

    /**
    * Координата Y данной клетки
    */
    int getY() { return this->y_; }

    /**
    * Размер ячейки
    */
    int getSize() { return this->size_; }

    /**
    * Возвращаем тип ячейки. Может быть твердый(лава) или свободный(пустыня)
    */
    std::string getType() { return this->type_; }

    /**
    * Получаем массив объектов, которые принадлежат данной клетке
    */
    std::vector<Object *>& getObjects() { return this->objects_; }

    /**
    * Присваиваем Y координату
    */
    void setX(int x){
        if(x<0)
            throw std::exception();
        this->x_=x;
    }

    /**
    * Присваиваем X координату
    */
    void setY(int y){
        if(y<0)
            throw std::exception();
        this->y_=y;
    }

    /**
    * Присваиваем ячейке объект
    */
    void setObject(Object *object) {
        if (object != nullptr)
            this->objects_.push_back(object);
        if(object->type=="resource"){
            this->type_=object->type;
        }
    }

    /**
    * Удаляем определенный объект из данной ячейки
    */
    void deleteObject(Object *object);
};