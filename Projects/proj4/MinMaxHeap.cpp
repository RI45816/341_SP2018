/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*****************************************
 ** File:    MinMaxHeap.cpp
 ** Project: CMSC 341 proj4, Spring 2018
 ** Author:  Uzoma Uwanamodo
 ** Date:    05/04/2018
 ** E-mail:  uu3@umbc.edu
 ** 
 ** This file contains the definition for the MinMaxHeap class.
 ** 
 ** 
 ** 
 ** 
 *********************************************/
#ifndef MINMAXHEAP_CPP
#define MINMAXHEAP_CPP


#include <iostream>
#include <sstream>
#include <stdexcept>
#include "MinMaxHeap.h"

using namespace std;

template <typename T>
int MinMaxHeap<T>::debug_count = 0;
/*
 *  Method: MinMaxHeap<T>::MinMaxHeap()
 *   Descr: Default constructor for MinMaxHeap
 */
template <typename T>
MinMaxHeap<T>::MinMaxHeap(int capacity) : m_size(0),m_capacity(capacity) {
    // cout << debug_count++ << endl;
    m_heaps[MAX] = new Heap(capacity, greaterThan);
    m_heaps[MIN] = new Heap(capacity, lesserThan);
    for (int i = 0;i<TWIN;i++)
        m_heaps[i]->setTwin(m_heaps[i^1]);
}

/*
 *  Method: MinMaxHeap<T>::MinMaxHeap()
 *   Descr: Copy constructor for MinMaxHeap
 */
template <typename T>
MinMaxHeap<T>::MinMaxHeap(const MinMaxHeap<T>& other) : m_capacity(other.m_capacity), m_size(other.m_size) {
    m_heaps[MAX]=new Heap(*other.m_heaps[MAX]);
    m_heaps[MIN] = new Heap(*other.m_heaps[MIN]);
    for (int i = 0; i < TWIN; i++)
        m_heaps[i]->setTwin(m_heaps[i^1]);

}

/*
 *  Method: MinMaxHeap<T>::operator=()
 *   Descr: Overloaded assignment operator for MinMaxHeap
 */
template <typename T>
const MinMaxHeap<T> & MinMaxHeap<T>::operator=(const MinMaxHeap<T> &rhs) {
    m_capacity = rhs.m_capacity;
    m_size = rhs.m_size;

    *m_heaps[MIN] = *rhs.m_heaps[MIN];
    *m_heaps[MAX] = *rhs.m_heaps[MAX];
    for (int i = 0; i < TWIN; i++)
        m_heaps[i]->setTwin(m_heaps[i^1]);

    return *this;
}

/*
 *  Method: MinMaxHeap<T>::MinMaxHeap()
 *   Descr: Destructor method for MinMaxHeap
 */
template <typename T>
MinMaxHeap<T>::~MinMaxHeap() {
    m_heaps[MIN]->setTwin(0);
    m_heaps[MAX]->setTwin(0);
    
    
    delete m_heaps[MIN];
    delete m_heaps[MAX];
    m_heaps[MIN]=0;
    m_heaps[MAX]=0;
    
//    delete [] m_heaps;
}

/*------------------------------------------------------------------------------*/

/*
 *  Method: MinMaxHeap::Heap::Heap()
 *   Descr: Constructor for Heap
 */
template <typename T>
 MinMaxHeap<T>::Heap::Heap(int capacity, itemCompare compare) : m_compare(compare), m_elements(new HeapItem<T> * [1 << (this->findMSBSet(capacity))]), m_capacity(capacity), m_size(0) {
}

template <typename T>
MinMaxHeap<T>::Heap::Heap(const Heap& other) : m_compare(other.m_compare), m_elements(new HeapItem<T> * [1 << (this->findMSBSet(other.m_capacity))]), m_capacity(other.m_capacity),m_size(other.m_size) {
    for (int i = 1; i <= other.m_size; i++)
    m_elements[i]=new HeapItem<T>(*other.m_elements[i]);
}

template <typename T>
const  typename MinMaxHeap<T>::Heap& MinMaxHeap<T>::Heap::operator=(const Heap& rhs) {
    m_compare = rhs.m_compare;
    m_capacity = rhs.m_capacity;
    HeapItem<T> ** elements = new HeapItem<T> * [1 << (this->findMSBSet(m_capacity))];
    for (int i = 1; i <= m_size; i++) delete m_elements[i];
    delete [] m_elements;
    m_size = rhs.m_size;
    for (int i = 1; i <= m_size; i++) {
        elements[i] = new HeapItem<T>(*rhs.m_elements[i]);
    }

    m_elements = elements;
    return *this;
}

