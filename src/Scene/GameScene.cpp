#include "GameScene.h"

// Абсолютная скорость движения наблюдателя.
static const float WATCHER_SPEED = 500;
static const int OUR_LAIR = 0;
static const container<std::string> COLOR = {"green", "red"};

//создание окна
Window *newWindow(const sf::Vector2i &windowSize) {
    Window *window = new Window;
    window->windowSize_ = windowSize;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;//задаем уровень сглаживания
    window->window_.create(sf::VideoMode(windowSize.x, windowSize.y),
                           "Game",
                           sf::Style::Close, settings);
    window->window_.setFramerateLimit(30);//fps
    window->camera_.setCenter(float(windowSize.x / 1.9), float(windowSize.y / 1.9));
    return window;
}

//загрузка нужных текстур
GameScene *newGameScene() {
    GameScene *gameScene = new GameScene;
    Level &level = gameScene->level;
    level.loadMapFromFile("../res/map.tmx");
    level.loadObjectsFromFile("../res/objects.xml");
    return gameScene;
}

void mainGameLoop(Window &window, OnUpdate onUpdate, void *pData) {

    srand(time(0));

    sf::Font font;
    font.loadFromFile("../res/font.ttf");
    sf::Clock click, attack, moveTime, updateArmy, updateTable, win, resource;
    float x = 0, y = 0, x1 = 0, y1 = 0;
    int height = 0, width = 0;
    bool flag = false, flagClick = false, flagZoneClick = false, flagWin = false;

    GameScene *gameScene = reinterpret_cast<GameScene *>(pData);
    container<Object *> objects;
    //Lair *lair = nullptr;


    // create a view half the size of the default view
    sf::View view = window.window_.getDefaultView();

//------------------------------------------------------------------------------------------------------
    while (window.window_.isOpen()) {
        window.window_.setView(window.window_.getDefaultView());



//////////////////////////////////////ПРОВЕРЯЕМ СОБЫТИЯ/////////////////////////////////
        sf::Event event;
        while (window.window_.pollEvent(event)) {
            /////////////////закрытие//////////////////////////////////////
            if (event.type == sf::Event::Closed) {
                window.window_.close();
            }
            /////////////////события клавиш мышки//////////////////////////
            if (click.getElapsedTime().asMilliseconds() > 300) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        x1 = event.mouseButton.x;
                        y1 = event.mouseButton.y;
                        x = (window.camera_.getCenter().x +
                             (float(event.mouseButton.x) / window.windowSize_.x - float(1) / 2) *
                             window.camera_.getSize().x);
                        y = (window.camera_.getCenter().y +
                             (float(event.mouseButton.y) / window.windowSize_.y - float(1) / 2) *
                             window.camera_.getSize().y);
                    }
                    click.restart();
                    std::cout << x1 << ";" << y1 << std::endl;
                    flagClick = true;
                }
                if (event.type == sf::Event::MouseButtonReleased) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        height = abs(int(x - (window.camera_.getCenter().x +
                                              (float(event.mouseButton.x) / window.windowSize_.x - float(1) / 2) *
                                              window.camera_.getSize().x)));
                        width = abs(int(y - (window.camera_.getCenter().y +
                                             (float(event.mouseButton.y) / window.windowSize_.y - float(1) / 2) *
                                             window.camera_.getSize().y)));
                        std::cout << x << ";" << y << "    " << height << ";" << width << std::endl;
                    }
                    flagZoneClick = true;
                }
            }
            ///////////////////пауза///////////////////////////////////////
            if (event.type == sf::Event::LostFocus) {
                while (true)
                    if (window.window_.pollEvent(event))
                        break;
            }
            ////////////////колесико мышки/////////////////////////////////
            if (event.type == sf::Event::MouseWheelMoved) {
                std::cout << "wheel movement: " << event.mouseWheel.delta << std::endl;
            }
        }
////////////////////////////////////////////////////////////////////////////////////////


        const sf::Time elapsedTime = window.clock_.getElapsedTime();
        window.clock_.restart();
        onUpdate(pData, window, elapsedTime.asSeconds());//обновление экрана
        window.window_.clear();
        gameScene->level.draw(window.window_);



