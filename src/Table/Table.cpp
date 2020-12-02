#include "Table.h"
#include <vector>

Table::Table(int width, int height, std::vector<Cell *> &cells) {
    this->width_ = width;
    this->height_ = height;
    this->cells_ = cells;
}

void Table::deleteObject(Object *object) {
    std::vector<Cell *> cells = this->getCellsObject(object);
    for (int i = 0; i < cells.size(); i++) {
        cells[i]->deleteObject(object);
    }
}

void Table::update() {
    std::vector<Cell *> cells = this->getCells();
    bool flag = true;

    //считываем все объекты
    for (int i = 0; i < cells.size(); i++) {
        std::vector<Object *> objects = cells[i]->getObjects();
        for (int j = objects.size() - 1; j >= 0; j--) {

            //если это солдат, то
            if (objects[j]->type == "unit") {

                ///////////определяем взаимодействие с соседними объектами//////////////////
                if (objects[j]->x == objects[j]->moveX && objects[j]->y == objects[j]->moveY) {
                    std::vector<Cell *> cellsObject = getCellsObject(objects[j]);
                    //массив соседних ячек с объектами
                    std::vector<Cell *> nearObjects;
                    nearObjects = getNearObjects(objects[j]);
                }
                ////////////////////////////////////////////////////////////////////////////


                //////////////////ДВИЖЕНИЕ////////////////////////////////////////////////////
                if (objects[j]->x != objects[j]->moveX || objects[j]->y != objects[j]->moveY) {
                    std::vector<Cell *> cellsObject = getCellsObject(objects[j]);

                    ///////////определяем столкновение с solid//////////////////////////////////
                    //массив соседних ячеек с лавой
                    std::vector<Cell *> nearSolids;
                    nearSolids = getSolidCells(objects[j]);
                    //определяем направление движения
                    int x = 0, y = 0;
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
                            if ((nearSolids[k]->getX() == (cellsObject[l]->getX() + x)) &&
                                (nearSolids[k]->getY() == (cellsObject[j]->getY() + y)))
                                flag = false;
                        }
                    if (flag) {
                        for (int k = 0; k < cellsObject.size(); k++)
                            cellsObject[k]->deleteObject(objects[j]);

                        objects[j]->updateMove();

                        cellsObject = getCellsObject(objects[j]);
                        for (int k = 0; k < nearSolids.size(); k++) {
                            for (int l = 0; l < cellsObject.size(); l++) {
                                if (nearSolids[k]->getX() == cellsObject[l]->getX() &&
                                    (nearSolids[k]->getY() == cellsObject[j]->getY())) {
                                    objects[j]->y -= y;
                                    objects[j]->x -= x;
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
                    std::vector<Cell *> cellsObject = getCellsObject(objects[j]);
                    for (int k = 0; k < cellsObject.size(); k++) {
                        cellsObject[k]->deleteObject(objects[j]);
                    }
                    bool flag1 = false;
                    do {
                        if(flag1) {
                            objects[j]->moveX = rand() % 3200;
                            objects[j]->moveY = rand() % 3200;
                        }
                        if (flag1)
                            for (int k = 0; k < cellsObject.size(); k++) {
                                cellsObject[k]->deleteObject(objects[j]);
                            }
                        flag1=false;
                        objects[j]->x = objects[j]->moveX;
                        objects[j]->y = objects[j]->moveY;
                        this->pushObject(objects[j]);
                        cellsObject = getCellsObject(objects[j]);
                        for(int k=0; k<cellsObject.size(); k++)
                            if(cellsObject[k]->getType()=="solid")
                                flag1=true;
                    } while (flag1);

                    objects[j]->sprite.setPosition(objects[j]->x, objects[j]->y);

                }
            }
        }
    }
}

std::vector<Object *> Table::getObjects(int x, int y, int width, int height, std::string &color) {
    std::vector<Object *> objects;
    if (width != 0 && height != 0)
        for (int j = y; j <= y + height; j += 32)
            for (int i = x; i <= x + width; i += 32) {
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
    for (int i = object->x; i < object->x + object->width + cells[0]->getSize(); i += cells[0]->getSize()) {
        for (int j = object->y; j < object->y + object->height + cells[0]->getSize(); j += cells[0]->getSize()) {
            cells[index(i, j, width_)]->setObject(object);
        }
    }
}

int index(int x, int y, int width) {
    return (x / 32 + y / 32 * width);
}

std::vector<Cell *> Table::getCellsObject(Object *object) {
    std::vector<Cell *> cells;
    for (float i = object->x - 32; i < object->x + object->width + 32; i += 32)
        for (float j = object->y - 32; j < object->y + object->height + 32; j += 32) {
            cells.push_back(this->getCell(i, j));
        }

    return cells;
}

std::vector<Cell *> Table::getNearObjects(Object *object) {
    std::vector<Cell *> cells;
    Cell *cell;
    Object *Obj;
    std::vector<Object *> objects;

    //вверх
    for (float i = object->x - 32; i < object->x + object->width + 32; i += 32) {
        cell = this->getCell(i, object->y - 32);
        objects = cell->getObjects();
        for (int j = 0; j < objects.size(); j++) {
            Obj = objects[j];
            if (Obj != nullptr && Obj != object)
                cells.push_back(cell);
        }
    }
    objects.clear();

    //сверху вниз края
    for (int i = object->y; i < object->y + object->height + 32; i += 32) {
        cell = this->getCell(object->x - 32, i);
        for (int j = 0; j < objects.size(); j++) {
            Obj = objects[j];
            if (Obj != nullptr && Obj != object)
                cells.push_back(cell);
        }
    }
    objects.clear();

    for (int i = object->y; i < object->y + object->height + 32; i += 32) {
        cell = this->getCell(object->x + object->width + 32, i);
        objects = cell->getObjects();
        for (int j = 0; j < objects.size(); j++) {
            Obj = objects[j];
            if (Obj != nullptr && Obj != object)
                cells.push_back(cell);
        }
    }
    objects.clear();

    //низ
    for (int i = object->x - 32; i < object->x + object->width + 32; i += 32) {
        cell = this->getCell(i, object->y + object->height + 32);
        objects = cell->getObjects();
        for (int j = 0; j < objects.size(); j++) {
            Obj = objects[j];
            if (Obj != nullptr && Obj != object)
                cells.push_back(cell);
        }
    }
    objects.clear();
    return cells;
}

std::vector<Cell *> Table::getSolidCells(Object *object) {
    std::vector<Cell *> cells;
    Cell *cell;

    //вверх
    for (int i = object->x - 32; i < object->x + object->width + 32; i += 32) {
        cell = this->getCell(i, object->y - 32);
        if (cell->getType() == "solid") {
            cells.push_back(cell);
        }
    }

    for (int i = object->y; i < object->y + object->height + 32; i += 32) {
        cell = this->getCell(object->x - 32, i);
        if (cell->getType() == "solid") {
            cells.push_back(cell);
        }
    }

    for (int i = object->y; i < object->y + object->height + 32; i += 32) {
        cell = this->getCell(object->x + object->width + 32, i);
        if (cell->getType() == "solid") {
            cells.push_back(cell);
        }
    }

    //низ
    for (int i = object->x - 32; i < object->x + object->width + 32; i += 32) {
        cell = this->getCell(i, object->y + object->height + 32);
        if (cell->getType() == "solid") {
            cells.push_back(cell);
        }
    }
    return cells;
}
