#ifndef __ZOO_CPP
#define __ZOO_CPP
#define COUT std::cout
#define CIN std::cin
#define ENDL "\n"

#include "Zoo.h"
#include "ReadResult.h"
#include "Util.cpp"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <cstring>

/**
 * @brief A method that deletes all dynamic fields.
 */
void Zoo::deleteDynamicFields() {
    for (int i = 0; i < cages -> size(); i ++) {
        delete cages -> get(i);
    }
    delete this -> cages;
}

/**
 * @brief Construct a new Zoo object
 * A default constructor.
 */
Zoo::Zoo() {
    this -> cages = new Vector<Cage*>;
    this -> foodAmount = 0;
    this -> initZoo();
}

/**
 * @brief Destroy the Zoo object
 */
Zoo::~Zoo() {
    this -> deleteDynamicFields();
}

/**
 * @brief A method that initializes the Zoopark.
 * 
 * It searches for "information.txt" file - if found, takes the information from there.
 * If not, it creates random cages.
 */
void Zoo::initZoo() {
    std::ifstream inputFile("information.txt", std::ios::in);

    if(!inputFile) {
        COUT << "There is no information about existing zoo. Creating a new one...\n";
        this -> initializeRandomCages();
        return;
    }

    inputFile.seekg(0, inputFile.end);
    int length = inputFile.tellg();
    inputFile.seekg(0, inputFile.beg);
    
    char* buffer = new char[length];
    inputFile.read(buffer, length);
    inputFile.close();

    int startIndex = 0;

    ReadResult result = Util::readInt(buffer, startIndex);
    startIndex = result.nextIndex;
    int timestamp = result.number;
    if (timestamp == -1) {
        COUT << "Provided information about the zoo is corrupted. Creating a brand new zoo for you...\n";
        this -> initializeRandomCages();
        return;
    }

    result = Util::readInt(buffer, startIndex);
    startIndex = result.nextIndex;
    if (result.number == -1) {
        COUT << "Provided information about the zoo is corrupted. Creating a brand new zoo for you...\n";
        this -> initializeRandomCages();
        return;
    }
    this -> setFoodAmount(result.number);

    result = Util::readInt(buffer, startIndex);
    startIndex = result.nextIndex;
    int numberOfCages = result.number;
    if (numberOfCages == -1) {
        COUT << "Provided information about the zoo is corrupted. Creating a brand new zoo for you...\n";
        this -> initializeRandomCages();
        return;
    }
    for (int i = 0; i < numberOfCages; i ++) {
        Cage* cage = new Cage;

        result = Util::readInt(buffer, startIndex);
        startIndex = result.nextIndex;
        if (result.number == -1) {
            COUT << "Provided information about the zoo is corrupted. Creating a brand new zoo for you...\n";
            this -> initializeRandomCages();
            return;
        }
        cage -> setCageSize((CageSize)result.number);

        result = Util::readString(buffer, startIndex);
        startIndex = result.nextIndex;
        cage -> setClimate(result.string);

        result = Util::readInt(buffer, startIndex);
        startIndex = result.nextIndex;
        if (result.number == -1) {
            COUT << "Provided information about the zoo is corrupted. Creating a brand new zoo for you...\n";
            this -> initializeRandomCages();
            return;
        }
        cage -> setEra((Era)result.number);

        result = Util::readInt(buffer, startIndex);
        startIndex = result.nextIndex;
        int numberOfDinos = result.number;
        if (numberOfDinos == -1) {
            COUT << "Provided information about the zoo is corrupted. Creating a brand new zoo for you...\n";
            this -> initializeRandomCages();
            return;
        }
        for (int j = 0; j < numberOfDinos; j ++) {
            Dinosaur* dinosaur = new Dinosaur;

            result = Util::readString(buffer, startIndex);
            startIndex = result.nextIndex;
            dinosaur -> setName(result.string);

            result = Util::readString(buffer, startIndex);
            startIndex = result.nextIndex;
            dinosaur -> setDinoType(result.string);

            result = Util::readInt(buffer, startIndex);
            startIndex = result.nextIndex;
            if (result.number == -1) {
                COUT << "Provided information about the zoo is corrupted. Creating a brand new zoo for you...\n";
                this -> initializeRandomCages();
                return;
            }
            dinosaur -> setGender((Gender)result.number);

            result = Util::readInt(buffer, startIndex);
            startIndex = result.nextIndex;
            if (result.number == -1) {
                COUT << "Provided information about the zoo is corrupted. Creating a brand new zoo for you...\n";
                this -> initializeRandomCages();
                return;
            }
            dinosaur -> setDinosaurClass((DinosaurClass)result.number);

            result = Util::readInt(buffer, startIndex);
            startIndex = result.nextIndex;
            if (result.number == -1) {
                COUT << "Provided information about the zoo is corrupted. Creating a brand new zoo for you...\n";
                this -> initializeRandomCages();
                return;
            }
            dinosaur -> setFoodType((FoodType)result.number);

            result = Util::readInt(buffer, startIndex);
            startIndex = result.nextIndex;
            if (result.number == -1) {
                COUT << "Provided information about the zoo is corrupted. Creating a brand new zoo for you...\n";
                this -> initializeRandomCages();
                return;
            }
            dinosaur -> setAmountOfFood(result.number);

            cage -> getDinosaurs() -> pushBack(dinosaur);
            cage -> setNeededAmountOfFood(cage -> getNeededAmountOfFood() + dinosaur -> getAmountOfFood());
        }

        this -> cages -> pushBack(cage);
    }
    time_t now = time(nullptr);
    int currentTimestamp = (int)now;
    int secondsSinceLastZooEntrance = currentTimestamp - timestamp;
    // One day in the zoo is 30 minutes in real-life. 30 minutes = 1800 secs.
    int zooDaysSinceLastZooEntrance = secondsSinceLastZooEntrance / 1800 + (secondsSinceLastZooEntrance % 1800 != 0);
    int foodPerDay = this -> foodRequiredForAllCages();
    int neededFood = zooDaysSinceLastZooEntrance * foodPerDay;
    
    COUT << "You did not see your zoo in " << zooDaysSinceLastZooEntrance << " zoo days." << ENDL;
    COUT << "Your zoo needs " << foodPerDay << " food units per day so that your dinosaurs do not die! Keep that in mind! " << ENDL;
    this -> setFoodAmount(this -> getFoodAmount() - neededFood);
    if (this -> getFoodAmount() < 0) {
        COUT << "!!!Your zoo is in food deficit. Your first job now is to load the food storages with at least " << 
        -this -> getFoodAmount() << " food units. Otherwise, your dinosaurs will die.!!!" << ENDL << ENDL;
    } else {
        COUT << "Everything is going well, your dinosaurs have been fed well since you were not here." << ENDL << ENDL;
    }

}

