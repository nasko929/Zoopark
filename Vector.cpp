#ifndef __VECTOR_CPP
#define __VECTOR_CPP

#include "Vector.h"

template<class T>
Vector<T>::Vector() {
    this -> arr = new T[1];
    this -> current = 0;
    this -> maxSize = 1;
}

template<class T>
Vector<T>::~Vector() {
    delete [] arr;
}

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

template<class T>
int Vector<T>::size() {
    return this -> current;
}

template<class T>
T Vector<T>::get(int i) {
    if (i < current) {
        return arr[i];
    }
    return arr[0];
}

template<class T>
void Vector<T>::set(T obj, int i) {
    if (i < current) {
        arr[i] = obj;
    }
}

template<class T>
void Vector<T>::remove(int index) {
    if (index < current) {
        for (; index < current - 1; index ++) {
            arr[index] = arr[index + 1];
        }
        current --;
    }
}

template<class T>
void Vector<T>::pop() {
    if (current > 0) {
        current--;
    }
}

#endif