#include "TableOfUnits.h"

TableOfUnits::TableOfUnits() {
    sf::Image img;
    img.loadFromFile("../res/image/TableOfUnits.png");
    this->texture.loadFromImage(img);
    this->background.setTexture(texture);

    this->cleaner_ = nullptr;
    this->hunter_ = nullptr;
    this->usual_ = nullptr;
    this->stormtrooper_ = nullptr;

    this->costC_ = {40, 20, 30};
    this->costH_ = {50, 25, 50};
    this->costS_ = {25, 50, 50};
    this->costU_ = {30, 30, 40};
}

void TableOfUnits::newUnits(int level) {
    this->hunter_ = new Hunter(level);
    this->stormtrooper_ = new Stormtrooper(level);
    this->cleaner_ = new Cleaner(level);
    this->usual_ = new Usual(level);
}

void TableOfUnits::draw(int level, sf::RenderWindow *window, sf::Font &font) {

    if (this->cleaner_ == nullptr)
        this->newUnits(level);
    else if (this->cleaner_->getLevel() != level)
        this->newUnits(level);

    window->setView(window->getDefaultView());
    this->getSprite().setPosition(900, 300);
    window->draw(this->getSprite());

    //Stormtrooper
    int health = this->cleaner_->getMaxHealth();
    if (1) {
        sf::Text textH(std::to_string(health), font, 15);
        textH.setPosition(920, 334);
        sf::Text textD(std::to_string(this->stormtrooper_->getDamage()), font, 15);
        textD.setPosition(920, 348);
        sf::Text textL(std::to_string(level), font, 15);
        textL.setPosition(920, 362);
        sf::Text text(std::to_string(this->stormtrooper_->getDamage()), font, 10);
        text.setPosition(920, 383);
        window->draw(text);
        window->draw(textH);
        window->draw(textD);
        window->draw(textL);

        sf::Text salt(std::to_string(this->costS_[0]), font, 15);
        salt.setPosition(918, 413);
        sf::Text acid(std::to_string(this->costS_[1]), font, 15);
        acid.setPosition(948, 413);
        sf::Text food(std::to_string(this->costS_[2]), font, 15);
        food.setPosition(978, 413);
        window->draw(salt);
        window->draw(acid);
        window->draw(food);
    }

    //Hunter
    if (1) {
        sf::Text textH(std::to_string(health), font, 15);
        textH.setPosition(920, 436);
        sf::Text textD(std::to_string(this->hunter_->getDamage()), font, 15);
        textD.setPosition(920, 451);
        sf::Text textL(std::to_string(level), font, 15);
        textL.setPosition(920, 465);
        sf::Text text(std::to_string(0), font, 10);
        text.setPosition(920, 484);
        window->draw(text);
        window->draw(textH);
        window->draw(textD);
        window->draw(textL);

        sf::Text salt(std::to_string(this->costH_[0]), font, 15);
        salt.setPosition(918, 512);
        sf::Text acid(std::to_string(this->costH_[1]), font, 15);
        acid.setPosition(948, 512);
        sf::Text food(std::to_string(this->costH_[2]), font, 15);
        food.setPosition(978, 512);
        window->draw(salt);
        window->draw(acid);
        window->draw(food);
    }

    //Usual
    if (1) {
        sf::Text textH(std::to_string(health), font, 15);
        textH.setPosition(920, 538);
        sf::Text textD(std::to_string(this->usual_->getDamage()), font, 15);
        textD.setPosition(920, 553);
        sf::Text textL(std::to_string(level), font, 15);
        textL.setPosition(920, 567);
        sf::Text text(std::to_string(0), font, 10);
        text.setPosition(920, 585);
        window->draw(text);
        window->draw(textH);
        window->draw(textD);
        window->draw(textL);

        sf::Text salt(std::to_string(this->costU_[0]), font, 15);
        salt.setPosition(918, 610);
        sf::Text acid(std::to_string(this->costU_[1]), font, 15);
        acid.setPosition(948, 610);
        sf::Text food(std::to_string(this->costU_[2]), font, 15);
        food.setPosition(978, 610);
        window->draw(salt);
        window->draw(acid);
        window->draw(food);
    }

    //Cleaner
    if (1) {
        sf::Text textH(std::to_string(health), font, 15);
        textH.setPosition(920, 635);
        sf::Text textD(std::to_string(0), font, 15);
        textD.setPosition(920, 650);
        sf::Text textL(std::to_string(level), font, 15);
        textL.setPosition(920, 666);
        sf::Text text(std::to_string(0), font, 10);
        text.setPosition(920, 685);
        window->draw(text);
        window->draw(textH);
        window->draw(textD);
        window->draw(textL);

        sf::Text salt(std::to_string(this->costC_[0]), font, 15);
        salt.setPosition(918, 710);
        sf::Text acid(std::to_string(this->costC_[1]), font, 15);
        acid.setPosition(948, 710);
        sf::Text food(std::to_string(this->costC_[2]), font, 15);
        food.setPosition(978, 710);
        window->draw(salt);
        window->draw(acid);
        window->draw(food);
    }
}

std::vector<int> TableOfUnits::getCost(int number) {
    if (number == 1)
        return this->costS_;
    else if (number == 2)
        return this->costH_;
    else if (number == 3)
        return this->costU_;
    else if (number == 4)
        return this->costC_;
    else
        return {0,0,0};
}