template <typename T>
MinMaxHeap<T>::Heap::~Heap() {
    for (int i = 1; i<=m_size; i++) {
        delete m_elements[i];
        m_elements[i] = 0;
    }
    
    delete [] m_elements;
    
    m_compare = 0;
}



/*
 *  Method: MinMaxHeap::Heap::dump()
 *   Descr: Print out all the items in the heap
 */
template <typename T>
void MinMaxHeap<T>::Heap::dump() {
    for (int i=1; i<=m_size; i++)
    cout << "Heap["<< i << "] = ("<< m_elements[i]->m_item << ","<< m_elements[i]->m_twinIndex << ")" << endl;
}

/*
 *  Method: MinMaxHeap::Heap::insert()
 *   Descr: Insert an item into the heap
 */
template <typename T>
void MinMaxHeap<T>::Heap::insert(const T &data) {
    static int i;
    if (!m_size) i = 0;
    // cout << debug_count++ << endl;
    m_elements[++m_size] = new HeapItem<T>(data, (m_size+1>m_twin->m_size || !i) ? m_size+1 : i);
    if (m_size == 1) return;
    
    // Percolate up
    for (i = m_size; i>1 && m_compare(m_elements[i],m_elements[i>>1]);i>>=1) swap(m_elements[i],m_elements[i>>1],i,i>>1);
    // cout << debug_count++ << endl;
}

/*
 *  Method: MinMaxHeap::Heap::swap()
 *   Descr: Take two variables and switch them
 */
template <typename T>
void MinMaxHeap<T>::Heap::swap(HeapItem<T> * hi1, HeapItem<T>  * hi2, int index,int index2) {
    // cout << debug_count++ << endl; 

    HeapItem<T> hi3 = *hi1;
    
    // Swap the index in the heap so they keep track of each other
    m_twin->m_elements[hi2->m_twinIndex]->m_twinIndex = index;
    if (m_size==m_twin->m_size) 
    m_twin->m_elements[hi1->m_twinIndex]->m_twinIndex = index2;
    *hi1 = *hi2;
    *hi2 = hi3;
}

/*
 *  Method: MinMaxHeap::Heap::at()
 *   Descr: Retrieve heap item at pos
 */
template <typename T>
HeapItem<T> & MinMaxHeap<T>::Heap::at(int pos) {
    return *m_elements[pos];
}

/*
 *  Method: MinMaxHeap::getElements()
 *   Descr: Retrieve the item and its index in the twin heap
 */
template <typename T>
void MinMaxHeap<T>::Heap::getElement(int pos, T& data, int &index) {
    data = m_elements[pos]->m_item;
    index = m_elements[pos]->m_twinIndex;
}



/*
 *  Method: MinMaxHeap::Heap::compareItems()
 *   Descr: Get the min or max of the two items depending on function in m_compare
 */
template <typename T>
HeapItem<T> * MinMaxHeap<T>::Heap::compareItems(int index1, int index2,int &finalIndex) {
    // cout << debug_count++ << endl;
    HeapItem<T> * hi1 = m_elements[index1], * hi2 = m_elements[index2];
    if (!hi2 || m_compare(hi1, hi2)) {
        finalIndex = index1;
        return hi1;
    } else {
        finalIndex = index2;
        return hi2;
    }
}
/*
 *  Method: MinMaxHeap::Heap::deleteFirstItem()
 *   Descr: Delete and return the first item from the MinMaxHeap
 */
