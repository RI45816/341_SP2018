/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*****************************************
 ** File:    SortedSquareList.cpp
 ** Project: CMSC 341 proj1, Spring 2018
 ** Author:  Uzoma Uwanamodo
 ** Date:    02/26/2018
 ** E-mail:  uu3@umbc.edu
 ** 
 ** This file contains the definition for the SortedSquareList class.
 ** 
 ** 
 ** 
 ** 
 *********************************************/

#include <iostream>
#include "SortedSquareList.h"
#include <math.h>
#include <stdexcept>

using namespace std;

/*
 *  Method: SortedSquareList::SortedSquareList()
 *   Descr: Default constructor for SortedSquareList
 */
SortedSquareList::SortedSquareList() : m_capacity(2), m_size(0), m_start(0), m_end(0) {
    m_cols = new SSLColumn * [m_capacity];
    m_colInfo = new int[m_capacity * 2 + 1]; // Stores highest number and series of size of columns

    // Initiailize m_cols
    for (int i = 0; i < m_capacity; i++)
        m_cols[i] = new SSLColumn(m_capacity);

    // Initialize m_colInfo
    for (int i = 0; i < m_capacity * 2 + 1; i++)
        m_colInfo[i] = 0;
}


/*
 *  Method: SortedSquareList::Sorted)List()
 *   Descr: Copy constructor for SortedSquareList
 */
SortedSquareList::SortedSquareList(const SortedSquareList &other) : m_capacity(other.m_capacity), m_size(other.m_size), m_start(other.m_start), m_end(other.m_end) {
    for (int i = 0; i < m_capacity; i++) {
        m_cols = new SSLColumn * [m_capacity]; // Array of pointers to SSLColumn
        m_colInfo = new int [m_capacity * 2 + 1]; // Stores highest number and series of size of columns

        // Initiailize m_cols
        for (int i = 0; i < m_capacity; i++)
            m_cols[i] = new SSLColumn(m_capacity);

        // Initialize m_colInfo
        for (int i = 0; i < m_capacity * 2 + 1; i++)
            m_colInfo[i] = 0;

        // Transfer existing data to new arrays
        for (int i = 0; i < m_capacity; i++)
            m_cols[i] = new SSLColumn(*other.m_cols[i]);

        for (int i = 0; i < m_capacity + 1; i++)
            m_colInfo[i] = other.m_colInfo[i];
    }
}


/*
 *  Method: SortedSquareList::~SortedSquareList()
 *   Descr: 
 */
SortedSquareList::~SortedSquareList()
{
    delete [] m_colInfo;
    for (int i=0;i<m_capacity;i++)
        delete m_cols[i];
    delete [] m_cols;
}




/*
 *  Method: SortedSquareList::operator=()
 *   Descr: 
 */
const SortedSquareList & SortedSquareList::operator=(const SortedSquareList &rhs) {
        
    int capacity = rhs.m_colInfo[rhs.m_capacity*2] > size() ? rhs.m_colInfo[rhs.m_capacity*2] : size();
    
    // Shrink or grow list depending on the right hand's size
    if (pow(2,(int) sqrt(capacity)) == capacity) capacity--;
    m_capacity = pow(2,ceil(log((sqrt(capacity))/log(2))));

        // Initiailize m_cols
        for (int i = 0; i < m_capacity; i++)
            m_cols[i] = new SSLColumn(m_capacity);

        // Initialize m_colInfo
        for (int i = 0; i < m_capacity * 2 + 1; i++)
            m_colInfo[i] = 0;

    m_size = rhs.m_size;
        m_end = bufferIndex(m_size);
    m_start = 0;

    for (int i = 0; i < m_size; i++)
        *m_cols[i] = *rhs.m_cols[(rhs.m_start + i) % m_capacity];

    for (int i = 0; i<m_size*2;i++)
        m_colInfo[i] = rhs.m_colInfo[(rhs.m_start + i) % m_capacity];
    m_colInfo[m_capacity*2] = rhs.m_colInfo[rhs.m_capacity*2];

        return *this;
}


/*
 *  Method: SortedSquareList::add()
 *   Descr: Adds a value to the list, making square to keep it in order and sqaure
 */
