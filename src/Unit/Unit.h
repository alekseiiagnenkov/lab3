#pragma once

#include "../Object/Object.h"
#include <string>

/**
     * Класс юнита, обобщающих их всех
     */
class Unit: public Object {
private:
    std::string name_="";
    int level_;
    int maxHealth_;
    int health_;
    bool state_; //0-свободен, 1- занят
    int intake_;
    float dodge_;

public:

    //CONSTRUCTORS
    Unit(){}
    Unit(std::string &name, std::string &type, std::string& color,
         int x, int y, int width, int height, int lvl, int health); //level берется из уровня логова


    //GETTERS
    /**
     * Получить макс здоровье
     */
    int getMaxHealth() { return this->maxHealth_; }

    /**
     * Получить текущее здоровье
     */
    int getHealth() { return this->health_; }

    /**
     * Получить состояние юнита(занят/нет)
     */
    bool getState() { return this->state_; }

    /**
     * Получить вероятность увернуться
     */
    double getDodge() { return this->dodge_; }

    /**
     * Получить уровень
     */
    int getLevel() { return this->level_; }

    /**
     * Получить урон по ресурсным точкам
     */
    int getIntake() { return this->intake_; }

    /**
     * Получить название
     */
    std::string getName() { return this->name_; }


    //SETTERS
    /**
     * Изменить макс здоровье
     */
    void setMaxHealth(int maxHealth) { this->maxHealth_ = maxHealth; }

    /**
     * Изменить текущее здоровье
     */
    void setHealth(int health) { this->health_ = health; }

    /**
     * Изменить состояние
     */
    void setState(bool state) { this->state_ = state; }

    /**
     * Изменить вероятность увернуться
     */
    void setDodge(double dodge) { this->dodge_ = dodge; }

    /**
     * Изменить урон по ресурсным точкам
     */
    void setIntake(int intake) { this->intake_ = intake; }

    /**
     * Изменить уровень
     */
    void setLevel(int level) { this->level_ = level; }

    /**
     * Изменить название
     */
    void setName(std::string& name) { this->name_ = name; }
};

