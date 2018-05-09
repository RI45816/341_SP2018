/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*****************************************
 ** File:    MinMaxHeap.h
 ** Project: CMSC 341 proj4, Spring 2017
 ** Author:  Uzoma Uwanamodo
 ** Date:    05/04/2018
 ** E-mail:  uu3@umbc.edu
 ** 
 ** This file contains the header for the MinMaxHeap class.
 ** 
 ** 
 ** 
 ** 
 *********************************************/

#ifndef MINMAXHEAP_H
#define MINMAXHEAP_H


#define TWIN 2

enum {MIN,MAX};

template<typename T>
struct HeapItem {
    int m_twinIndex; // Store index of twin item in other heap
    T m_item; // The actual item being stored

    HeapItem(){}
    
    HeapItem(T item, int index) : m_item(item), m_twinIndex(index) {
    }


} ;

template<typename T>
class MinMaxHeap {
public:

    typedef bool (*itemCompare)(HeapItem<T>*,HeapItem<T>*);
class Heap {
    public:
        // Constructor for Heap
        Heap(int capacity, itemCompare compare);

        // Default Constructor for Heap
        Heap();
        
        // prints out the contents of the heap including the positions of each key in the min-heap and the max-heap along with recorded position of its "twin"
        void dump();

        // adds the item given in the parameter to the heap
        void insert(const T& data);

        // deletes item at index in the heap, its twin in the twin heap, and returns the item
        T deleteItem(int index);

        HeapItem<T>& at(int pos);

        // swaps two elements within a heap
        void swap(HeapItem<T> * hi1, HeapItem<T> * hi2, int index, int index2);

        // determines which item should be compared while percolating down
        HeapItem<T> * compareItems(int index1, int index2, int &finalIndex);

        // Give heap access to its twin
        void setTwin(Heap* twin);

        // Determine most significant bit
        unsigned int findMSBSet(unsigned int pattern);

        // Retrieve heap item at index
        void getElement(int pos, T &data, int &index);


        // overloaded assignment operator
        const Heap& operator=(const Heap& rhs);

        // copy constructor
        Heap(const Heap& other);

        // destructor
        ~Heap();


    private:
        HeapItem<T> ** m_elements; // Store the elements
        Heap * m_twin; // The min (or max) heap's twin heap
        itemCompare m_compare; // Comparison function to be used to sort heap
        int m_size; // Current size of heap
        int m_capacity; // Maximum size of heap
    } ;
    // default constructor
    MinMaxHeap(int capacity);

    // copy constructor
    MinMaxHeap(const MinMaxHeap<T>& other);

    // overloaded assignment operator
    const MinMaxHeap<T>& operator=(const MinMaxHeap<T>& rhs);

    // destructor
    ~MinMaxHeap();

    // returns the number of items in the min-max heap
    int size();

    // adds the item given in the parameter to the min-max heap
    void insert(const T& data);

    // removes the smallest item in the min-max heap and returns the key value of the deleted item
    T deleteMin();

    // removes the largest item in the min-max heap and returns the key value of the deleted item
    T deleteMax();

    // prints out the contents of the min-max heap including the positions of each key in the min-heap and the max-heap along with recorded position of its "twin"
    void dump();

    // Retrieve the item at the requested pos and its index in the twin heap
    void locateMin(int pos, T& data, int& index);

    // Retrieve the item at the requested pos and its index in the twin heap
    void locateMax(int pos, T& data, int& index);
    


private:
    Heap * m_heaps[TWIN]; // Store the heaps
    int m_size; // Current size of the heap
    int m_capacity; // Maximum amount of items heap can store
    static int debug_count;

};

    
    // Determines whether or not the first item is greater than the second
    template <typename T>
    bool greaterThan(HeapItem<T> * hi1, HeapItem<T> * hi2);
    
    // Determines whether or not the first item is less than the second
    template <typename T>
    bool lesserThan(HeapItem<T> * hi1, HeapItem<T> * hi2);
    
    

#include "MinMaxHeap.cpp"
#endif /* MINMAXHEAP_H */