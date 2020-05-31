#ifndef __READ_RESULT_H
#define __READ_RESULT_H

/**
 * @brief A struct that is used when reading the data from the file.
 * 
 * This struct is needed so that it provides information about the just-read
 * value from the buffer that we read from the input file.
 * The field nextIndex is referring to the start index of the next word to read.
 */
struct ReadResult {
    char* string;
    int number;
    int nextIndex;
};

#endif