/**
 * @brief Method that returns how much food is needed for one day in the zoo.
 * 
 * @return int - amount of food.
 */
int Zoo::foodRequiredForAllCages() {
    int foodRequired = 0;
    for (int i = 0; i < this -> getCages() -> size(); i++) {
        foodRequired += this -> getCages() -> get(i) -> getNeededAmountOfFood();
    }
    return foodRequired;
}

/**
 * @brief Method that initializes random cages if no input file found or found, but not in right format.
 */
void Zoo::initializeRandomCages() {
    while (this -> cages -> size() != 0) {
        this -> cages -> pop();
    }

    srand(time(NULL));

    int numberOfCages = rand() % 4 + 2;
    int cageSizes[3] = {1, 3, 10};
    for (int i = 0; i < numberOfCages; i ++) {
        Cage* cage = new Cage;

        int climate = rand() % 3;
        switch(climate) {
            case 0:
                cage -> setClimate("tropical");
                break;
            case 1:
                cage -> setClimate("rainy");
                break;
            case 2:
                cage -> setClimate("cold");
                break;
        }
        cage -> setCageSize((CageSize)cageSizes[rand() % 3]);
        cage -> setEra((Era)(rand() % 3));

        this -> cages -> pushBack(cage);
    }
    this -> setFoodAmount(100);
}

