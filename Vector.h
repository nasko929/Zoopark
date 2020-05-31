#ifndef __VECTOR_H
#define __VECTOR_H

template <class T>
class Vector {

private:
    T* arr;
    int current;
    int maxSize;
public:
    Vector();
    // Vector(const Vector&);
    // Vector& operator=(const Vector&);
    ~Vector();
    void pushBack(T);
    T get(int);
    void set(T, int);
    void remove(int);
    void pop();
    int size();
};

#endif