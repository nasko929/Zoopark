#ifndef __CAGE_H
#define __CAGE_H
#include "CageSize.h"
#include "Dinosaur.cpp"
#include "Vector.cpp"

/**
 * @brief A class that represents a cage in a zoo.
 */
class Cage {

private:
    int id;
    CageSize size;
    char* climate;
    Vector<Dinosaur*>* dinosaurs;
    Era era;
    int neededAmountOfFood;

public:
    static int numberOfCages;
    void deleteDynamicFields();
    Cage();
    Cage(CageSize, char*, Era);
    ~Cage();
    int getId() const;
    CageSize getCageSize() const;
    void setCageSize(const CageSize);
    char* getClimate() const;
    void setClimate(const char*);
    Vector<Dinosaur*>* getDinosaurs() const;
    void setDinosaurs(Vector<Dinosaur*>*);
    Era getEra() const;
    void setEra(const Era);
    int getNeededAmountOfFood() const;
    void setNeededAmountOfFood(const int);
};

#endif