/**
 * @brief Method that adds new dinosaur.
 */
void Zoo::addNewDinosaur() {
    char *name, *dinoType;
    name = new char[128];
    dinoType = new char[128];
    int gender, dinosaurClass, foodType, era, amountOfFood;
    
    COUT << "Type the name of the new Dino (up to 64 characters): ";
    CIN.getline(name, 128);
    while (strlen(name) > 64) {
        COUT << "Name too long." << ENDL;
        COUT << "Type the name of the new Dino (up to 64 characters): ";
        CIN.getline(name, 128);
    }
    
    COUT << "Type the dinosaur type (up to 64 characters): ";
    CIN.getline(dinoType, 128);
    while (strlen(dinoType) > 64) {
        COUT << "Dinosaur type too long." << ENDL;
        COUT << "Type the dinosaur type (up to 64 characters): ";
        CIN.getline(dinoType, 128);
    }
    
    COUT << "Type the number of its gender (Female - 0, Male - 1): ";
    CIN >> gender;
    while (gender < 0 || gender > 1) {
        COUT << "Invalid number." << ENDL;
        COUT << "Type the number of its gender (Female - 0, Male - 1): ";
        CIN >> gender;
    }
    
    COUT << "Type the number of its dinosaur class (Carnivore - 0, Herbivore - 1, Water - 2, Flying - 3): ";
    CIN >> dinosaurClass;
    while (dinosaurClass < 0 || dinosaurClass > 3) {
        COUT << "Invalid number." << ENDL;
        COUT << "Type the number of its dinosaur class (Carnivore - 0, Herbivore - 1, Water - 2, Flying - 3): ";
        CIN >> dinosaurClass;
    } 

    COUT << "Type the number of its food type (Grass - 0, Meat - 1, Fish - 2): ";
    CIN >> foodType;
    while (foodType < 0 || foodType > 2) {
        COUT << "Invalid number." << ENDL;
        COUT << "Type the number of its food type (Grass - 0, Meat - 1, Fish - 2): ";
        CIN >> foodType;
    }

    COUT << "Type the number of its era (Triassic - 0, Jurassic - 1, Cretaceous - 2): ";
    CIN >> era;
    while (era < 0 || era > 2) {
        COUT << "Invalid number." << ENDL;
        COUT << "Type the number of its era (Triassic - 0, Jurassic - 1, Cretaceous - 2): ";
        CIN >> era;
    }

    COUT << "Type how many food units will the dinosaur consume: ";
    CIN >> amountOfFood;

    Dinosaur* dinosaur = new Dinosaur(name, dinoType, (Gender)gender, (DinosaurClass)dinosaurClass, (FoodType)foodType, amountOfFood);

    for (int i = 0; i < this -> cages -> size(); i++) {
        Cage* cage = this -> cages -> get(i);
        if (cage -> getEra() == (Era)era && cage -> getDinosaurs() -> size() < cage -> getCageSize()) {
            COUT << "Dinosaur added successfully in cage with id: " << cage -> getId() << ENDL;
            cage -> getDinosaurs() -> pushBack(dinosaur);
            return;
        }
    }

    COUT << "No suitable cage found for this dinosaur. Let's create one.." << ENDL;
    int cageSize;
    char* climate;
    climate = new char[128];

    COUT << "Type the climate for the new cage (up to 64 characters): ";
    CIN.get();
    CIN.getline(climate, 128);
    while (strlen(climate) > 64) {
        COUT << "Climate too long." << ENDL;
        COUT << "Type the climate for the new cage (up to 64 characters): ";
        CIN.getline(climate, 128);
    }

    COUT << "Input the size of the cage (Small - 1, Medium - 3, Big - 10): ";
    CIN >> cageSize;
    while (cageSize != 1 && cageSize != 3 && cageSize != 10) {
        COUT << "Invalid cage size." << ENDL;
        COUT << "Input the size of the cage (Small - 1, Medium - 3, Big - 10): ";
        CIN >> cageSize;
    }

    Cage* cage = new Cage((CageSize)cageSize, climate, (Era)era);

    cage -> getDinosaurs() -> pushBack(dinosaur);
    this -> getCages() -> pushBack(cage);
    COUT << "Dinosaur added successfully in cage with id: " << cage -> getId() << ENDL;
}

