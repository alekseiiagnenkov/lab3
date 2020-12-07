#include "Table.h"


Table::Table(int width, int height, std::vector<Cell *> &cells) {
    this->width_ = width;
    this->height_ = height;
    this->cells_ = cells;
}

void Table::deleteObject(Object *object) {
    container<Cell *> cells = this->getCellsObject(object);
    for (int i = 0; i < cells.size(); i++) {
        cells[i]->deleteObject(object);
    }
}

void Table::update(const std::string &color, sf::RenderWindow *window) {
    std::vector<Cell *> cells = this->getCells();
    bool flag = true;

    //считываем все объекты
    for (int i = 0; i < cells.size(); i++) {
        container<Object *> objects = cells[i]->getObjects();
        for (int j = objects.size() - 1; j >= 0; j--) {

            //если это солдат, то
            if (objects[j]->type == "unit") {

                ///////////определяем взаимодействие с соседними объектами//////////////////
//                if (objects[j]->x == objects[j]->moveX && objects[j]->y == objects[j]->moveY) {
//                    container<Cell *> cellsObject = getCellsObject(objects[j]);
//                    //массив соседних ячек с объектами
//                    container<Cell *> nearObjects = getNearObjects(objects[j]);
//                }
                //////////////////////////////////////////////////////////////////////////////


                ////////////////////////////ДВИЖЕНИЕ ВРАГОВ//////////////////////////////////////
                if ((objects[j]->x == objects[j]->moveX ||
                     objects[j]->y == objects[j]->moveY) && objects[j]->color != color) {
                    container<Cell *> cellsObject;
                    bool flag2 = true;
                    float x = objects[j]->x, y = objects[j]->y;
                    do {
                        if (flag2) {
                            objects[j]->x = rand() % 3200;
                            objects[j]->y = rand() % 3200;
                            flag2 = false;
                        }
                        cellsObject = getCellsObject(objects[j]);
                        for (int k = 0; k < cellsObject.size(); k++)
                            if (cellsObject[k]->getType() == "solid") {
                                flag2 = true;
                                break;
                            }
                    } while (flag2);
                    objects[j]->moveX = objects[j]->x;
                    objects[j]->moveY = objects[j]->y;
                    objects[j]->y = y;
                    objects[j]->x = x;
                }

                //////////////////ДВИЖЕНИЕ СОЛДАТ////////////////////////////////////////////////////
                if (objects[j]->x != objects[j]->moveX || objects[j]->y != objects[j]->moveY) {
                    container<Cell *> cellsObject = getCellsObject(objects[j]);//ячейки которым принадлежит unit
                    //sf::Sprite sprite;
//                    for(int o=0; o<cellsObject.size(); o++){
//                        //sprite.setTexture(tileSetImage_);//ссылка на файл с текстурами
//                        sprite.setTextureRect(sf::Rect(0,0,0,0));
//                        sprite.setPosition(cellsObject[o]->getX(), cellsObject[o]->getX());//задаем положение тайла
//                        sprite.setColor(sf::Color(255, 0, 0, 100));
//                        window->draw(sprite);
//                    }

                    ///////////определяем столкновение с solid//////////////////////////////////
                    //массив соседних ячеек с лавой
                    container<Cell *> nearSolids = getSolidCells(objects[j]);

                    //определяем направление движения
                    float x = 0, y = 0;
                    if (objects[j]->x < objects[j]->moveX)
                        x++;
                    else if (objects[j]->x > objects[j]->moveX)
                        x--;
                    if (objects[j]->y < objects[j]->moveY)
                        y++;
                    else if (objects[j]->y > objects[j]->moveY)
                        y--;

                    for (int k = 0; k < nearSolids.size(); k++)
                        for (int l = 0; l < cellsObject.size(); l++) {
                            if (nearSolids[k] ==
                                getCell(cellsObject[l]->getX() + x, cellsObject[l]->getY() + y)) {
                                flag = false;
                                objects[j]->y -= y;
                                objects[j]->x -= x;
                                objects[j]->moveX = objects[j]->x;
                                objects[j]->moveY = objects[j]->y;
                                break;
                            }
                        }
                    if (flag) {
                        for (int k = 0; k < cellsObject.size(); k++)
                            cellsObject[k]->deleteObject(objects[j]);

                        objects[j]->updateMove();

                        cellsObject = getCellsObject(objects[j]);
                        for (int k = 0; k < nearSolids.size(); k++) {
                            for (int l = 0; l < cellsObject.size(); l++) {
                                if (nearSolids[k] == cellsObject[l])
                                    /*getCell(cellsObject[l]->getX()*//* + x*//*, cellsObject[l]->getY()*//* + y*//*))*/ {
                                    objects[j]->y -= y;
                                    objects[j]->x -= x;
                                    objects[j]->moveX = objects[j]->x;
                                    objects[j]->moveY = objects[j]->y;
                                }
                            }
                        }

                        this->pushObject(objects[j]);
                    }
                    flag = true;
                    //////////////////////////////////////////////////////////////////////////////

                }
            }
            if (objects[j]->type == "resource") {
                if (objects[j]->moveX != objects[j]->x || objects[j]->moveY != objects[j]->y) {
                    container<Cell *> cellsObject = getCellsObject(objects[j]);
                    for (int k = 0; k < cellsObject.size(); k++) {
                        cellsObject[k]->deleteObject(objects[j]);
                    }
                    bool flag1 = false;
                    do {
                        if (flag1) {
                            objects[j]->moveX = rand() % 3200;
                            objects[j]->moveY = rand() % 3200;
                        }
                        if (flag1)
                            for (int k = 0; k < cellsObject.size(); k++) {
                                cellsObject[k]->deleteObject(objects[j]);
                            }
                        flag1 = false;
                        objects[j]->x = objects[j]->moveX;
                        objects[j]->y = objects[j]->moveY;
                        this->pushObject(objects[j]);
                        cellsObject = getCellsObject(objects[j]);
                        for (int k = 0; k < cellsObject.size(); k++)
                            if (cellsObject[k]->getType() == "solid") {
                                flag1 = true;
                                break;
                            }
                    } while (flag1);

                    objects[j]->sprite.setPosition(objects[j]->x, objects[j]->y);

                }
            }
        }
    }
}