/////////////////////////ОБНОВЛЕНИЕ SPRITE and TABLE/////////////////////////////////////
        updateScene(updateTable, attack, resource, &gameScene->level, &window.window_);
/////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////ОТРИСОВКА ОБЪЕКТОВ/////////////////////////////////////////
        drawObjects(gameScene->level, &window.window_, font);
/////////////////////////////////////////////////////////////////////////////////////////



/////////////////////// если куда то тыкнули или выделили область////////////////////////
        doPlayerEvents(&flag, &flagClick, &flagZoneClick, objects, x, y, x1, y1, width, height, &gameScene->level,
                       &window, font);
/////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////-------WIN-------------/////////////////////////////////////////
        if (gameScene->level.getColonies().size() == 1) {
            window.window_.setView(window.window_.getDefaultView());
            flagWin = true;
            sf::Text win1("WINNER WINNER", font, 100);
            sf::Text win2("CHICKEN DINER", font, 100);
            win1.setPosition(125, 400);
            win2.setPosition(150, 500);
            window.window_.draw(win1);
            window.window_.draw(win2);
        } else {
            win.restart();
        }
        if (flagWin && win.getElapsedTime().asMilliseconds() > 10000) {
            break;
        }
/////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////
        window.window_.display();
        width = 0;
        height = 0;
        flagClick = false;
        flagZoneClick = false;


    }

//----------------------------------------------------------------------------------------------------------
}

void doPlayerEvents(bool *flag, bool *flagClick, bool *flagZoneClick,
                    container<Object *> &objects,
                    float x, float y, float x1, float y1,
                    int width,
                    int height, Level *level, Window *window, sf::Font &font) {

    Lair* lair = level->getColonies()[OUR_LAIR]->getLair();
    //если в прошлый раз тыкнули на UNIT, то указываем ему куда идти
    if (*flag && *flagClick) {
        std::cout << objects.size() << std::endl;
        int a = sqrt(objects.size());
        if (a == 1)
            a++;
        int xX = 0, yY = 0;
        for (int i = 0; i < objects.size(); i++, xX++) {
            if (xX >= a) {
                xX = 0;
                yY++;
            }
            objects[i]->moveX = x + xX * objects[i]->width + 3;
            objects[i]->moveY = y + yY * objects[i]->width + 3;
        }
        x = 0;
        y = 0;
        width = 0;
        height = 0;
        *flag = false;
        objects.clear();
    }

    //если тыкнули на таблицу
    if (lair != nullptr) {
        if (lair->getOpen()) {

            Stormtrooper *stormtrooper = nullptr;\
            Hunter *hunter = nullptr;
            Usual *usual = nullptr;
            Cleaner *cleaner = nullptr;

            if (level->getColonies()[OUR_LAIR]->wasteResources(
                    lair->checkTap(x1, y1, stormtrooper,
                                   hunter,
                                   usual,
                                   cleaner))) {
                if (stormtrooper != nullptr) {
                    level->getColonies()[OUR_LAIR]->getArmy()->setUnit(stormtrooper);
                    level->getTable()->pushObject(stormtrooper);
                } else if (hunter != nullptr) {
                    level->getColonies()[OUR_LAIR]->getArmy()->setUnit(hunter);
                    level->getTable()->pushObject(hunter);
                } else if (usual != nullptr) {
                    level->getColonies()[OUR_LAIR]->getArmy()->setUnit(usual);
                    level->getTable()->pushObject(usual);
                } else if (cleaner != nullptr) {
                    level->getColonies()[OUR_LAIR]->getArmy()->setUnit(cleaner);
                    level->getTable()->pushObject(cleaner);
                }
                level->getColonies()[OUR_LAIR]->getLair()->setOpen(false);
            }
        }
    }

    //объекты в выделенной области
    if (*flagClick || *flagZoneClick) {
        objects = level->getTable()->getObjects(x,y, width, height,
                                       level->getColonies()[OUR_LAIR]->getColor());
    }

    //если тыкнули или выделили объекты
    if (objects.size() != 0) {
        //получаем логово
        lair = level->getColonies()[OUR_LAIR]->getLair();

        //если тыкнули на логово
        if (objects[0]->type == "lair") {
            if (objects[0] == lair) {
                lair->drawTableOfUnits(&window->window_, font);
            }
            lair->setOpen(true);
        } else
            lair->setOpen(false);

        //если тыкнули на солдата/солдат
        if (objects[0]->type == "unit") {
            *flag = true;
        }
    }
}