void SortedSquareList::add(int data) {

    // If the arrays are full, resize them
    if (size() == pow(m_capacity, 2)) {
        resizeSquareList();
        add(data);
        return;
    }

    int colNumber = findNearest(data); // The column in which the data is most likely to appear
    int square_dimension = ceil(sqrt(size())); // Sqaure dimension

    // If the current column is full and the data is higher than the highest value in that column move to the next one
    if ((columnSize(colNumber) == square_dimension && (!colNumber || columnSize(colNumber - 1) == square_dimension) && size() != pow(square_dimension, 2)) && (data > m_colInfo[bufferIndex(colNumber)*2 + 1]))
        
        // If the columns are maxed out, create a new one
        if (++colNumber == m_size)
            m_end = bufferIndex(++m_size);


    // If the list is empty
    if (!size()) {
        m_cols[bufferIndex(colNumber)]->add(data);

        // Update colInfo and m_end
        m_colInfo[bufferIndex(colNumber)*2]++;
        m_colInfo[bufferIndex(colNumber)*2 + 1] = data;
        m_end = bufferIndex(++m_size);
        m_colInfo[m_capacity * 2]++;

        return;
    }

    // Determine the mean lengths of the columns on each side
    double left = colNumber ? m_colInfo[bufferIndex(colNumber - 1)*2] / (double) colNumber : 0
            , right = (colNumber < m_size-1) ? (m_colInfo[(bufferIndex(m_size + m_capacity - 1))*2] - m_colInfo[bufferIndex(colNumber)*2]) / (double) (m_size - 1 - colNumber) : 0;

    // If the current column isn't full, add the element and update colInfo
    if ((size() == pow(square_dimension, 2) || columnSize(colNumber) < square_dimension) && (!colNumber || columnSize(colNumber - 1) == square_dimension)) {
        m_cols[bufferIndex(colNumber)]->add(data);
        m_colInfo[bufferIndex(colNumber)*2 + 1] = m_cols[bufferIndex(colNumber)]->findAt(-1);
        m_colInfo[m_capacity * 2]++;

        // Otherwise shift
    } else {


        // Shift right
        if ((!left && !right) || (!!right && left >= right) || left == 0) {

            // add the number to be added to the column
            // shift the number that was removed from the column 
            int add = data, * shift = &data;
            // Keep shifting until there's no need to shift or we've shifted every column
            for (int i = colNumber; i < m_size && shift != 0; i++) {
                if (columnSize(i) == square_dimension && columnSize(i) != 1) {
                    *shift = m_cols[bufferIndex(i)]->removeLast();
                } else
                    shift = 0;

                m_cols[bufferIndex(i)]->add(add);

                // Update colinfo to keep track of list
                m_colInfo[bufferIndex(colNumber)*2 + 1] = m_cols[bufferIndex(colNumber)]->findAt(-1);

                if (shift)
                    add = *shift;
            }
            if (shift) {
                m_end = bufferIndex(++m_size);
                m_cols[bufferIndex(m_size - 1)]->add(*shift);
            }

            // Shift left    
        } else {
            // add the number to be added to the column
            // shift the number that was removed from the column 
            int add = data, * shift = &data;
            // Keep shifting until there's no need to shift or we've shifted every column
            for (int i = colNumber; i >= 0 && shift != 0; i--) {
                if (columnSize(i) == square_dimension && columnSize(i) != 1) {
                    *shift = m_cols[bufferIndex(i)]->removeFirst();
                } else
                    shift = 0;
                m_cols[bufferIndex(i)]->add(add);

                // Update colinfo to keep track of list
                m_colInfo[bufferIndex(i)*2 + 1] = m_cols[bufferIndex(i)]->findAt(-1);

                if (shift)
                    add = *shift;
            }
            if (shift) {
                m_start = (m_start + m_capacity - 1) % m_capacity;
                m_cols[m_start]->add(*shift);
            }
        }
    // Update colInfo to keep track of list
    m_colInfo[m_capacity * 2]++;
    }
    
    // Update colInfo to keep track of list
    for (int i = 0; i < m_size; i++)
        m_colInfo[bufferIndex(i)*2] = m_cols[bufferIndex(i)]->size()+(i ? m_colInfo[bufferIndex(i - 1)*2] : 0);
}


/*
 *  Method: SortedSquareList::find()
 *   Descr: return the index of the specified value, or -1 if not found
 */