/**
 * @brief Method that creates a new cage.
 * 
 */
void Zoo::createNewCage() {
    int cageSize, era;
    char* climate;
    climate = new char[128];

    COUT << "Type the climate for the new cage (up to 64 characters): ";
    CIN.getline(climate, 128);
    while (strlen(climate) > 64) {
        COUT << "Climate too long." << ENDL;
        COUT << "Type the climate for the new cage (up to 64 characters): ";
        CIN.getline(climate, 128);
    }

    COUT << "Input the size of the cage (Small - 1, Medium - 3, Big - 10): ";
    CIN >> cageSize;
    while (cageSize != 1 && cageSize != 3 && cageSize != 10) {
        COUT << "Invalid cage size." << ENDL;
        COUT << "Input the size of the cage (Small - 1, Medium - 3, Big - 10): ";
        CIN >> cageSize;
    }

    COUT << "Type the number of the cage's era (Triassic - 0, Jurassic - 1, Cretaceous - 2): ";
    CIN >> era;
    while (era < 0 || era > 2) {
        COUT << "Invalid number." << ENDL;
        COUT << "Type the number of the cage's era (Triassic - 0, Jurassic - 1, Cretaceous - 2): ";
        CIN >> era;
    }

    Cage* cage = new Cage((CageSize)cageSize, climate, (Era)era);
    this -> getCages() -> pushBack(cage);
    COUT << "Successfully created new cage with id: " << cage -> getId() << ENDL << ENDL;
}

/**
 * @brief Method that removes dinosaur from a cage.
 * 
 */
void Zoo::removeDinosaur() {
    COUT << "In which cage is the dinosaur that you want to remove? " << ENDL;
    bool anyDinosaurs = 0;
    int numberOfCages = this -> getCages() -> size();
    for (int i = 0; i < numberOfCages; i++) {
        Cage* cage = this -> getCages() -> get(i);
        if (cage -> getDinosaurs() -> size() > 0) {
            anyDinosaurs = 1;
            COUT << "-----------" << ENDL
            << "Cage id: " << cage -> getId() << ENDL
            << "Cage size: " << Util::cageSizeToString(cage -> getCageSize()) << ENDL
            << "Cage era: " << Util::eraToString(cage -> getEra()) << ENDL
            << "Number of Dinosaurs in the cage: " << cage -> getDinosaurs() -> size() << ENDL;
        }
    }
    if (!anyDinosaurs) {
        COUT << "There are not any dinosaurs in the zoo at the moment." << ENDL;
        return;
    }
    COUT << "-----------" << ENDL;
    COUT << "Type in the id of the cage that you want to remove dinosaur from: ";
    int id;
    CIN >> id;
    COUT << ENDL << ENDL;
    for (int i = 0; i < numberOfCages; i++) {
        if (this -> getCages() -> get(i) -> getId() == id && this -> getCages() -> get(i) -> getDinosaurs() -> size() > 0) {
            Cage* cage = this -> getCages() -> get(i);
            int numberOfDinosaurs = cage -> getDinosaurs() -> size();
            COUT << "Which dinosaur do you want to remove?" << ENDL;
            for (int j = 0; j < numberOfDinosaurs; j++) {
                Dinosaur* dinosaur = cage -> getDinosaurs() -> get(j);
                COUT << "----------" << ENDL
                << "Dinosaur id: " << dinosaur -> getId() << ENDL
                << "Dinosaur name: " << dinosaur -> getName() << ENDL
                << "Dinosaur type: " << dinosaur -> getDinoType() << ENDL
                << "Dinosaur gender: " << Util::genderToString(dinosaur -> getGender()) << ENDL
                << "Dinosaur class:" << Util::dinosaurClassToString(dinosaur -> getDinosaurClass()) << ENDL
                << "Dinosaur food type: " << Util::foodTypeToString(dinosaur -> getFoodType()) << ENDL
                << "Amount of food, eaten by this dino: " << dinosaur -> getAmountOfFood() << ENDL;
            }
            COUT << "-----------" << ENDL;
            COUT << "Type in the id of the dinosaur that you want to remove: ";
            int dinoId;
            CIN >> dinoId;
            for (int j = 0; j < numberOfDinosaurs; j++) {
                if (cage -> getDinosaurs() -> get(j) -> getId() == dinoId) {
                    cage -> setNeededAmountOfFood(cage -> getNeededAmountOfFood() - cage -> getDinosaurs() -> get(j) -> getAmountOfFood());
                    delete cage -> getDinosaurs() -> get(j);
                    cage -> getDinosaurs() -> remove(j);
                    COUT << "Dinosaur with id: " << dinoId << " successfully removed from the zoo." << ENDL << ENDL;
                    return;
                }
            }
            COUT << "Wrong dinosaur id." << ENDL << ENDL;
        }
    }
}

