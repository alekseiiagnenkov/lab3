#pragma once

#include "../Lair/Lair.h"
#include "../Army/Army.h"
#include "../TableOfResource/TableOfResource.h"
#include<vector>
#include <string>

/**
* Класс колония
*/
class Colony {
private:
    std::string color_;
    int acid_;
    int salt_;
    int food_;
    container<Object *> resources_;
    Lair *lair_;
    Army *army_;
    TableOfResource *TR;
public:

    Colony(int acid, int salt, int food, Lair *lair, std::string &color, Army *);


    /**
    * Получаем лового данной колонии
    */
    Lair *getLair() { return this->lair_; }

    /**
    * Кол-во еды
    */
    int getFood() { return this->food_; }

    /**
    * Кол-во кислоты
    */
    int getAcid() { return this->acid_; }

    /**
    * Кол-во соли
    */
    int getSalt() { return this->salt_; }

    /**
    * Захваченные ресурсные точки
    */
    container<Object *> getResources() { return this->resources_; }

    /**
    * Получаем цвет данной колонии
    */
    std::string &getColor() { return this->color_; }

    /**
    * Получаем армию колонии
    */
    Army *getArmy() { return this->army_; }

    /**
    * Ресурсная таблица, чтобы игрок видел кол-во ресурсов
    */
    TableOfResource *getTableOfResource() { return this->TR; }


    //SETTERS
    /**
    * Присваиваем колонии логово
    */
    void setLair(Lair *lair) { this->lair_ = lair; }

    /**
    * Изменяем кол-во еды
    */
    void setFood(int food) {
        if (food < 0)
            throw std::exception();
        this->food_ = food;
    }

    /**
    * Изменяем кол-во кислоты
    */
    void setAcid(int acid) {
        if (acid < 0)
            throw std::exception();
        this->acid_ = acid;
    }

    /**
    * Изменяем кол-во соли
    */
    void setSalt(int salt) {
        if(salt<0)
            throw std::exception();
        this->salt_ = salt; }

    /**
    * Присваиваем армию, нужно при создании, когда мы загружаем юнитов
    */
    void setArmy(Army *army) { this->army_ = army; }

    /**
    * Добавляем захваченный ресурс
    */
    void setResource(Object *resource) { this->resources_.push_back(resource); }

    //FUNCTION

    /**
    * Вырисовываем таблицу ресурсов
    * @param font шрифт вывода
    */
    void drawTableOfResource(sf::RenderWindow *window, sf::Font &font);

    /**
    * Проверяем, можем ли мы потратить данное кол-во ресурсов
     * @param waste массив ресурсов, необходимых, чтобы создать юнита
    */
    bool wasteResources(container<int> waste);
};