container<Object *> Table::getObjects(float x, float y, int width, int height, std::string &color) {
    container<Object *> objects;
    if (width != 0 && height != 0)
        for (float j = y; j <= y + height; j += 32)
            for (float i = x; i <= x + width; i += 32) {
                std::vector<Object *> Obj = this->getCells()[index(i, j, width_)]->getObjects();
                for (int k = 0; k < Obj.size(); k++) {
                    Object *object = Obj[k];
                    if (object->type == "unit") {
                        if (object->color == color) {
                            int g;
                            for (g = 0; g < objects.size(); g++)
                                if (object == objects[g])
                                    break;
                            if (g >= objects.size()) {
                                objects.push_back(object);
                            }
                        }
                    }
                }
            }
    else {
        std::vector<Object *> Obj = this->getCell(x, y)->getObjects();
        if (Obj.size() > 0) {
            Object *obj = Obj[Obj.size() - 1];
            if (obj->color == color)
                objects.push_back(obj);
        }
    }
    return objects;
}

void Table::pushObject(Object *object) {
    std::vector<Cell *> cells = this->getCells();
    int a = int(object->width + int(object->x) % 32), b = int(object->height + int(object->y) % 32);

    if (a % 32 > 0)
        a = a / 32 + 1;
    else
        a = a / 32;

    if (b % 32 > 0)
        b = b / 32 + 1;
    else
        b = b / 32;

    for (int i = 0; i < a; i++)
        for (int j = 0; j < b; j++) {
            int ind=index(object->x + i * 32, object->y + j * 32, width_);
            cells[ind]->setObject(object);
        }
}

int index(float x, float y, int width) {
    return int(int(x) / 32 + int(y) / 32 * float(width));
}

container<Cell *> Table::getCellsObject(Object *object) {
    container<Cell *> cells;

    int a = int(object->width + int(object->x) % 32), b = int(object->height + int(object->y) % 32);

    if (a % 32 > 0)
        a = a / 32 + 1;
    else
        a = a / 32;

    if (b % 32 > 0)
        b = b / 32 + 1;
    else
        b = b / 32;

    for (int i = 0; i < a; i++)
        for (int j = 0; j < b; j++) {
            cells.push_back(cells_[index(object->x + i * 32, object->y + j * 32, width_)]);
        }

    return cells;
}

