#include "Level.h"

using namespace tinyxml2;

// On Windows, backslash '\\' is directory separator in paths
// On UNIX paths separated with slash '/'.
#if defined(_WIN32)
const char DIR_SEPARATOR = '\\';
#else
const char DIR_SEPARATOR = '/';
#endif

// Возвращает пусть родительской директории
std::string getParentDirectory(const std::string &filepath) {
    const size_t slashPos = filepath.find_last_of('/');
    std::string parentDir;
    if (slashPos != std::string::npos) {
        parentDir = filepath.substr(0, slashPos);
    }
    return parentDir;
}

// Объединяет два фрагмента пути, например путь к каталогу и имя файла
std::string joinPaths(const std::string &path, const std::string &subpath) {
    if (path.empty()) {
        return subpath;
    }
    if (subpath.empty()) {
        return path;
    }

    return path + DIR_SEPARATOR + subpath;
}

bool Level::loadMapFromFile(const std::string &filepath) {
    XMLDocument levelFile;
    std::vector<Cell *> cells;
    //container<Cell *> cells;

    // Загружаем файл в память
    if (levelFile.LoadFile(filepath.c_str()) != XML_SUCCESS) {
        throw std::runtime_error("Loading level \"" + filepath + "\" failed.");
    }

    // Ищем map
    XMLElement *map = levelFile.FirstChildElement("map");
    if (map == nullptr) {
        throw std::runtime_error("<map> element not found");
    }

    width_ = std::stoi(map->Attribute("width"));
    height_ = std::stoi(map->Attribute("height"));
    tileWidth_ = std::stoi(map->Attribute("tilewidth"));
    tileHeight_ = std::stoi(map->Attribute("tileheight"));

    // Инфа по тайлы
    XMLElement *tileSetElement = map->FirstChildElement("tileset");
    firstTileID_ = std::stoi(tileSetElement->Attribute("firstgid"));

    // Текстуры тайлов
    XMLElement *image = tileSetElement->FirstChildElement("image");
    const std::string imageFileName = image->Attribute("source");

    sf::Image img;
    if (!img.loadFromFile(joinPaths(getParentDirectory(filepath), imageFileName))) {
        std::cout << "Failed to load tile sheet." << std::endl;
        return false;
    } else {
        std::cout << "Map tiles loaded successfully." << std::endl;
    }

    tileSetImage_.loadFromImage(img);//загружаем текстуры

    //получаем кол-во строк и столбцов в файле с тайлами
    const int columns = int(tileSetImage_.getSize().x / tileWidth_);
    const int rows = int(tileSetImage_.getSize().y / tileHeight_);

    //получаем прямоугольники(квадраты) по одному
    //std::vector<sf::IntRect> subRects;
    container<sf::IntRect> subRects;
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++) {
            sf::IntRect rect;
            rect.top = y * tileHeight_;
            rect.left = x * tileWidth_;
            rect.height = tileHeight_;
            rect.width = tileWidth_;
            subRects.push_back(rect);//Это массив прямоугольников с их координатами
        }
    }

    //////////////////////////считываем карту////////////////////////////////////////////
    ///
    XMLElement *layerElement = map->FirstChildElement("layer");
    int flag = 0;
    while (layerElement) {
        Layer layer;

        layer.opacity = 255;//прозрачность

        // <data> содержит описание всех тайлов
        XMLElement *layerDataElement = layerElement->FirstChildElement("data");
        if (layerDataElement == nullptr) {
            std::cout << "No layer information found." << std::endl;
        }

        // <tile> содержит описание 1 тайла
        XMLElement *tileElement = layerDataElement->FirstChildElement("tile");
        if (tileElement == nullptr) {
            std::cout << "Bad map. No tile information found." << std::endl;
            return false;
        }

        //начальные координаты вывода тайлов
        int x = 0, y = 0;

        while (tileElement) {
            const char *name = tileElement->Attribute("gid");//номер тайла в char

            int tileID;
            if (name != nullptr) {
                tileID = std::stoi(name);//получаем int из строчки(номер тайла)
                const int subRectToUse = tileID - firstTileID_;//получаем индекс тайла

                // Figure out texture rect for each tile.
                if (subRectToUse >= 0) {
                    sf::Sprite sprite;
                    sprite.setTexture(tileSetImage_);//ссылка на файл с текстурами
                    sprite.setTextureRect(subRects[subRectToUse]);
                    sprite.setPosition(float(x * tileWidth_), float(y * tileHeight_));//задаем положение тайла
                    sprite.setColor(sf::Color(255, 255, 255, layer.opacity));

                    layer.tiles.push_back(sprite);
                }
            }
            tileElement = tileElement->NextSiblingElement("tile");


            if (flag == 0)
                cells.push_back(new Cell(x, y, nullptr, tileID));


            //получаем следующие координаты
            x++;
            if (x >= width_) {
                x = 0;
                y++;
                if (y >= height_)
                    y = 0;
            }

        }
        layers_.push_back(layer);
        layerElement = layerElement->NextSiblingElement("layer");//переходим к загрузке следующего слоя
        flag = 1;
    }

    T = new Table(width_, height_, cells);

    return true;
}

