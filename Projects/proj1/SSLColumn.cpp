/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*****************************************
 ** File:    SSLColumn.cpp
 ** Project: CMSC 341 proj1, Spring 2018
 ** Author:  Uzoma Uwanamodo
 ** Date:    02/26/2018
 ** E-mail:  uu3@umbc.edu
 ** 
 ** This file contains the definition for the SSLColumn class.
 ** 
 ** 
 ** 
 ** 
 *********************************************/

#include <iostream>
#include "SSLColumn.h"

using std::endl;
using std::cout;

/*
 *  Method: SSLColumn::SSLColumn()
 *   Descr: Initialize SSLColumn and create circular buffer array
 */
SSLColumn::SSLColumn(int n) : m_capacity(n), m_size(0), m_start(0), m_end(0) {
    m_data = new int[m_capacity];

}


/*
 *  Method: SSLColumn::SSLColumn()
 *   Descr: Copy constructor for SSLColumn
 */
SSLColumn::SSLColumn(const SSLColumn &other) : m_capacity(other.m_capacity), m_size(other.m_size), m_start(other.m_start), m_end(other.m_end) {
    m_data = new int[m_capacity];
    for (int i = 0; i < m_capacity; i++)
        m_data[i] = other.m_data[i];

}


/*
 *  Method: SSLColumn::~SSLColumn()
 *   Descr: Deconstructer method for SSLColumn
 */
SSLColumn::~SSLColumn()
{
    delete m_data;
}

/*
 *  Method: SSLColumn::operator=()
 *   Descr: Equivalence operator for SSLColumn
 */
const SSLColumn & SSLColumn::operator=(const SSLColumn &rhs) {

    // Resize array if necessary
    if (m_capacity < rhs.m_capacity) {
        m_capacity = rhs.m_capacity;
        m_data = new int[m_capacity];
    }

    // Initialize variables based on rhs
    m_size = rhs.m_size;
    m_start = 0;
    m_end = m_size % m_capacity;

    // Copy all values from other array
    for (int i = 0; i < m_size; i++)
        m_data[i] = rhs.m_data[(rhs.m_start + i) % rhs.m_capacity];

    return *this;
}


/*
 *  Method: SSLColumn::add()
 *   Descr: 
 */
void SSLColumn::add(int data) {
    
    // Throw exception if the array is full
    if (m_size == m_capacity)
        throw std::overflow_error("add: column full");

    
    int insertIndex = m_size ? findNearest(data) : 0; // Find the point of insertion for the array
    
    if (insertIndex == 0)
        addFirst(data);
    else if (insertIndex == m_capacity - 1)
        addLast(data);
    else {
        for (int i = m_size; i > insertIndex; i--)
            m_data[bufferIndex(i)] = findAt(i - 1);
        m_data[bufferIndex(insertIndex)] = data;
        m_end = bufferIndex(++m_size);
    }
}


/*
 *  Method: SSLColumn::addFirst()
 *   Descr: Add a value to the beginning of the column
 */
void SSLColumn::addFirst(int data) {
    // Throw exception if the array is full
    if (m_size == m_capacity)
        throw std::overflow_error("addFirst: column full");

    // If the array is empty, increment m_end, otherwise, decrement m_start
    if (m_size) {
        m_start = (m_start + m_capacity - 1) % m_capacity;
        m_size++;
    } else
        m_end = bufferIndex(++m_size);
    m_data[m_start] = data;
}


/*
 *  Method: SSLColumn::addLast()
 *   Descr: Add a value to the end of the column
 */
void SSLColumn::addLast(int data) {
    // Throw exception if the array is full
    if (m_size == m_capacity)
        throw std::overflow_error("addLast: column full");

    m_data[m_end] = data;
    m_end = bufferIndex(++m_size);

}


/*
 *  Method: SSLColumn::find()
 *   Descr: return the index of the specified value, or -1 if not found
 */