template <typename T>
T MinMaxHeap<T>::Heap::deleteItem(int index) {
    if (m_size) {
        HeapItem<T> * swappedItem = m_elements[index], * removedItem = m_elements[m_size];
        if (index != m_size) swap(swappedItem, removedItem, index, m_size);
        m_elements[m_size] = 0;

        // Percolate down
        if (index != 1) m_size--;
        for (int i = index, j = 0; i <= (m_size - 1) >> 1 && m_compare(compareItems(i << 1, (i << 1) + 1, j), m_elements[i]); i = j) swap(m_elements[i], m_elements[j], i, j);

        if (index != 1 && index != m_size+1)
            for (int i = index; i > 1 && m_compare(m_elements[i], m_elements[i >> 1]); i >>= 1) swap(m_elements[i], m_elements[i >> 1], i, i >> 1);

        if (index == 1) {
            m_size--;
            if (removedItem->m_twinIndex <= m_twin->m_size)
                m_twin->deleteItem(removedItem->m_twinIndex);
        }
        T t = removedItem->m_item;
        delete removedItem;
        return t;
        
    } else
        throw out_of_range("There are no more items in the list");
}


 /* 
  *  Method: MinMaxHeap::Heap::setTwin()
  *  Descr: Give heap a pointer to its twin
 */
template <typename T>
void MinMaxHeap<T>::Heap::setTwin(Heap* twin) {
    m_twin = twin;    
}

/*
 *  Method: MinMaxHeap::size()
 *   Descr: Return number of elements in heap
 */
template <typename T>
int MinMaxHeap<T>::size() {
    return m_size;
}

/*
 *  Method: MinMaxHeap::insert()
 *   Descr: Insert an item into the heaps
 */
template <typename T>
void MinMaxHeap<T>::insert(const T &data) {
    if(m_size++ == m_capacity)
        throw out_of_range("The heap has reached its capacity");
    for (int i = 0;i<TWIN;i++)
        m_heaps[i]->insert(data);
}

/*
 *  Method: MinMaxHeap::deleteMin()
 *   Descr: Delete the smallest item from both heaps
 */
template <typename T>
T MinMaxHeap<T>::deleteMin() {
    if (m_size--)
        return m_heaps[MIN]->deleteItem(1);
    else
        throw out_of_range("The heap...it's empty");
}

/*
 *  Method: MinMaxHeap::deleteMax()
 *   Descr: Delete the largest item from both heaps
 */
template <typename T>
T MinMaxHeap<T>::deleteMax() {
    if (m_size--)
        return m_heaps[MAX]->deleteItem(1);
    else
        throw out_of_range("The heap...it's empty");
}

/*
 *  Method: MinMaxHeap::dump()
 *   Descr: Print out the contents of the twin heaps
 */
template <typename T>
void MinMaxHeap<T>::dump() {
    // cout << debug_count++ << endl;
    cout << "\n... MinMaxHeap::dump() ..." << endl << endl;
cout << "------------Min Heap------------" << endl;
cout << "size = " << m_size << ", capacity = " << m_capacity << endl;
m_heaps[MIN]->dump();
cout << "\n------------Max Heap------------" << endl;
cout << "size = " << m_size << ", capacity = " << m_capacity << endl;
m_heaps[MAX]->dump();
cout << "--------------------------------" << endl << endl;


}

/*
 *  Method: MinMaxHeap::locateMin()
 *   Descr: Locate the item in the min Heap and its index in the max Heap
 */
template <typename T>
void MinMaxHeap<T>::locateMin(int pos, T &data, int &index) {
    m_heaps[MIN]->getElement(pos,data,index);
}

/*
 *  Method: MinMaxHeap::locateMax()
 *   Descr: Locate the item in the max Heap and its index in the min Heap
 */
template <typename T>
void MinMaxHeap<T>::locateMax(int pos, T &data, int &index) {
    m_heaps[MAX]->getElement(pos,data,index);
}


/*------------------------------------------------------------------------------*/

// Determine most significant bit

template <typename T>
unsigned int MinMaxHeap<T>::Heap::findMSBSet(unsigned int pattern) {
    int bit = 0;
    if (pattern) {
        // Do binary search for highest-order differing bit
        for (int i = 16; i; i >>= 1) {
            if (pattern >> bit + i) bit += i;
        }
        bit++; // this maps to range 1..32
    }
    return bit;
}


/*------------------------------------------------------------------------------*/


// Determines whether or not the first item is greater than the second

template <typename T>
bool greaterThan(HeapItem<T> * hi1, HeapItem<T> * hi2) {
    return hi1->m_item > hi2->m_item;
}

// Determines whether or not the first item is less than the second

template <typename T>
bool lesserThan(HeapItem<T> * hi1, HeapItem<T> * hi2) {
    return hi1->m_item <= hi2->m_item;
}

#endif  // MINMAXHEAP_CPP