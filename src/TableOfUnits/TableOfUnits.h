#pragma once

#include "SFML/Graphics.hpp"
#include "../Unit/Hunter/Hunter.h"
#include "../Unit/Stormtrooper/Stormtrooper.h"
#include "../Unit/Cleaner/Cleaner.h"
#include "../Unit/Usual/Usual.h"
#include "../../lib/MyContainer/Container.h"

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

    void newUnits(int level);

    sf::Texture &getTexture() { return this->texture; }

    sf::Sprite &getSprite() { return this->background; }

    void draw(int level, sf::RenderWindow* window, sf::Font&);

    container<int> getCost(int );

};