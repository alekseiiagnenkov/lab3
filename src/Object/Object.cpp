#include "Object.h"

//const float SPEED=0.25;
const float SPEED=1;

Object::Object(std::string &name, std::string &type, std::string& color, float x, float y, int w, int h) {
    this->x = x;
    this->y = y;
    this->moveY = y;
    this->moveX = x;
    this->width = w;
    this->height = h;
    this->name = name;
    this->type = type;
    this->color = color;
    sf::Image img;
    if (!img.loadFromFile("../res/image/" + color + "/" + name + ".png"))
        std::cout << "No loaded " << color <<" "<< name << std::endl;
    texture.loadFromImage(img);
    sprite.setPosition(float(x), float(y));
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, w, h));
}

void Object::updateMove() {

    if (x != moveX) {
        if(abs(int(x-moveX))<1)
            x=moveX;
        else {
            if (x < moveX)
                x += SPEED;
            else if (x > moveX)
                x -= SPEED;
        }
    }
    if (y != moveY) {
        if(abs(int(y-moveY))<1)
            y=moveY;
        else {
            if (y < moveY)
                y += SPEED;
            else if (y > moveY)
                y -= SPEED;
        }
    }
    sprite.setPosition(x, y);
}

void Object::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

sf::Vector2i Object::getCoord() {
    sf::Vector2i V(x, y);
    return V;
}