void drawObjects(Level level, sf::RenderWindow *window, sf::Font &font) {

    //рисуем ресурсы
    for (int i = 0; i < level.getResources().size(); i++) {
        level.getResources()[i]->draw(*window);
        sf::Text text(std::to_string(level.getResources()[i]->getHealth()), font, 15);
        if (level.getResources()[i]->getColony() != nullptr) {
            if (level.getResources()[i]->getColony()->getColor() == "red")
                text.setFillColor(sf::Color::Red);
            else if (level.getResources()[i]->getColony()->getColor() == "green")
                text.setFillColor(sf::Color(40, 80, 40));
            else if (level.getResources()[i]->getColony()->getColor() == "magenta")
                text.setFillColor(sf::Color::Magenta);
            else if (level.getResources()[i]->getColony()->getColor() == "yellow")
                text.setFillColor(sf::Color::Yellow);
        } else
            text.setFillColor(sf::Color::Blue);
        text.setPosition(level.getResources()[i]->x + 30, level.getResources()[i]->y - 10);
        window->draw(text);
    }
    //отрисовываем войска и логова
    for (int i = 0; i < level.getColonies().size(); i++) {
        if (level.getColonies()[i]->getLair() != nullptr) {
            level.getColonies()[i]->getLair()->draw(*window);
            sf::Text text(std::to_string(level.getColonies()[i]->getLair()->getHealth()), font, 20);
            if (level.getColonies()[i]->getColor() == "red")
                text.setFillColor(sf::Color::Red);
            else if (level.getColonies()[i]->getColor() == "green")
                text.setFillColor(sf::Color(40, 80, 40));
            else if (level.getColonies()[i]->getColor() == "magenta")
                text.setFillColor(sf::Color::Magenta);
            else if (level.getColonies()[i]->getColor() == "yellow")
                text.setFillColor(sf::Color::Yellow);
            text.setPosition(level.getColonies()[i]->getLair()->x + 30, level.getColonies()[i]->getLair()->y - 30);
            window->draw(text);
        }
    }

    for (int i = 0; i < level.getColonies().size(); i++) {
        Army *A = level.getColonies()[i]->getArmy();
        if (A != nullptr) {
            for (int j = 0; j < A->getHunters().size(); j++) {
                A->getHunters()[j]->draw(*window);
                sf::Text text(std::to_string(A->getHunters()[j]->getHealth()), font, 15);
                text.setFillColor(sf::Color::Black);
                text.setPosition(A->getHunters()[j]->x + 10, A->getHunters()[j]->y - 15);
                window->draw(text);

            }
            for (int j = 0; j < A->getStormtroopers().size(); j++) {
                A->getStormtroopers()[j]->draw(*window);
                sf::Text text(std::to_string(A->getStormtroopers()[j]->getHealth()), font, 15);
                text.setFillColor(sf::Color::Black);
                text.setPosition(A->getStormtroopers()[j]->x + 10, A->getStormtroopers()[j]->y - 15);
                window->draw(text);
            }
            for (int j = 0; j < A->getCleaners().size(); j++) {
                A->getCleaners()[j]->draw(*window);
                sf::Text text(std::to_string(A->getCleaners()[j]->getHealth()), font, 15);
                text.setFillColor(sf::Color::Black);
                text.setPosition(A->getCleaners()[j]->x + 10, A->getCleaners()[j]->y - 15);
                window->draw(text);
            }
            for (int j = 0; j < A->getUsuals().size(); j++) {
                A->getUsuals()[j]->draw(*window);
                sf::Text text(std::to_string(A->getUsuals()[j]->getHealth()), font, 15);
                text.setFillColor(sf::Color::Black);
                text.setPosition(A->getUsuals()[j]->x + 10, A->getUsuals()[j]->y - 15);
                window->draw(text);
            }
        }
    }

    level.getColonies()[OUR_LAIR]->drawTableOfResource(window, font);
}

