#ifndef __CAGE_CPP
#define __CAGE_CPP

#include "Cage.h"
#include <iostream>
#include <cstring>

int Cage::numberOfCages = 0;

void Cage::deleteDynamicFields() {
    delete this -> dinosaurs;
}

Cage::Cage() {
    this -> id = ++numberOfCages;
    this -> dinosaurs = new Vector<Dinosaur*>;
    this -> climate = new char[1];
    this -> climate[0] = '\0';
    this -> neededAmountOfFood = 0;
}

Cage::Cage(CageSize cageSize, char* climate, Era era): Cage() {
    this -> setCageSize(cageSize);
    this -> setClimate(climate);
    this -> setEra(era);
}

Cage::Cage(const Cage& cage) {
    std::cout << "COPY-CONSTRUCT CAGE" << std::endl;
    this -> id = cage.getId();
    this -> setCageSize(cage.getCageSize());
    this -> setClimate(cage.getClimate());
    this -> setDinosaurs(cage.getDinosaurs());
    this -> setEra(cage.getEra());
}

Cage& Cage::operator=(const Cage& cage) {
    this -> deleteDynamicFields();
    this -> id = cage.getId();
    this -> setCageSize(cage.getCageSize());
    this -> setClimate(cage.getClimate());
    this -> setDinosaurs(cage.getDinosaurs());
    this -> setEra(cage.getEra());
}

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