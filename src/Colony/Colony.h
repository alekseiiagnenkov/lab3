#pragma once

//#include "../Table/Table.h"
//#include "../Unit/Unit.h"
#include "../Lair/Lair.h"
#include "../Army/Army.h"
#include "../TableOfResource/TableOfResource.h"
#include<vector>
#include <string>

class Colony {
private:
    std::string color_;
    int acid_;
    int salt_;
    int food_;
    container<Object*> resources_;
    Lair *lair_;
    Army *army_;
    TableOfResource* TR;
public:
    //CONSTRUCTORS

    Colony(int acid, int salt, int food, Lair *lair, std::string& color, Army*);


    //GETTERS
    Lair *getLair() { return this->lair_; }

    int getFood() { return this->food_; }

    int getAcid() { return this->acid_; }

    int getSold() { return this->salt_; }

   container<Object*> getResources() { return this->resources_;}

    std::string& getColor() { return this->color_; }

    Army* getArmy() {return this->army_;}

    TableOfResource* getTableOfResource() {return this->TR;}


    //SETTERS
    void setLair(Lair *lair) { this->lair_ = lair; }

    void setFood(int food) { this->food_ = food; }

    void setAcid(int acid) { this->acid_ = acid; }

    void setSold(int sold) { this->salt_ = sold; }

    void setArmy(Army* army) { this->army_ = army; }

    void setResource(Object* resource) { this->resources_.push_back(resource); }

    //FUNCTION

    void drawTableOfResource(sf::RenderWindow *window, sf::Font& font);

    bool wasteResources (container<int> waste);

    void updateResources();


};
