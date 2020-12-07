#pragma once

#include "../Colony/Colony.h"

#include "../Unit/Hunter/Hunter.h"
#include "../Unit/Cleaner/Cleaner.h"
#include "../Unit/Stormtrooper/Stormtrooper.h"
#include "../Unit/Usual/Usual.h"

#include "../ResourcePoint/SaltPoint/SaltPoint.h"
#include "../ResourcePoint/FoodPoint/FoodPoint.h"
#include "../ResourcePoint/AcidPoint/AcidPoint.h"

#include "../Table/Table.h"
#include "../Object/Object.h"

#include "../../lib/tinyxml2/tinyxml2.h"
#include <SFML/Graphics.hpp>
#include "../../lib/MyContainer/Container.h"
#include <iostream>

/**
 * Слой карты
 * В картах TMX слой - это набор тайлов (спрайтов),
 * из которых складывается ландшафт карты.
 * Слоёв может быть несколько, что позволяет нарисовать,
 * например, слой травы поверх слоя земли.
 */
class Layer {
public:
    sf::Uint8 opacity = 0;
    std::vector<sf::Sprite> tiles;
};

/**
 * Сама карта. Может состоять из слоев
 */
class Level {
private:
    int tileHeight_, tileWidth_, firstTileID_, height_, width_;
    sf::Texture tileSetImage_;
    std::vector<Layer> layers_;
public:
    Table *T;

    container<ResourcePoint *> resources_;
    container<Colony *> colonies_;

    /**
    * Загружает карту по пути
    */
    bool loadMapFromFile(const std::string &filepath);

    /**
    * Загружает по пути объекты на карте: логово, юнитов, ресурсные точки
    */
    bool loadObjectsFromFile(const std::string &filepath);

    /**
    * Длина тайла
    */
    float getTileMapWidth();

    /**
    * Высота тайла
    */
    float getTileMapHeight();

    /**
    * рисует все слои тайлов один за другим,
    *  но не рисует объекты (рисованием которых должна заниматься игра).
    * Принимает любую цель для рисования, например, sf::RenderWindow.
    */
    void draw(sf::RenderTarget &target);
};
