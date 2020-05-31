#ifndef __VECTOR_CPP
#define __VECTOR_CPP

#include "Vector.h"

/**
 * @brief Construct a new Vector< T>:: Vector object
 */
template<class T>
Vector<T>::Vector() {
    this -> arr = new T[1];
    this -> current = 0;
    this -> maxSize = 1;
}

/**
 * @brief Destroy the Vector< T>:: Vector object
 */
template<class T>
Vector<T>::~Vector() {
    delete [] arr;
}

/**
 * @brief - Method that adds object to the end of the vector.
 * 
 * @param obj - object to be added.
 */
template<class T>
void Vector<T>::pushBack(T obj) {
    if (this -> current == this -> maxSize - 1) {
        T* newArr = new T[maxSize * 2];
        for (int i = 0; i < this -> current; i++) {
            newArr[i] = arr[i];
        }
        delete [] arr;
        maxSize *= 2;
        arr = newArr;
    }
    this -> arr[current++] = obj;
}

/**
 * @brief Method that returns the current size of the vector.
 */
template<class T>
int Vector<T>::size() {
    return this -> current;
}

/**
 * @brief Method that returns an object at specific index.
 * 
 * @param i - the specific index.
 * @return T - the object at index i, if i is in range. Otherwise, the first object in the vector.
 */
template<class T>
T Vector<T>::get(int i) {
    if (i < current) {
        return arr[i];
    }
    return arr[0];
}

/**
 * @brief Method that sets an object at specific index.
 *
 * @param obj - the object to be set.
 * @param i - the specific index for the object to be set.
 */
template<class T>
void Vector<T>::set(T obj, int i) {
    if (i < current) {
        arr[i] = obj;
    }
}

/**
 * @brief Method that removes an object at specific index.
 * 
 * @param i - the specific index to be removed from the vector.
 */
template<class T>
void Vector<T>::remove(int i) {
    if (i < current) {
        for (; i < current - 1; i ++) {
            arr[i] = arr[i + 1];
        }
        current--;
    }
}

/**
 * @brief Method that removes the last element of the vector.
 */
template<class T>
void Vector<T>::pop() {
    if (current > 0) {
        current--;
    }
}

#endif