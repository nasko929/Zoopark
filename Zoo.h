#ifndef __ZOO_H
#define __ZOO_H

#include "Cage.h"
#include "Vector.h"

class Zoo {

private:
    Vector<Cage*>* cages;
    int foodAmount;
    void initZoo();
    void initializeRandomCages();

public:
    void deleteDynamicFields();
    Zoo();
    ~Zoo();
    Vector<Cage*>* getCages() const;
    void setCages(Vector<Cage*>*);
    int getFoodAmount() const;
    void setFoodAmount(const int);
    int foodRequiredForAllCages();
    void addNewDinosaur();
    void removeDinosaur();
    void createNewCage();
    void loadStorageWithFood(int);
    void showInfoAboutCages();
    void showInfoAboutDinosaursInCage(int);
};

#endif