#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>


// В картах TMX объект - это область на карте, имеющая имя, тип,
//  границы, набор пользовательских свойств (в формате ключ-значение)
//  и текстурные координаты.
// Текстурные координаты позволяют связать с объектом спрайт,
//  использующий основную текстуру карты как источник данных.
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

    void draw(sf::RenderWindow &window);

    void updateMove();

    sf::Vector2i getCoord();

};