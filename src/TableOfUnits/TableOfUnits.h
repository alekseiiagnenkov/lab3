#pragma once

#include "SFML/Graphics.hpp"
#include "../Unit/Hunter/Hunter.h"
#include "../Unit/Stormtrooper/Stormtrooper.h"
#include "../Unit/Cleaner/Cleaner.h"
#include "../Unit/Usual/Usual.h"
#include "../../lib/MyContainer/Container.h"

/**
 * Класс таблицы создания юнитов
 */
class TableOfUnits {
private:
    Cleaner* cleaner_;
    container<int> costC_;
    Hunter* hunter_;
    container<int> costH_;
    Usual* usual_;
    container<int> costU_;
    Stormtrooper* stormtrooper_;
    container<int> costS_;
    sf::Texture texture;
    sf::Sprite background;
public:

    TableOfUnits();

    ~TableOfUnits();

    /**
     * Создаем шаблоны юнитов, чтобы знать какие параметры будут у них при создании
     */
    void newUnits(int level);

    /**
     * Получаем текстуру таблицы
     */
    sf::Texture &getTexture() { return this->texture; }

    /**
     * Получаем спрайт
     */
    sf::Sprite &getSprite() { return this->background; }

    /**
     * Рисуем таблицу с юнитами определнного уровня
     */
    void draw(int level, sf::RenderWindow* window, sf::Font&);

    /**
     * Получаем стоимость определенного юнита
     */
    container<int> getCost(int nomber);

};