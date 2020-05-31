#ifndef __VECTOR_H
#define __VECTOR_H

/**
 * @brief A template class that is representing the C++ vector<T>.
 * 
 * @tparam T - type of objects to put in the vector.
 */
template <class T>
class Vector {

private:
    T* arr;
    int current;
    int maxSize;
public:
    Vector();
    ~Vector();
    void pushBack(T);
    T get(int);
    void set(T, int);
    void remove(int);
    void pop();
    int size();
};

#endif