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


//constructor
template<class T>
Array<T>::Array(int sz){
    assert(sz>=0);
    size=sz;
    list=new T[size];
}

//deconstructor
template<class T>
Array<T>::~Array(){
    delete []list;
}

//copy constructor, deep copy
template<class T>
Array<T>::Array(const Array<T>&a){
    size=a.size;
    list=new T[size];
    for(int i=0;i<size;++i){
        list[i]=a.list[i];
    }
}

//operand overload "="
template<class T>
Array<T>& Array<T>::operator=(const Array<T>& rhs){
    if(&rhs!=this){
        return *this;
    }
    if(size!=rhs.size){
        delete[] list;
        size=rhs.size;
        list=new T[size];
    }
    for(int i=0;i<size;++i){
        list[i]=rhs.list[i];
    }
}

//operand overload "[]"
template<class T>
T& Array<T>::operator[](int n){
    assert(n>=0 && n<size);
    return list[n];
}

template<class T>
const T& Array<T>::operator[](int n)const{
    assert(n>=0 && n<size);
    return list[n];
}

//conversion to T* so it could function like C-style array
//T* points to T* list in this class
template<class T>
Array<T>::operator T*(){
    return list;
}

template<class T>
Array<T>::operator const T*()const{
    return list;
}

//return size of this array
template<class T>
int Array<T>::getSize() const{
    return size;
}

//modify array size to sz
template<class T>
void Array<T>::resize(int sz){
    assert(sz>=0);
    if(sz==size){
        return;
    }
    T* newList=new T[sz];
    int n=(sz<size)?sz:size;
    for(int i=0;i<n;++i){
        newList[i]=list[i];
    }
    delete[] list;
    list=newList;
    size=sz;
}


#endif //Array.h