#pragma once

#include "../Unit/Cleaner/Cleaner.h"
#include "../Unit/Stormtrooper/Stormtrooper.h"
#include "../Unit/Hunter/Hunter.h"
#include "../Unit/Usual/Usual.h"
#include "../Table/Table.h"
#include <vector>

class Army {
private:
    std::vector<Stormtrooper *> stormtroopers_;
    std::vector<Usual *> usuals_;
    std::vector<Cleaner *> cleaners_;
    std::vector<Hunter *> hunters_;
public:
    Army() {}

    Army(std::vector<Stormtrooper *> &stormtroopers, std::vector<Usual *> &usuals, std::vector<Hunter *> &hunters,
         std::vector<Cleaner *> &cleaners);


    std::vector<Stormtrooper *> getStormtroopers() { return this->stormtroopers_; }

    std::vector<Usual *> getUsuals() { return this->usuals_; }

    std::vector<Cleaner *> getCleaners() { return this->cleaners_; }

    std::vector<Hunter *> getHunters() { return this->hunters_; }


    void setUnit(Cleaner *cleaner) { this->cleaners_.push_back(cleaner); }

    void setUnit(Stormtrooper *stormtrooper) { this->stormtroopers_.push_back(stormtrooper); }

    void setUnit(Usual *usual) { this->usuals_.push_back(usual); }

    void setUnit(Hunter *hunter) { this->hunters_.push_back(hunter); }

    Unit* findUnit(Object* O);

    void checkUnitsHealth(Table* T);

    int size();

};
