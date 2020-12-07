#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <cmath>

/**
 * Класс объекта. Все классы, имеющие картинку являются подклассами данного класса
 * В картах TMX объект - это область на карте, имеющая имя, тип,
 *  границы, набор пользовательских свойств (в формате ключ-значение)
 *  и текстурные координаты.
 * Текстурные координаты позволяют связать с объектом спрайт,
 *  использующий основную текстуру карты как источник данных.
 */
class Object {
public:
    float x, y;
    float moveX, moveY;
    int width, height;
    std::string color;
    std::string name;//имя
    std::string type;//тип
    sf::Texture texture;
    sf::Sprite sprite;//картинка
    std::map<std::string, std::string> properties;//свойства

    Object(){}

    Object(std::string &name, std::string &type, std::string&  color, float x, float y, int width, int height);

    /**
    * Рисуем объект
    */
    void draw(sf::RenderWindow &window);

    /**
    * Обновляем положение объекта
    */
    void updateMove();

    /**
    * Текущие координаты объекта
    */
    sf::Vector2f getCoord();

};