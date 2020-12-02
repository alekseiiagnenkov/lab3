#include "TableOfResource.h"

TableOfResource::TableOfResource() {
    sf::Image img;
    img.loadFromFile("../res/image/TableOfResource.png");
    this->texture.loadFromImage(img);
    this->background.setTexture(texture);
}

void TableOfResource::draw(int salt, int acid, int food, int numberUnits, sf::RenderWindow* window, sf::Font& font) {

    window->setView(window->getDefaultView());
    this->getSprite().setPosition(300, 10);
    window->draw(this->getSprite());

    sf::Text textS(std::to_string(salt), font, 15);
    textS.setPosition(330,17);
    sf::Text textA(std::to_string(acid), font, 15);
    textA.setPosition(410,17);
    sf::Text textF(std::to_string(food), font, 15);
    textF.setPosition(490,17);
    sf::Text textU(std::to_string(numberUnits), font, 15);
    textU.setPosition(560,17);
    window->draw(textS);
    window->draw(textA);
    window->draw(textF);
    window->draw(textU);

}