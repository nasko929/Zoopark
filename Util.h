#ifndef __UTIL_H
#define __UTIL_H

#include "Era.h"
#include "CageSize.h"
#include "DinosaurClass.h"
#include "FoodType.h"
#include "Gender.h"
#include "ReadResult.h"

/**
 * @brief A util class.
 * 
 * This class is making the code more clear as it divides the not so good-looking logic into separate class.
 */
class Util {

public:
    static ReadResult readInt(char*, int);
    static ReadResult readString(char*, int);
    static const char* eraToString(Era);
    static const char* cageSizeToString(CageSize);
    static const char* dinosaurClassToString(DinosaurClass);
    static const char* foodTypeToString(FoodType);
    static const char* genderToString(Gender);
};

#endif