container<Cell *> Table::getNearObjects(Object *object) {
    container<Cell *> cells;
    Cell *cell;
    Object *Obj;
    std::vector<Object *> objects;

    int a = int(object->width + int(object->x) % 32), b = int(object->height + int(object->y) % 32);

    if (a % 32 > 0)
        a = a / 32 + 1;
    else
        a = a / 32;

    if (b % 32 > 0)
        b = b / 32 + 1;
    else
        b = b / 32;


    for (int i = -1; i < a + 1; i++) {
        cell = this->getCell(object->x + i * 32, object->y - 32);
        objects = cell->getObjects();
        for (int j = 0; j < objects.size(); j++) {
            Obj = objects[j];
            if (Obj != nullptr && Obj != object)
                cells.push_back(cell);
        }
    }
    objects.clear();
    //вверх
//    for (float i = object->x - 32; i < object->x + object->width + 32; i += 32) {
//        cell = this->getCell(i, object->y - 32);
//        objects = cell->getObjects();
//        for (int j = 0; j < objects.size(); j++) {
//            Obj = objects[j];
//            if (Obj != nullptr && Obj != object)
//                cells.push_back(cell);
//        }
//    }
//    objects.clear();

    for (int i = 0; i < b; i++) {
        cell = this->getCell(object->x - 32, object->y + i * 32);
        objects = cell->getObjects();
        for (int j = 0; j < objects.size(); j++) {
            Obj = objects[j];
            if (Obj != nullptr && Obj != object)
                cells.push_back(cell);
        }
    }
    objects.clear();
//
//    //сверху вниз края
//    for (int i = object->y; i < object->y + object->height + 32; i += 32) {
//        cell = this->getCell(object->x - 32, i);
//        for (int j = 0; j < objects.size(); j++) {
//            Obj = objects[j];
//            if (Obj != nullptr && Obj != object)
//                cells.push_back(cell);
//        }
//    }
//    objects.clear();

    for (int i = 0; i < b; i++) {
        cell = this->getCell(object->x + a * 32 + 32, object->y + i * 32);
        objects = cell->getObjects();
        for (int j = 0; j < objects.size(); j++) {
            Obj = objects[j];
            if (Obj != nullptr && Obj != object)
                cells.push_back(cell);
        }
    }
    objects.clear();

//    for (int i = object->y; i < object->y + object->height + 32; i += 32) {
//        cell = this->getCell(object->x + object->width + 32, i);
//        objects = cell->getObjects();
//        for (int j = 0; j < objects.size(); j++) {
//            Obj = objects[j];
//            if (Obj != nullptr && Obj != object)
//                cells.push_back(cell);
//        }
//    }
//    objects.clear();

    for (int i = -1; i < a + 1; i++) {
        cell = this->getCell(object->x + i * 32, object->y + b * 32 + 32);
        objects = cell->getObjects();
        for (int j = 0; j < objects.size(); j++) {
            Obj = objects[j];
            if (Obj != nullptr && Obj != object)
                cells.push_back(cell);
        }
    }
    objects.clear();

//    //низ
//    for (int i = object->x - 32; i < object->x + object->width + 32; i += 32) {
//        cell = this->getCell(i, object->y + object->height + 32);
//        objects = cell->getObjects();
//        for (int j = 0; j < objects.size(); j++) {
//            Obj = objects[j];
//            if (Obj != nullptr && Obj != object)
//                cells.push_back(cell);
//        }
//    }
//    objects.clear();
    return cells;
}

container<Cell *> Table::getSolidCells(Object *object) {
    container<Cell *> cells;
    Cell *cell;

    int a = int(object->width + int(object->x) % 32), b = int(object->height + int(object->y) % 32);

    if (a % 32 > 0)
        a = a / 32 + 1;
    else
        a = a / 32;

    if (b % 32 > 0)
        b = b / 32 + 1;
    else
        b = b / 32;



    for (int i = -1; i < a + 1; i++) {
        cell = this->getCell(object->x + i * 32, object->y - 32);
        //вверх
//    for (int i = object->x - 32; i < object->x + object->width + 32; i += 32) {
//        cell = this->getCell(i, object->y - 32);
        if (cell->getType() == "solid") {
            cells.push_back(cell);
        }
    }

    for (int i = 0; i < b; i++) {
        cell = this->getCell(object->x - 32, object->y + i * 32);
//    for (int i = object->y; i < object->y + object->height + 32; i += 32) {
//        cell = this->getCell(object->x - 32, i);
        if (cell->getType() == "solid") {
            cells.push_back(cell);
        }
    }

    for (int i = 0; i < b; i++) {
        cell = this->getCell(object->x + a * 32 + 32, object->y + i * 32);
//        for (int i = object->y; i < object->y + object->height + 32; i += 32) {
//        cell = this->getCell(object->x + object->width + 32, i);
        if (cell->getType() == "solid") {
            cells.push_back(cell);
        }
    }

    for (int i = -1; i < a + 1; i++) {
        cell = this->getCell(object->x + i * 32, object->y + b * 32 + 32);
        //низ
//    for (int i = object->x - 32; i < object->x + object->width + 32; i += 32) {
//        cell = this->getCell(i, object->y + object->height + 32);
        if (cell->getType() == "solid") {
            cells.push_back(cell);
        }
    }
    return cells;
}