int SSLColumn::find(int data) {
    int pos = m_size / 2;

    // loop through array to execute binary search
    // minIndex  the lower bound of the array to check
    // maxIndex the upper bound of the array to check
    // curValue the value at the current position in array
    for (int minIndex = 0, maxIndex = m_size, curValue = findAt(pos); curValue != data; pos = minIndex + (maxIndex - minIndex) / 2, curValue = findAt(pos)) {
        if (minIndex == maxIndex || ((pos == minIndex) && (minIndex == maxIndex - 1)))
            return -1;
        if (curValue > data)
            maxIndex = pos;
        else
            minIndex = pos;
    }

    return pos;
}    

/*
 *  Method: SSLColumn::findNearest()
 *   Descr: return the index of the specified value, or the index of the nearest value if not found
 */
int SSLColumn::findNearest(int data) {
    int pos = m_size / 2;

    // loop through array to execute binary search
    // minIndex  the lower bound of the array to check
    // maxIndex the upper bound of the array to check
    // curValue the value at the current position in array
    for (int minIndex = 0, maxIndex = m_size, curValue = findAt(pos); curValue != data; pos = minIndex + (maxIndex - minIndex) / 2, curValue = findAt(pos)) {
        
        if (minIndex == maxIndex || ((pos == minIndex) && (minIndex == maxIndex - 1)))
            return data <= curValue ? minIndex : maxIndex;
        if (curValue > data)
            maxIndex = pos;
        else
            minIndex = pos;
    }

    return pos;

}

/*
 *  Method: SSLColumn::findAt()
 *   Descr: Return the value at the specified index of the array, with -1 pointing to the end of the array
 */
int SSLColumn::findAt(int pos) {

    // Throw range error if requested index is out of bounds
    if (pos >= m_size || pos < -1)
        throw std::range_error("findAt: bad position");
    
    else
        return m_data[bufferIndex(~pos ? pos : m_size - 1)];
}

/*
 *  Method: SSLColumn::bufferIndex()
 *  Descr: Take a regular 0-based index and return the correspondingf index in the buffer
 */
int SSLColumn::bufferIndex(int index) {
    return (m_start + index) % m_capacity;
}

/*
 *  Method: SSLColumn::remove()
 *   Descr: 
 */
int SSLColumn::remove(int data) {
    int deleteIndex = find(data); // Get the index to delete
    // 
    if (deleteIndex == 0)
        removeFirst();
    else if (deleteIndex == m_capacity - 1)
        removeLast();
    else if (deleteIndex == -1)
        return -1;
    else {
        for (int i = deleteIndex; i < m_size - 1; i++)
            m_data[bufferIndex(i)] = findAt(i + 1);
        m_end = bufferIndex(--m_size);
    }


    return deleteIndex;
}


/*
 *  Method: SSLColumn::removeFirst()
 *   Descr: 
 */
int SSLColumn::removeFirst(void)
{
    // Throw exception if the array is empty
    if (!m_size)
       throw  std::underflow_error("removeFirst: column empty");

    // Adjust start indicator
    m_start = (m_start + 1) % m_capacity;
    m_size--;
    
    return findAt(0);
}


/*
 *  Method: SSLColumn::removeLast()
 *   Descr: 
 */
int SSLColumn::removeLast(void)
{
    // Throw exception if the array is empty
    if (!m_size)
       throw std::underflow_error("removeLast: column empty");
    
    m_end = bufferIndex(--m_size);
    
    return findAt(-1);
}

/*
 *  Method: SSLColumn::capacity()
 *   Descr: return the capacity of array
 */
int SSLColumn::capacity()
{
    return m_capacity;
}


/*
 *  Method: SSLColumn::size()
 *   Descr: return the number of elements in the array
 */
int SSLColumn::size()
{
    return m_size;
}


/*
 *  Method: SSLColumn::dump()
 *   Descr: 
 */
void SSLColumn::dump() {
    cout << "SSLColumn::dump(): m_size = " << m_size << endl;
    for (int i = 0; i < m_size; i++)
        cout << "[" << bufferIndex(i) << "] " << findAt(i) << ", ";
    cout << endl;
}