int SortedSquareList::find(int data) {
    // Isolate the column in which the data is most likely to appear
    int colNumber = findNearest(data);
    if (data > m_colInfo[bufferIndex(colNumber)*2+1])
        colNumber++;
    
    return (colNumber ? m_colInfo[bufferIndex(colNumber-1)*2] : 0)+ m_cols[bufferIndex(colNumber)]->find(data);
}


/*
 *  Method: SortedSquareList::findAt()
 *   Descr: Retrieve the value at the specified index
 */
int SortedSquareList::findAt(int pos) {
    // Throw range error if requested index is out of bounds
    if (pos >= size() || pos < -1)
        throw std::range_error("findAt: bad position");

    if (pos == -1)
        return m_cols[m_end - 1]->findAt(-1);

    int pos2 = m_size / 2;

    // loop through array to execute binary search
    // minIndex  the lower bound of the array to check
    // maxIndex the upper bound of the array to check
    // curValue the value at the current position in array
    for (int minIndex = 0, maxIndex = m_size, curValue = m_colInfo[bufferIndex(pos2)*2]; curValue != pos; pos2 = minIndex + (maxIndex - minIndex) / 2, curValue = m_colInfo[bufferIndex(pos2)*2]) {

        if (minIndex == maxIndex || ((pos2 == minIndex) && (minIndex == maxIndex - 1))) {
            int colNumber = bufferIndex(pos <= curValue ? minIndex : maxIndex);
            return m_cols[colNumber]->findAt(pos - (colNumber ? m_colInfo[(colNumber-1) * 2]:0));
        }
        if (curValue > pos)
            maxIndex = pos2;
        else
            minIndex = pos2;
    }

    return m_cols[bufferIndex(pos2+1)]->findAt(pos -  m_colInfo[bufferIndex(pos2) * 2]);

}

/*
 *  Method: SortedSquareList::findNearest()
 *   Descr: return the column the specified value is most likely to be in
 */

int SortedSquareList::findNearest(int data) {

    int pos = m_size / 2;

    // loop through array to execute binary search
    // minIndex  the lower bound of the array to check
    // maxIndex the upper bound of the array to check
    // curValue the value at the current position in array
    for (int minIndex = 0, maxIndex = m_size, curValue = m_colInfo[bufferIndex(pos)*2 + 1]; curValue != data; pos = minIndex + (maxIndex - minIndex) / 2, curValue = m_colInfo[bufferIndex(pos)*2 + 1]) {

        if (minIndex == maxIndex || ((pos == minIndex) && (minIndex == maxIndex - 1))) {
            return minIndex;
        }
        if (curValue > data)
            maxIndex = pos;
        else
            minIndex = pos;
    }

    return pos;

}

/*
 *  Method: SortedSquareList::remove()
 *   Descr: Remove an element from the SortedSquareList
 */
bool SortedSquareList::remove(int data) {
    int colNumber = findNearest(data); // The column in which the data is most likely to appear
    int square_dimension = ceil(sqrt(size())); // Sqaure dimension

    if (data > m_colInfo[bufferIndex(colNumber)*2 + 1])
        colNumber++;


    // Edit colInfo and m_end only if the removal was successful         
    bool success = ~m_cols[bufferIndex(colNumber)]->remove(data);
    if (success) {
        m_colInfo[m_capacity * 2]--;
        
        // Kind of like a base case
        if (size() == 1) {
            m_colInfo[bufferIndex(colNumber)*2]--;
            m_colInfo[bufferIndex(colNumber)*2 + 1] = 0;
            m_end = bufferIndex(--m_size);
        } else {


            // Determine the Square Dimension of the adjacent columns 
            int left = colNumber ? columnSize(colNumber - 1) : 0, right = (colNumber < m_size - 1) ? columnSize(colNumber + 1) : 0;

            // Shift array
            if (left == square_dimension || right == square_dimension) {
                if (right >= left)
                    shiftFromRight(colNumber);
                else
                    shiftFromLeft(colNumber);
            } else if (left < square_dimension - 1 || right < square_dimension - 1) {
                if (right > left)
                    shiftFromRight(colNumber);
                else
                    shiftFromLeft(colNumber);
            } else if (right) {
                shiftFromRight(colNumber);
            }

        }

        for (int i = 0; i < m_size; i++)
            m_colInfo[bufferIndex(i)*2] = m_cols[bufferIndex(i)]->size()+(i ? m_colInfo[bufferIndex(i - 1)*2] : 0);
    }
    return success;
}



