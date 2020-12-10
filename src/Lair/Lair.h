#pragma once

#include "SFML/Graphics.hpp"
#include "../Object/Object.h"
#include "../TableOfUnits/TableOfUnits.h"
#include "../../lib/MyContainer/Container.h"

    /**
    * Класс логова колонии
    */
class Lair : public Object {
private:
    bool open_ = false;
    int level_;
    int maxHealth_;
    int health_;
    TableOfUnits *TU;
public:

    //CONSTRUCTORS
    Lair(std::string name, std::string type, std::string color,
         float x, float y, int w, int h, int level, int health);

    /**
    * Уровень логова
    */
    int getLevel() { return this->level_; }

    /**
    * Максимальное здоровье логова
    */
    int getMaxHealth() { return this->maxHealth_; }

    /**
    * Текущее здоровье логова
    */
    int getHealth() { return this->health_; }

    /**
    * Открыта ли таблица создания юнитов
    */
    bool getOpen() { return this->open_; }

    /**
    * Таблица создания юнитов
    */
    TableOfUnits *getTableOfUnits() { return this->TU; }

    /**
    * Изменение уровня
    */
    void setLevel(int level) {
        if(level<0)
            throw std::exception();
        this->level_ = level;
    }

    /**
    * Изменение максимального здоровья
    */
    void setMaxHealth(int maxHealth) {
        if(maxHealth<0)
            throw std::exception();
        this->maxHealth_ = maxHealth; }

    /**
    * Изменение здоровья
    */
    void setHealth(int health) {
        this->health_ = health; }

    /**
    * Открыта ли таблица
    */
    void setOpen(bool flag) { this->open_ = flag; }


    /**
    * Повышение уровня
    */
    void levelUp();

    /**
    * Вырисовка таблицы создания юнитов
    */
    void drawTableOfUnits(sf::RenderWindow *window, sf::Font &font);

    /**
    * Проверяем, нажал ли пользователь в определенную область для создания юнита
     * Возвращает стоимость и созданного солдата
     * @param cleaner возвращает указатель на созданного юнита
     * @param hunter возвращает указатель на созданного юнита
     * @param stormtrooper возвращает указатель на созданного юнита
     * @param usual возвращает указатель на созданного юнита
    */
    container<int> checkTap(float x, float y,
                              Stormtrooper *&stormtrooper,
                              Hunter *&hunter,
                              Usual *&usual,
                              Cleaner *&cleaner);


};