bool Level::loadObjectsFromFile(const std::string &filepath) {
    XMLDocument stateFile;
    Lair *lair;
    Colony *colony;

    container<Object> objects;
    // Load XML into in-memory XMLDocument.
    if (stateFile.LoadFile(filepath.c_str()) != XML_SUCCESS) {
        throw std::runtime_error("Loading level \"" + filepath + "\" failed.");
    }

    //std::string imageFileName;

    XMLElement *map = stateFile.FirstChildElement("map"); // загрузил карту объектов


    ///////////////////////////загружаем колонии//////////////////////////////////////////
    XMLElement *group;

    XMLElement *numColonies;
    numColonies = map->FirstChildElement("number");
    int numberColonies = std::stoi(numColonies->Attribute("number"));


    // Если есть слои объектов
    if (map->FirstChildElement("group") != nullptr) {
        group = map->FirstChildElement("group");

        // идём по слоям объектов
        while (group) {

            std::string property = group->Attribute("property");

            ///считываем ресурсы колонии
            XMLElement *resources;
            resources = group->FirstChildElement("resource");
            int acid, salt, food;
            if (resources) {
                acid = std::stoi(resources->Attribute("acid"));
                salt = std::stoi(resources->Attribute("salt"));
                food = std::stoi(resources->Attribute("food"));
            }

            //Массив солдат
            container<Unit *> army;

            container<Cleaner*> cleaners;
            container<Stormtrooper*> stormtroopers;
            container<Usual*> usuals;
            container<Hunter*> hunters;

            // Контейнер <object>
            XMLElement *element;
            element = group->FirstChildElement("object");

            while (element) {
                // Получаем все данные - тип, подтип, имя, позиция
                std::string type;
                if (element->Attribute("type") != nullptr) {
                    type = element->Attribute("type");
                }

                std::string name;
                if (element->Attribute("name") != nullptr) {
                    name = element->Attribute("name");
                }


                //координаты вывода
                float x = std::stof(element->Attribute("x"));
                float y = std::stof(element->Attribute("y"));

                int width = std::stoi(element->Attribute("width"));
                int height = std::stoi(element->Attribute("height"));

                // Экземпляр объект
                Object object;

                // "Переменные" объекта (характеристики)
                XMLElement *properties;
                properties = element->FirstChildElement("properties");
                if (properties != nullptr) {
                    XMLElement *prop;
                    prop = properties->FirstChildElement("property");
                    if (prop != nullptr) {
                        while (prop) {
                            std::string propertyName = prop->Attribute("name");
                            std::string propertyValue = prop->Attribute("value");
                            object.properties[propertyName] = propertyValue;
                            prop = prop->NextSiblingElement("property");
                        }
                    }
                }

                if (property == "red" || property == "green") {
                    if (type == "lair") {
                        lair = new Lair(name, type, property, x, y, width, height,
                                        std::stoi(object.properties["level"]),
                                        std::stoi(object.properties["health"]));
                        T->pushObject(lair);
                    } else if (type == "unit") {
                        if (name == "hunter") {
                            hunters.push_back(new Hunter(name, type, property, x, y, width, height,
                                                         std::stoi(object.properties["level"]),
                                                         std::stoi(object.properties["health"])));
                            T->pushObject(hunters[hunters.size() - 1]);
                        } else if (name == "usual") {
                            usuals.push_back(new Usual(name, type, property, x, y, width, height,
                                                       std::stoi(object.properties["level"]),
                                                       std::stoi(object.properties["health"])));
                            T->pushObject(usuals[usuals.size() - 1]);
                        } else if (name == "stormtrooper") {
                            stormtroopers.push_back(new Stormtrooper(name, type, property, x, y, width, height,
                                                                     std::stoi(object.properties["level"]),
                                                                     std::stoi(object.properties["health"])));
                            T->pushObject(stormtroopers[stormtroopers.size() - 1]);
                        } else if (name == "cleaner") {
                            cleaners.push_back(new Cleaner(name, type, property, x, y, width, height,
                                                           std::stoi(object.properties["level"]),
                                                           std::stoi(object.properties["health"])));
                            T->pushObject(cleaners[cleaners.size() - 1]);
                        }
                    }
                } else if (property == "resource") {
                    int nomColony = std::stoi(object.properties["colony"]);
                    if (nomColony == -1) {
                        colony = nullptr;
                    }
                    else {
                        colony = this->colonies_[nomColony];
                    }
                    if (name == "acid") {
                        resources_.push_back(new AcidPoint(name, type, type, colony, x, y, width, height,
                                                           std::stoi(object.properties["health"])));
                    } else if (name == "salt") {
                        resources_.push_back(new SaltPoint(name, type, type, colony, x, y, width, height,
                                                           std::stoi(object.properties["health"])));
                    } else if (name == "food") {
                        resources_.push_back(new FoodPoint(name, type, type, colony, x, y, width, height,
                                                           std::stoi(object.properties["health"])));
                    }
                    T->pushObject(resources_[resources_.size() - 1]);
                }
                element = element->NextSiblingElement("object");
            }

            group = group->NextSiblingElement("group");
            if (numberColonies > 0) {
                colonies_.push_back(
                        new Colony(acid, salt, food, lair, property, new Army(stormtroopers,usuals,hunters,cleaners)));
            }
            numberColonies--;
        }
    } else {
        std::cout << "No item & unit & resources layers found..." << std::endl;
        return false;
    }
    return true;
}

float Level::getTileMapWidth() {
    return (tileWidth_ * width_);
}

float Level::getTileMapHeight() {
    return (tileHeight_ * height_);
}

void Level::draw(sf::RenderTarget &target) {
    const sf::FloatRect viewportRect = target.getView().getViewport();

    // draw all tiles (and don't draw objects)
    for (const auto &layer : layers_) {
        for (const auto &tile : layer.tiles) {
            if (viewportRect.intersects(tile.getLocalBounds())) {
                target.draw(tile);
            }
        }
    }
    for (const auto &layer : layers_) {
        for (const auto &tile : layer.tiles) {
            if (viewportRect.intersects(tile.getLocalBounds())) {
                target.draw(tile);
            }
        }
    }
}

