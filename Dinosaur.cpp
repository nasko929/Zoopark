#ifndef __DINOSAUR_CPP
#define __DINOSAUR_CPP

#include "Dinosaur.h"
#include <iostream>
#include <cstring>

int Dinosaur::numberOfDinosaurs = 0;

void Dinosaur::deleteDynamicFields() {
    delete [] this -> name;
    delete [] this -> dinoType;
}

Dinosaur::Dinosaur() {
    this -> id = ++numberOfDinosaurs;
    this -> name = new char[1];
    this -> name[0] = '\0';
    this -> dinoType = new char[1];
    this -> dinoType[0] = '\0';
    this -> amountOfFood = 0;
}

Dinosaur::Dinosaur(char* name, char* dinoType, Gender gender, DinosaurClass dinosaurClass, FoodType foodType, int amountOfFood) : Dinosaur() {
    this -> setName(name);
    this -> setDinoType(dinoType);
    this -> setGender(gender);
    this -> setDinosaurClass(dinosaurClass);
    this -> setFoodType(foodType);
    this -> setAmountOfFood(amountOfFood);
}

Dinosaur::Dinosaur(const Dinosaur& dinosaur) {
    std::cout << "COPY-CONSTRUCTOR dino" << std::endl;
    this-> id = dinosaur.getId();
    this -> setName(dinosaur.getName());
    this -> setDinoType(dinosaur.getDinoType());
    this -> setGender(dinosaur.getGender());
    this -> setDinosaurClass(dinosaur.getDinosaurClass());
    this -> setFoodType(dinosaur.getFoodType());
}

Dinosaur& Dinosaur::operator=(const Dinosaur& dinosaur) {
    this -> deleteDynamicFields();
    this -> id = dinosaur.getId();
    this -> setName(dinosaur.getName());
    this -> setDinoType(dinosaur.getDinoType());
    this -> setGender(dinosaur.getGender());
    this -> setDinosaurClass(dinosaur.getDinosaurClass());
    this -> setFoodType(dinosaur.getFoodType());
}

Dinosaur::~Dinosaur() {
    this -> deleteDynamicFields();
}

int Dinosaur::getId() const {
    return this -> id;
}

char* Dinosaur::getName() const {
    return this -> name;
}

void Dinosaur::setName(const char* name) {
    delete [] this -> name;
    this -> name = new char[strlen(name) + 1];
    strcpy(this -> name, name);
}

char* Dinosaur::getDinoType() const {
    return this -> dinoType;
}

void Dinosaur::setDinoType(const char* dinoType) {
    delete [] this -> dinoType;
    this -> dinoType = new char[strlen(dinoType) + 1];
    strcpy(this -> dinoType, dinoType);
}

Gender Dinosaur::getGender() const {
    return this -> gender;
}

void Dinosaur::setGender(const Gender gender) {
    this -> gender = gender;
}

DinosaurClass Dinosaur::getDinosaurClass() const {
    return this -> dinosaurClass;
}

void Dinosaur::setDinosaurClass(const DinosaurClass dinosaurClass) {
    this -> dinosaurClass = dinosaurClass;
}

FoodType Dinosaur::getFoodType() const {
    return this -> foodType;
}

void Dinosaur::setFoodType(const FoodType foodType) {
    this -> foodType = foodType;
}

int Dinosaur::getAmountOfFood() const {
    return this -> amountOfFood;
}

void Dinosaur::setAmountOfFood(const int amountOfFood) {
    this -> amountOfFood = amountOfFood;
}

#endif