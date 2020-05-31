#include <iostream>
#include <fstream>
#include "Zoo.cpp"
#include "Vector.cpp"
#include "Era.h"
#include "Cage.cpp"
#include "Dinosaur.cpp"
#include <ctime>
#define COUT std::cout
#define CIN std::cin
#define ENDL "\n"

int main() {

    Zoo* zoo = new Zoo;
    int command;
    do {
        COUT << "Welcome to your Zoo." << ENDL;
        COUT << "Menu:" << ENDL
        << "1) Create new dinosaur" << ENDL
        << "2) Remove dinosaur" << ENDL
        << "3) Create new cage" << ENDL
        << "4) Load the storage with more units of food" << ENDL
        << "5) See information about all cages" << ENDL
        << "6) See information about all dinosaurs in a cage" << ENDL
        << "7) Exit"
        << ENDL
        << "You can choose (from 1 to 7): ";
        CIN >> command;
        switch(command) {
            case 1:
                zoo -> addNewDinosaur();
                break;
            case 2:
                zoo -> removeDinosaur();
                break;
            case 3:
                zoo -> createNewCage();
                break;
            case 4:
                int unitsOfFood;
                COUT << "Input the number of units of food you want to add to the zoo: ";
                CIN >> unitsOfFood;
                zoo -> loadStorageWithFood(unitsOfFood);
                break;
            case 5:
                zoo -> showInfoAboutCages();
                break;
            case 6:
                int cageId;
                COUT << "Input the id of the cage that you want to see the dinosaurs in: ";
                CIN >> cageId;
                zoo -> showInfoAboutDinosaursInCage(cageId);
                break;
            default:
                break;
        }
    } while (command != 7);

    time_t now = time(nullptr);

    std::ofstream outputFile("information.txt", std::ios::out);

    outputFile << now << ENDL;
    outputFile << zoo -> getFoodAmount() << ENDL;
    int numberOfCages = zoo -> getCages() -> size();
    outputFile << numberOfCages << ENDL;
    for (int i = 0; i < numberOfCages; i++) {
        Cage* cage = zoo -> getCages() -> get(i);
        outputFile << cage -> getCageSize() << ENDL;
        outputFile << cage -> getClimate() << ENDL;
        outputFile << cage -> getEra() << ENDL;
        int numberOfDinosaurs = cage -> getDinosaurs() -> size();
        outputFile << numberOfDinosaurs << ENDL;
        for (int j = 0; j < numberOfDinosaurs; j++) {
            Dinosaur* dinosaur = cage -> getDinosaurs() -> get(j);
            outputFile << dinosaur -> getName() << ENDL;
            outputFile << dinosaur -> getDinoType() << ENDL;
            outputFile << dinosaur -> getGender() << ENDL;
            outputFile << dinosaur -> getDinosaurClass() << ENDL;
            outputFile << dinosaur -> getFoodType() << ENDL;
            outputFile << dinosaur -> getAmountOfFood() << ENDL;
        }
    }
    outputFile << "END" << ENDL;
    outputFile.close();
    return 0;
}