#ifndef __DINOSAUR_H
#define __DINOSAUR_H

#include "DinosaurClass.h"
#include "Gender.h"
#include "FoodType.h"
#include "Era.h"

/**
 * @brief A class that represents the dinosaur object.
 */
class Dinosaur {

private:
    int id;
    char* name;
    char* dinoType;
    Gender gender;
    DinosaurClass dinosaurClass;
    FoodType foodType;
    int amountOfFood;

public:
    static int numberOfDinosaurs;
    void deleteDynamicFields();
    Dinosaur();
    Dinosaur(char*, char*, Gender, DinosaurClass, FoodType, int);
    ~Dinosaur();
    int getId() const;
    char* getName() const;
    void setName(const char*);
    char* getDinoType() const;
    void setDinoType(const char*);
    Gender getGender() const;
    void setGender(const Gender);
    DinosaurClass getDinosaurClass() const;
    void setDinosaurClass(const DinosaurClass);
    FoodType getFoodType() const;
    void setFoodType(const FoodType);
    int getAmountOfFood() const;
    void setAmountOfFood(const int);
};

#endif