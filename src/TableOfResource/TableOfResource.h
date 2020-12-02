#pragma once

#include <SFML/Graphics.hpp>

class TableOfResource {
private:
    sf::Texture texture;
    sf::Sprite background;

public:
    TableOfResource();

    sf::Texture& getTexture() { return this->texture; }

    void draw(int salti, int acidi, int foodi, int nomberUnits, sf::RenderWindow* window, sf::Font& font);

    sf::Sprite& getSprite() { return this->background; }
};
