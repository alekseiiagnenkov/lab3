#pragma once

#include "SFML/Graphics.hpp"
#include "../Unit/Hunter/Hunter.h"
#include "../Unit/Stormtrooper/Stormtrooper.h"
#include "../Unit/Cleaner/Cleaner.h"
#include "../Unit/Usual/Usual.h"

class TableOfUnits {
private:
    Cleaner* cleaner_;
    std::vector<int> costC_;
    Hunter* hunter_;
    std::vector<int> costH_;
    Usual* usual_;
    std::vector<int> costU_;
    Stormtrooper* stormtrooper_;
    std::vector<int> costS_;
    sf::Texture texture;
    sf::Sprite background;
public:

    TableOfUnits();

    ~TableOfUnits();

    void newUnits(int level);

    sf::Texture &getTexture() { return this->texture; }

    sf::Sprite &getSprite() { return this->background; }

    void draw(int level, sf::RenderWindow* window, sf::Font&);

    std::vector<int> getCost(int );

};