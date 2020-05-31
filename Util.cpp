#ifndef __UTIL_CPP
#define __UTIL_CPP

#include "Util.h"

ReadResult Util::readInt(char* buffer, int start) {
    ReadResult result;
    result.string = nullptr;
    int end = start;
    while (buffer[end] != (char)10) {
        end++;
    }
    result.nextIndex = end + 1;
    int number = 0;
    for (int i = start; i < end; i++) {
        if (buffer[i] >= '0' && buffer[i] <= '9') {
            number = number*10 + (buffer[i] - '0');
        } else {
            result.number = -1;
            return result;
        }
    }
    result.number = number;
    return result;
}

ReadResult Util::readString(char* buffer, int start) {
    ReadResult result;
    result.number = 0;
    int end = start;
    while (buffer[end] != (char)10) {
        end++;
    }
    result.nextIndex = end + 1;
    result.string = new char[end - start + 1];
    for (int i = start; i < end; i ++) {
        result.string[i - start] = buffer[i];
    }
    result.string[end - start] = '\0';
    return result;
}

const char* Util::eraToString(Era era) {
    switch (era) {
        case CRETACEOUS:
            return "Cretaceous";
        case TRIASSIC:
            return "Triassic";
        case JURASSIC:
            return "Jurassic";
    }
}

const char* Util::cageSizeToString(CageSize cageSize) {
    switch (cageSize) {
        case SMALL:
            return "Small - 1 slot";
        case MEDIUM:
            return "Medium - 3 slots";
        case BIG:
            return "Big - 10 slots";
    }
}

const char* Util::dinosaurClassToString(DinosaurClass dinosaurClass) {
    switch (dinosaurClass) {
        case HERBIVORE:
            return "Herbivore";
        case CARNIVORE:
            return "Carnivore";
        case FLYING_CLASS:
            return "Flying class";
        case WATER_CLASS:
            return "Water class";
    }
}

const char* Util::genderToString(Gender gender) {
    switch (gender) {
        case MALE:
            return "Male";
        case FEMALE:
            return "Female";
    }
}

const char* Util::foodTypeToString(FoodType foodType) {
    switch (foodType) {
        case GRASS:
            return "Grass";
        case MEAT:
            return "Meat";
        case FISH:
            return "Fish";
    }
}

#endif