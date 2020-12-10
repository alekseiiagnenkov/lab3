#pragma once

#include "../Colony/Colony.h"
#include <string>

/**
 * Класс, обобщающий все ресурсы
 */
class ResourcePoint : public Object {
private:
    std::string name_;
    Colony *colony_;
    int maxHealth_;
    int health_;
    int increase_;

public:
    //CONSTRUCTORS
    ResourcePoint(std::string &name, std::string &type, std::string &path, Colony *colony,
                  float x, float y, int width, int height, int health); //level берется из уровня логова

    //GETTERS
    /**
    * Максимальное здоровье
    */
    int getMaxHealth() { return this->maxHealth_; }

    /**
    * Текущее здоровье
    */
    int getHealth() { return this->health_; }

    /**
    * Сколько добавляет
    */
    int getIncrease() { return this->increase_; }

    /**
    * Название ресурса
    */
    std::string getName() { return this->name_; }

    /**
    * Какой колонии принадлежит
    */
    Colony *getColony() { return this->colony_; }

    //SETTERS
    /**
    * Изменить максимальное здоровье
    */
    void setMaxHealth(int maxHealth) {
        if (maxHealth < 0)
            throw std::exception();
        this->maxHealth_ = maxHealth;
    }

    /**
    * Изменить текущее здоровье
    */
    void setHealth(int health) {this->health_ = health;}

    /**
    * Изменить сколько добавляет
    */
    void setIncrease(int increase) {
        if(increase<0)
            throw std::exception();
        this->increase_ = increase; }

    /**
    * Изменить имя
    */
    void setName(std::string &name) { this->name_ = name; }

    /**
    * Присвоить ресурс какой либо колонии
    */
    void setColony(Colony *colony) { this->colony_ = colony; }


    //FUNCTIONS
    /**
    * Получить урон
     * @param colony если хп стало <0, то присваиваем его колонии
    */
    void takeDamage(int damage, Colony *colony);

    /**
     * Виртуальная функция
    * Изменение принадлежности колонии
    */
    virtual void Repopulate(Colony *colony) = 0;

    /**
     * Виртуальная функция
    * Добавить ресурс определенной колонии
    */
    virtual void toIncrease(Colony *colony) = 0;
};
