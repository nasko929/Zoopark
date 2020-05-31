#ifndef __CAGE_CPP
#define __CAGE_CPP

#include "Cage.h"
#include <iostream>
#include <cstring>

// Number of created objects.
int Cage::numberOfCages = 0;

/**
 * @brief Method that deletes all dynamic fields from the object. It is called in the destructor.
 */
void Cage::deleteDynamicFields() {
    delete this -> dinosaurs;
}

/**
 * @brief Construct a new Cage object
 */
Cage::Cage() {
    this -> id = ++numberOfCages;
    this -> dinosaurs = new Vector<Dinosaur*>;
    this -> climate = new char[1];
    this -> climate[0] = '\0';
    this -> neededAmountOfFood = 0;
}
/**
 * @brief Construct a new Cage object
 * 
 * @param cageSize - Cage's size.
 * @param climate - Cage's climate.
 * @param era - Cage's era.
 */
Cage::Cage(CageSize cageSize, char* climate, Era era): Cage() {
    this -> setCageSize(cageSize);
    this -> setClimate(climate);
    this -> setEra(era);
}

/**
 * @brief Destroy the Cage object
 */
Cage::~Cage() {
    this -> deleteDynamicFields();
}

int Cage::getId() const {
    return this -> id;
}

CageSize Cage::getCageSize() const {
    return this -> size;
}

void Cage::setCageSize(const CageSize size) {
    this -> size = size;
}

char* Cage::getClimate() const {
    return this -> climate;
}

void Cage::setClimate(const char* climate) {
    delete [] this -> climate;
    this -> climate = new char[strlen(climate) + 1];
    strcpy(this -> climate, climate);
}

Vector<Dinosaur*>* Cage::getDinosaurs() const {
    return this -> dinosaurs;
}

void Cage::setDinosaurs(Vector<Dinosaur*>* dinosaurs) {
    delete this -> dinosaurs;
    this -> dinosaurs = dinosaurs;
}

Era Cage::getEra() const {
    return this -> era;
}

void Cage::setEra(const Era era) {
    this -> era = era;
}

int Cage::getNeededAmountOfFood() const {
    return this -> neededAmountOfFood;
}

void Cage::setNeededAmountOfFood(const int neededAmountOfFood) {
    this -> neededAmountOfFood = neededAmountOfFood;
}

#endif