/**
 * @brief Method that displays information about all cages.
 * 
 */
void Zoo::showInfoAboutCages() {
    int numberOfCages = this -> getCages() -> size();
    for (int i = 0; i < numberOfCages; i++) {
        Cage* cage = this -> getCages() -> get(i);
        COUT << "-----------" << ENDL
        << "Cage id: " << cage -> getId() << ENDL
        << "Cage size: " << Util::cageSizeToString(cage -> getCageSize()) << ENDL
        << "Cage era: " << Util::eraToString(cage -> getEra()) << ENDL
        << "Number of Dinosaurs in the cage: " << cage -> getDinosaurs() -> size() << ENDL;
    }
    COUT << "-----------" << ENDL << ENDL;
}

/**
 * @brief Method that shows information about all dinosaurs in a given cage.
 * 
 * @param cageId - the id of the cage, which dinosaurs we want to see.
 */
void Zoo::showInfoAboutDinosaursInCage(int cageId) {
    int numberOfCages = this -> getCages() -> size();
    for (int i = 0; i < numberOfCages; i++) {
        if (this -> getCages() -> get(i) -> getId() == cageId) {
            Cage* cage = this -> getCages() -> get(i);
            int numberOfDinosaurs = cage -> getDinosaurs() -> size();
            for (int j = 0; j < numberOfDinosaurs; j++) {
                Dinosaur* dinosaur = cage -> getDinosaurs() -> get(j);
                COUT << "----------" << ENDL
                << "Dinosaur id: " << dinosaur -> getId() << ENDL
                << "Dinosaur name: " << dinosaur -> getName() << ENDL
                << "Dinosaur type: " << dinosaur -> getDinoType() << ENDL
                << "Dinosaur gender: " << Util::genderToString(dinosaur -> getGender()) << ENDL
                << "Dinosaur class:" << Util::dinosaurClassToString(dinosaur -> getDinosaurClass()) << ENDL
                << "Dinosaur food type: " << Util::foodTypeToString(dinosaur -> getFoodType()) << ENDL
                << "Amount of food, eaten by this dino: " << dinosaur -> getAmountOfFood() << ENDL;
            }
            COUT << "-----------" << ENDL << ENDL;
            return;
        }
    }
    COUT << "There is not a cage with such id." << ENDL << ENDL;
}

/**
 * @brief Method that loads storage with certain amount of units of food.
 * 
 * @param unitsOfFood - the amount of food.
 */
void Zoo::loadStorageWithFood(int unitsOfFood) {
    this -> setFoodAmount(this -> getFoodAmount() + unitsOfFood);
    COUT << ENDL;
}

Vector<Cage*>* Zoo::getCages() const {
    return this -> cages;
}

void Zoo::setCages(Vector<Cage*>* cages) {
    delete this -> cages;
    this -> cages = cages;
}

int Zoo::getFoodAmount() const {
    return this -> foodAmount;
}

void Zoo::setFoodAmount(const int foodAmount) {
    this -> foodAmount = foodAmount;
}

#endif