/*
 *  Method: SortedSquareList::capacity()
 *   Descr: return maximum number of active items this square list can hold with
 */
int SortedSquareList::capacity()
{
    return pow(m_capacity,2);
}


/*
 *  Method: SortedSquareList::size()
 *   Descr: Return the number of items in the square list as a whole, across all columns.
 */
int SortedSquareList::size()
{
    return m_colInfo[m_capacity * 2];
}

/*
 *  Method: SortedSqaureList::dump()
 *   Descr: Prints out array for debugging
 */

void SortedSquareList::dump() {
    cout << "SortedSquareList::dump(): m_size = " << m_size << endl;
    for (int i = 0; i < m_size; i++) {
        cout << "[" << i << "] ";
        m_cols[bufferIndex(i)]->dump();
    }
}

/*
 *  Method: SortedSquareList::bufferIndex()
 *  Descr: Take a regular 0-based index and return the correspondingf index in the buffer
 */
int SortedSquareList::bufferIndex(int index) {
    return (m_start + index) % m_capacity;
}


/*
 *  Method: SortedSquareList::resizeSquareList()
 *   Descr: Resize the SortedSquareList
 */
void SortedSquareList::resizeSquareList() {
    // Double the capacity
    m_capacity *= 2;

    SSLColumn **m_cols2 = new SSLColumn * [m_capacity]; // Array of pointers to SSLColumn
    int *m_colInfo2 = new int [m_capacity * 2 + 1]; // Stores highest number and series of size of columns

    // Initiailize m_cols2
    for (int i = 0; i < m_capacity; i++)
        m_cols2[i] = new SSLColumn(m_capacity);

    // Initialize m_colInfo2
    for (int i = 0; i < m_capacity * 2 + 1; i++)
        m_colInfo2[i] = 0;

    // Transfer existing data to new arrays
    for (int i = 0; i < m_capacity / 2; i++)
        *m_cols2[i] = *m_cols[i];

    for (int i = 0; i < m_capacity; i++)
        m_colInfo2[i] = m_colInfo[i];
    m_colInfo2[m_capacity * 2] = m_colInfo[m_capacity];

    //Replace old arrays with new arrays
    m_cols = m_cols2;
    m_colInfo = m_colInfo2;
    
    m_end = bufferIndex(m_size);
}

/*
 *  Method: SortedSquareList::columnSize()
 *   Descr: Get the size of the specified column
 */
int SortedSquareList::columnSize(int index)
{
    // Use m_colInfo to get sizes
    return m_colInfo[bufferIndex(index)*2] ? (index ? m_colInfo[bufferIndex(index)*2]-m_colInfo[bufferIndex(index-1)*2] : m_colInfo[bufferIndex(index)*2]) : 0;
}


/*
 *  Method: SortedSquareList::shiftFromRight()
 *   Descr: Shift the columns in from the right
 */
void SortedSquareList::shiftFromRight(int colNumber) {
    int square_dimension = ceil(sqrt(size())), * shift = &square_dimension;

    // Go through and shift all the columns until it's no longer necessary
    for (int i = colNumber; i < m_size && shift; i++) {
        if (columnSize(i) < square_dimension - 1) {
            *shift = m_cols[bufferIndex(i + 1)]->removeFirst();
            if (!columnSize(i + 1) - 1)
                m_end = bufferIndex(--m_size);
        } else
            shift = 0;

        if (shift) {
            m_cols[bufferIndex(i)]->add(*shift);
            m_colInfo[bufferIndex(i)*2 + 1] = *shift;
        }
    }
}


/*
 *  Method: SortedSquareList::shiftFromLeft()
 *   Descr: Shift the columns in from the left
 */
void SortedSquareList::shiftFromLeft(int colNumber) {
    int square_dimension = ceil(sqrt(size())), * shift = &square_dimension;

    // Go through and shift all the columns until it's no longer necessary
    for (int i = colNumber; i >= 0; i--) {
        if (columnSize(i) < square_dimension - 1) {
            *shift = m_cols[bufferIndex(i - 1)]->removeLast();
            if (!columnSize(i - 1) - 1) {
                m_start = (m_start + 1) % m_capacity;
                m_size--;
            }
        } else
            shift = 0;

        if (shift) {
            m_cols[bufferIndex(i)]->add(*shift);
        }
    }
}


