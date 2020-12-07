#pragma once

#include <SFML/Graphics.hpp>

/**
     * Класс таблицы ресурсов
     */
class TableOfResource {
private:
    sf::Texture texture;
    sf::Sprite background;

public:
    TableOfResource();

    /**
     * Получаем текстуру
     */
    sf::Texture& getTexture() { return this->texture; }

    /**
     * Вырисовываем таблицу с определенным кол-вом ресурсов
     */
    void draw(int salti, int acidi, int foodi, int nomberUnits, sf::RenderWindow* window, sf::Font& font);

    /**
     * Получаем спрайт
     */
    sf::Sprite& getSprite() { return this->background; }
};