void
updateScene(sf::Clock &updateTable, sf::Clock &attack, sf::Clock &resource, Level *level, sf::RenderWindow *window) {

    //обновление положения в таблице
    if (updateTable.getElapsedTime().asMilliseconds() > 10) {

        //конец игры
        for (int i = 0; i < level->getColonies().size(); i++) {
            level->getColonies()[i]->getArmy()->checkUnitsHealth(level->getTable());
            if (level->getColonies()[i]->getLair() != nullptr) {
                Lair *lair = level->getColonies()[i]->getLair();
                if (lair->getHealth() <= 0) {
                    level->getTable()->deleteObject(lair);
                    delete lair;
                    level->getColonies()[i]->setLair(nullptr);
                }
            }
            if (level->getColonies()[i]->getLair() == nullptr)
                if (level->getColonies()[i]->getArmy() != nullptr)
                    if (level->getColonies()[i]->getArmy()->size() == 0) {
                        Army *army = level->getColonies()[i]->getArmy();
                        level->getColonies()[i]->setArmy(nullptr);
                        delete army;
                    }
            if (level->getColonies()[i]->getArmy() == nullptr && level->getColonies()[i]->getLair() == nullptr) {
                //auto begin = level->colonies_.cbegin();
                level->getColonies().erase(/*begin + */i);
            }
        }

        level->getTable()->update(COLOR[OUR_LAIR], window);

        int j, k;

        //атака персонажей
        if (attack.getElapsedTime().asMilliseconds() > 1000) {

            //для каждой колонии
            for (int q = 0; q < level->getColonies().size(); q++) {
                if (level->getColonies()[q]->getResources().size() >= level->getColonies()[q]->getLair()->getLevel() * 2) {
                    level->getColonies()[q]->getLair()->levelUp();
                }
                Army *army = level->getColonies()[q]->getArmy();
                if (army != nullptr) {
                    for (int p = 0; p < level->getColonies().size(); p++) {
                        if (level->getColonies()[q] == level->getColonies()[p])
                            continue;
                        else {
                            Army *enemyArmy = level->getColonies()[p]->getArmy();

                            container<Stormtrooper *> stormtroopers = army->getStormtroopers();
                            container<Usual *> usuals = army->getUsuals();
                            container<Hunter *> hunters = army->getHunters();
                            container<Cleaner *> cleaners = army->getCleaners();

                            for (int i = 0; i < stormtroopers.size(); i++) {
                                if (stormtroopers[i]->x == stormtroopers[i]->moveX &&
                                    stormtroopers[i]->y == stormtroopers[i]->moveY) {

                                    container<Cell *> cellsObject = level->getTable()->getCellsObject(stormtroopers[i]);
                                    bool flagStop = false;
                                    for (j = 0; j < cellsObject.size(); j++) {
                                        container<Object *> objects = cellsObject[j]->getObjects();
                                        for (k = 0; k < objects.size(); k++) {
                                            if (objects[k]->color != COLOR[q]) {
                                                if (objects[k]->type == "unit") {
                                                    stormtroopers[i]->attackUnit(enemyArmy->findUnit(objects[k]),
                                                                                 rand() % 1000);
                                                    flagStop = true;
                                                    break;
                                                } else if (objects[k]->type == "lair" &&
                                                           objects[k]->color == level->getColonies()[p]->getColor()) {
                                                    Lair *lair = level->getColonies()[p]->getLair();
                                                    lair->setHealth(lair->getHealth() - stormtroopers[i]->getDamage());
                                                    stormtroopers[i]->setState(true);
                                                    std::cout << "attack lair" << std::endl;
                                                    flagStop = true;
                                                    break;
                                                }
                                            }
                                        }
                                        if (flagStop)
                                            break;
                                    }
                                }
                            }
                            for (int i = 0; i < cleaners.size(); i++) {
                                if (cleaners[i]->x == cleaners[i]->moveX && cleaners[i]->y == cleaners[i]->moveY) {

                                    container<Cell *> cellsObject = level->getTable()->getCellsObject(cleaners[i]);
                                    bool flagStop = false;
                                    cleaners[i]->setState(false);
                                    for (j = 0; j < cellsObject.size(); j++) {
                                        container<Object *> objects = cellsObject[j]->getObjects();
                                        for (k = 0; k < objects.size(); k++) {
                                            if (objects[k]->color != COLOR[q]) {
                                                if (objects[k]->type == "resource") {
                                                    ((ResourcePoint *) objects[k])->takeDamage(cleaners[i]->getTake(),
                                                                                               level->getColonies()[q]);
                                                    flagStop = true;
                                                    break;
                                                }
                                            }
                                        }
                                        if (flagStop)
                                            break;
                                    }
                                }
                            }
                            for (int i = 0; i < hunters.size(); i++) {
                                if (hunters[i]->x == hunters[i]->moveX && hunters[i]->y == hunters[i]->moveY) {

                                    container<Cell *> cellsObject = level->getTable()->getCellsObject(hunters[i]);
                                    bool flagStop = false;
                                    hunters[i]->setState(false);
                                    for (j = 0; j < cellsObject.size(); j++) {
                                        container<Object *> objects = cellsObject[j]->getObjects();
                                        for (k = 0; k < objects.size(); k++) {
                                            if (objects[k]->color != COLOR[q]) {
                                                if (objects[k]->type == "unit") {
                                                    hunters[i]->attackUnit(enemyArmy->findUnit(objects[k]),
                                                                           rand() % 1000);
                                                    hunters[i]->setState(true);
                                                    flagStop = true;
                                                    break;
                                                }
                                            }
                                        }
                                        if (flagStop)
                                            break;
                                    }
                                }
                            }
                            for (int i = 0; i < usuals.size(); i++) {
                                if (usuals[i]->x == usuals[i]->moveX && usuals[i]->y == usuals[i]->moveY) {

                                    container<Cell *> cellsObject = level->getTable()->getCellsObject(usuals[i]);
                                    bool flagStop = false;
                                    usuals[i]->setState(false);
                                    for (j = 0; j < cellsObject.size(); j++) {
                                        container<Object *> objects = cellsObject[j]->getObjects();
                                        for (k = 0; k < objects.size(); k++) {
                                            if (objects[k]->color != COLOR[q]) {
                                                if (objects[k]->type == "unit") {
                                                    usuals[i]->attackUnit(enemyArmy->findUnit(objects[k]),
                                                                          rand() % 1000);
                                                    usuals[i]->setState(true);
                                                    flagStop = true;
                                                    break;
                                                } else if (objects[k]->type == "resource") {
                                                    if (((ResourcePoint *) objects[k])->getColony() == nullptr) {
                                                        ((ResourcePoint *) objects[k])->takeDamage(
                                                                cleaners[i]->getTake(),
                                                                level->getColonies()[q]);
                                                        flagStop = true;
                                                        break;
                                                    }
                                                }
                                            }
                                        }
                                        if (flagStop)
                                            break;
                                    }
                                }
                            }
                            attack.restart();
                        }
                    }
                }

                //добавка ресурсов
                if (resource.getElapsedTime().asMilliseconds() > 60000) {
                    std::cout << "do it" << std::endl;
                    container<Object *> resources = level->getColonies()[q]->getResources();
                    for (int i = 0; i < resources.size(); i++) {
                        if (resources[i]->name == "acid") {
                            ((AcidPoint *) resources[i])->toIncrease(((AcidPoint *) resources[i])->getColony());
                        } else if (resources[i]->name == "salt") {
                            ((SaltPoint *) resources[i])->toIncrease(((SaltPoint *) resources[i])->getColony());
                        }
                    }
                    resource.restart();
                }

            }

        }
        updateTable.restart();
    }
}

