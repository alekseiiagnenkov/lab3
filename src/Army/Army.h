#pragma once

#include "../Unit/Cleaner/Cleaner.h"
#include "../Unit/Stormtrooper/Stormtrooper.h"
#include "../Unit/Hunter/Hunter.h"
#include "../Unit/Usual/Usual.h"
#include "../Table/Table.h"
#include "../../lib/MyContainer/Container.h"
#include <vector>

/**
 * Класс армия, в которой хранятся все юниты колонии
 */
class Army {
private:
    container<Stormtrooper *> stormtroopers_;
    container<Usual *> usuals_;
    container<Cleaner *> cleaners_;
    container<Hunter *> hunters_;
public:
    Army() {}

    Army(container<Stormtrooper *> &stormtroopers, container<Usual *> &usuals, container<Hunter *> &hunters,
         container<Cleaner *> &cleaners);
    /**
    * Получить всех штурмовиков колонии
    */
    container<Stormtrooper *> getStormtroopers() { return this->stormtroopers_; }

    /**
    * Получить всех обычных колонии
    */
    container<Usual *> getUsuals() { return this->usuals_; }

    /**
    * Получить всех чистильщиков колонии
    */
    container<Cleaner *> getCleaners() { return this->cleaners_; }

    /**
    * Получить всех охотников колонии
    */
    container<Hunter *> getHunters() { return this->hunters_; }

    /**
     * Перегруженная функция добавки юнита
     */
    void setUnit(Cleaner *cleaner) { this->cleaners_.push_back(cleaner); }

    /**
    * Перегруженная функция добавки юнита
    */
    void setUnit(Stormtrooper *stormtrooper) { this->stormtroopers_.push_back(stormtrooper); }

    /**
     * Перегруженная функция добавки юнита
     */
    void setUnit(Usual *usual) { this->usuals_.push_back(usual); }

    /**
     * Перегруженная функция добавки юнита
     */
    void setUnit(Hunter *hunter) { this->hunters_.push_back(hunter); }

    /**
     * Поиск юнита в данном классе
     */
     Unit *findUnit(Object *O);

    /**
     * Проверка здоровья всех юнитов
     * @param T если вдруг здоровье <0, то удаляем объект из таблицы
     */
    void checkUnitsHealth(Table *T);

    /**
     * Размер армии
     */
    int size();

};
