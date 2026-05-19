//Page 355, chapter 9.2.2
//Array.h
#ifndef ARRAY_H
#define ARRAY_H
#include<cassert>

template<class T>
class Array{
    private:
        T* list;//head addr
        int size;
    public:
        Array(int sz=50);
        Array(const Array<T>&a);//copy constructor
        ~Array();
        Array<T>& operator=(const Array<T>&rhs);
        T& operator[](int i);
        const T& operator[](int i)const;
        operator T*();
        operator const T*()const;
        int getSize() const;
        void resize(int sz);
};


#endif //Array.h