void destroyGameScene(GameScene *&gameScene) {
    for(int i=0; i<gameScene->level.getColonies().size(); i++){
        Colony* colony = gameScene->level.getColonies()[0];
        Army* army=colony->getArmy();
        container<Stormtrooper*> stormtroopers=army->getStormtroopers();
        container<Cleaner*> cleaners=army->getCleaners();
        container<Usual*> usuals=army->getUsuals();
        container<Hunter*> hunters=army->getHunters();

        for(int j=0; j<stormtroopers.size();j++){
            delete stormtroopers[j];
        }
        for(int j=0; j<cleaners.size();j++){
            delete cleaners[j];
        }
        for(int j=0; j<usuals.size();j++){
            delete usuals[j];
        }
        for(int j=0; i<hunters.size();j++){
            delete hunters[j];
        }
        //delete colony->getLair()->getTableOfUnits();
        delete colony->getLair();
        delete colony->getTableOfResource();
    }
    delete gameScene;
    gameScene = nullptr;
}

void destroyWindow(Window *&window) {
    delete window;
    window = nullptr;
}

//Проверка, не выходим ли бы за края. Применение изменений
void UpdateCamera(void *pData, Window &window, float deltaSec) {
    // Извлекаем указатель на GameLogic, ранее переданный в игровой цикл.
    GameScene *gameScene = reinterpret_cast<GameScene *>(pData);
    (void) deltaSec;
    //действия с камерой
    sf::Vector2f movement = Round(GetWatcherDirection() * WATCHER_SPEED * deltaSec);
    int number = GetWatcherZoom();

    //проверка, не вышли ли мы за края карты
    for (int i = 0; i < 2; i++)
        if ((window.camera_.getCenter().y - window.camera_.getSize().y / 2 + movement.y) >= 10 &&
            (window.camera_.getCenter().x - window.camera_.getSize().x / 2 + movement.x) >= 10 &&
            (movement.y + window.camera_.getCenter().y + window.camera_.getSize().y / 2) <=
            (gameScene->level.getTileMapHeight() - 10) &&
            (movement.x + window.camera_.getCenter().x + window.camera_.getSize().y / 2) <=
            (gameScene->level.getTileMapWidth() - 10)) {
            if (i == 0)
                window.camera_.setCenter(window.camera_.getCenter() + movement);
            if (i == 1)
                if (number != 0)
                    window.camera_.zoom(1.0f - 0.01f * float(number));
        }
    setCameraCenter(window, window.camera_.getCenter());//начальная позиция

    //не дает уйти за края экрана
    if ((window.camera_.getCenter().y - window.camera_.getSize().y / 2) < 10 ||
        (window.camera_.getCenter().x - window.camera_.getSize().x / 2) < 10 ||
        (window.camera_.getCenter().y + window.camera_.getSize().y / 2) >
        (gameScene->level.getTileMapHeight() - 10) ||
        (window.camera_.getCenter().x + window.camera_.getSize().y / 2) >
        (gameScene->level.getTileMapWidth()) - 10) {
        window.camera_.zoom(0.9999f);
    }
}

// Выполняет нормализацию вектора (приведение к единичной длине).
sf::Vector2f Normalize(const sf::Vector2f &value) {
    const float length = std::hypotf(value.x, value.y);
    if (length < FLT_EPSILON) {
        return sf::Vector2f(0, 0);
    }
    return value / length;
}

// Округляет компоненты вектора до ближайших целых чисел.
sf::Vector2f Round(const sf::Vector2f &value) {
    return sf::Vector2f(roundf(value.x), roundf(value.y));
}

// Определяет состояние клавиатуры и выбирает направление движения.
// Возвращает нормализованный вектор направления игрока.
sf::Vector2f GetWatcherDirection() {
    sf::Vector2f direction;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        direction.y = -1;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        direction.y = +1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        direction.x = -1;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        direction.x = +1;
    }

    return Normalize(direction);
}

//Зум камеры
int GetWatcherZoom() {
    int number = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp))
        number++;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown))
        number--;
    return number;
}

void setCameraCenter(Window &window, const sf::Vector2f &center) {
    window.camera_.setCenter(center.x, center.y);//ставит камеру
    window.window_.setView(window.camera_);//перезагружает камеру
}
