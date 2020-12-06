#pragma once

#include "../Unit/Cleaner/Cleaner.h"
#include "../Unit/Stormtrooper/Stormtrooper.h"
#include "../Unit/Hunter/Hunter.h"
#include "../Unit/Usual/Usual.h"
#include "../Table/Table.h"
#include "../../lib/MyContainer/Container.h"
#include <vector>

class Army {
private:
    container<Stormtrooper *> stormtroopers_;
    container<Usual *> usuals_;
    container<Cleaner *> cleaners_;
    container<Hunter *> hunters_;
public:
    Army() {}

    Army(container<Stormtrooper *> &stormtroopers, container<Usual *> &usuals, container<Hunter *> &hunters,
         container<Cleaner *> &cleaners);


    container<Stormtrooper *> getStormtroopers() { return this->stormtroopers_; }

    container<Usual *> getUsuals() { return this->usuals_; }

    container<Cleaner *> getCleaners() { return this->cleaners_; }

    container<Hunter *> getHunters() { return this->hunters_; }


    void setUnit(Cleaner *cleaner) { this->cleaners_.push_back(cleaner); }

    void setUnit(Stormtrooper *stormtrooper) { this->stormtroopers_.push_back(stormtrooper); }

    void setUnit(Usual *usual) { this->usuals_.push_back(usual); }

    void setUnit(Hunter *hunter) { this->hunters_.push_back(hunter); }

    Unit* findUnit(Object* O);

    void checkUnitsHealth(Table* T);

    int size();

};
