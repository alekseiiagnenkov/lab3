#include "Unit.h"

Unit::Unit(std::string &name, std::string &type, std::string& color,
           int x, int y, int w, int h, int lvl, int health): Object(name, type, color, float(x),float(y),w,h) {
    this->state_ = false;
    this->name_=name;
}

