#include "Army.h"

Army::Army(container<Stormtrooper *> &stormtroopers, container<Usual *> &usuals, container<Hunter *> &hunters,
           container<Cleaner *> &cleaners) {
    this->stormtroopers_ = stormtroopers;
    this->usuals_ = usuals;
    this->hunters_ = hunters;
    this->cleaners_ = cleaners;
}

Unit *Army::findUnit(Object *object) {
    Unit *unit = nullptr;
    if (object->name == "stormtrooper") {
        for (int i = 0; i < this->stormtroopers_.size(); i++) {
            if (object == this->stormtroopers_[i]) {
                unit = this->stormtroopers_[i];
                break;
            }
        }
    } else if (object->name == "cleaner") {
        for (int i = 0; i < this->cleaners_.size(); i++) {
            if (object == this->cleaners_[i]) {
                unit = this->cleaners_[i];
                break;
            }
        }
    } else if (object->name == "usual") {
        for (int i = 0; i < this->usuals_.size(); i++) {
            if (object == this->usuals_[i]) {
                unit = this->usuals_[i];
                break;
            }
        }
    } else if (object->name == "hunter") {
        for (int i = 0; i < this->hunters_.size(); i++) {
            if (object == this->hunters_[i]) {
                unit = this->hunters_[i];
                break;
            }
        }
    }
    return unit;
}

void Army::checkUnitsHealth(Table *T) {
    for (int i = 0; i < this->hunters_.size(); i++) {
        if (this->hunters_[i]->getHealth() < 0) {
            Hunter *H = this->hunters_[i];
            //auto begin = hunters_.cbegin();
            this->hunters_.erase(/*begin + */i);
            T->deleteObject(H);
            delete H;
        }
    }
    for (int i = 0; i < this->usuals_.size(); i++) {
        if (this->usuals_[i]->getHealth() < 0) {
            Usual *H = this->usuals_[i];
            //auto begin = usuals_.cbegin();
            this->usuals_.erase(/*begin + */i);
            T->deleteObject(H);
            delete H;
        }
    }
    for (int i = 0; i < this->stormtroopers_.size(); i++) {
        if (this->stormtroopers_[i]->getHealth() < 0) {
            Stormtrooper *H = this->stormtroopers_[i];
            //auto begin = stormtroopers_.cbegin();
            this->stormtroopers_.erase(/*begin +*/ i);
            T->deleteObject(H);
            delete H;
        }
    }
    for (int i = 0; i < this->cleaners_.size(); i++) {
        if (this->cleaners_[i]->getHealth() < 0) {
            Cleaner *H = this->cleaners_[i];
            //auto begin = cleaners_.cbegin();
            this->cleaners_.erase(/*begin +*/ i);
            T->deleteObject(H);
            delete H;
        }
    }
}

int Army::size(){
        return this->cleaners_.size()+this->stormtroopers_.size()+this->usuals_.size()+this->hunters_.size();
}