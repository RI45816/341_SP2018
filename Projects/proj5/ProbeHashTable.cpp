/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*****************************************
 ** File:    ProbeHashTable.cpp
 ** Project: CMSC 341 proj5, Spring 2018
 ** Author:  Uzoma Uwanamodo
 ** Date:    05/11/2018
 ** E-mail:  uu3@umbc.edu
 ** 
 ** This file contains the definition for the ProbeHashTable class.
 ** 
 ** 
 ** 
 ** 
 *********************************************/

#ifndef PROBEHASHTABLE_CPP
#define PROBEHASHTABLE_CPP


#include <iostream>
#include "ProbeHashTable.h"
#include <stdexcept>

using namespace std;

/*
 *  Method: ProbeHashTable::ProbeHashTable()
 *   Descr: Default constructor for ProbeHashTable
 */
template <typename T>
ProbeHashTable<T>::ProbeHashTable(unsigned int(*hashFunc)(const T&), int n) : m_table(new HashTableEntry[n]), m_length(n), m_size(0) {
    // cout << debug_count++ << endl;
    this->hashFunc = hashFunc;
}
 
/*
 *  Method: ProbeHashTable::ProbeHashTable()
 *   Descr: Copy constructor for ProbeHashTable
 */
template <typename T>
ProbeHashTable<T>::ProbeHashTable(const ProbeHashTable<T>& other) : m_table(new HashTableEntry[other.m_length]), m_length(other.m_length), m_size(other.m_size) {
    this->hashFunc = other.hashFunc;
    for (int i = 0; i<m_length;i++)
        if (other.m_table[i].m_flag == OCCUPIED)
            m_table[i] = HashTableEntry(other.m_table[i]);
}

/*
 *  Method: ProbeHashTable::operator=()
 *   Descr: Overloaded assignment operator for ProbeHashTable
 */
template <typename T>
const ProbeHashTable<T> & ProbeHashTable<T>::operator=(const ProbeHashTable<T> &rhs) {
    this->hashFunc = rhs.hashFunc;
    m_length = rhs.m_length;
    m_size = rhs.m_size;
    m_table = new HashTableEntry[m_length];
    for (int i = 0; i<m_length;i++)
        if (rhs.m_table[i].m_flag == OCCUPIED)
            m_table[i] = HashTableEntry(rhs.m_table[i]);
    return *this;
}

/*
 *  Method: ProbeHashTable::ProbeHashTable()
 *   Descr: Destructor method for ProbeHashTable
 */
template <typename T>
ProbeHashTable<T>::~ProbeHashTable() {
    delete [] m_table;
    
}


/*
 *  Method: ProbeHashTable::HashTableEntry::HashTableEntry()
 *   Descr: Create a new hashtable entry
 */
template <typename T>
ProbeHashTable<T>::HashTableEntry::HashTableEntry(const T &data) : m_data(data),m_flag(OCCUPIED) {
}


/*
 *  Method: ProbeHashTable::HashTableEntry::HashTableEntry()
 *   Descr: Create an empty hashtable entry
 */
template <typename T>
ProbeHashTable<T>::HashTableEntry::HashTableEntry() : m_flag(EMPTY), m_data(T()) {
}

/*
 *  Method: ProbeHashTable::at()
 *   Descr: Return number of items stored at index
 */
template <typename T>
int ProbeHashTable<T>::at(int index, vector<T> &contents) {
    if (index < 0 || index > m_length)
        throw out_of_range("Invalid index");

    HashTableEntry bucket = m_table[index];
    if (bucket.m_flag == OCCUPIED) {
        contents.push_back(bucket.m_data);
        return 1;
    } else
        return 0;
}


/*
 *  Method: ProbeHashTable::dump()
 *   Descr: Print hashtable to console
 */
template <typename T>
void ProbeHashTable<T>::dump() {
    cout << "ProbeHashTable dump; size: " << m_length << " buckets" << endl;
    for (int i = 0; i < m_length; i++) {
        cout << "[" << i << "]: ";
        switch (m_table[i].m_flag) {
            case DELETED:
                cout << "DELETED" << endl;
                break;
            case EMPTY:
                cout << "EMPTY" << endl;
                break;
            case OCCUPIED:
                cout << m_table[i].m_data << " (" << this->hashFunc(m_table[i].m_data) % m_length << ")" << endl;
                break;
        }
    }
    cout << "Total items: " << m_size << "" << endl;
}


/*
 *  Method: ProbeHashTable::find()
 *   Descr: Return true if data is in m_table or false if not
 */
template <typename T>
bool ProbeHashTable<T>::find(const T &data)
{
    int index;
    return locate(data,index,false);
}


/*
 *  Method: ProbeHashTable::insert()
 *   Descr: Return true if item successfully inserted and false if not
 */
template <typename T>
bool ProbeHashTable<T>::insert(const T &data) {
    if (m_size++ == m_length)
        throw out_of_range("The hashtable is full");

    int index;
    if (locate(data, index))
        return false;

    if (~index) {
        m_table[index] = HashTableEntry(data);
        return true;
    }

    return false;
}


/*
 *  Method: ProbeHashTable::remove()
 *   Descr: Return the removed item
 */
template <typename T>
T ProbeHashTable<T>::remove(const T &data, bool &found) {
    if (!m_size--) {
        m_size++;
        found = false;
    } else {

        int index;
        found = locate(data, index,false);
        if (found) {
            m_table[index].m_flag = DELETED;
            return m_table[index].m_data;
        }
    }
}

/*
 *  Method: ProbeHashTable::locate()
 *   Descr: Locate the item and store the index in a variable, return whether or not the data is already in the hash
 */
template <typename T>
bool ProbeHashTable<T>::locate(const T& data, int& index, bool stopAtDeleted) {
    /**
     * 
     * @param data Data to find
     * @param index Return index of data
     * @param stopAtDeleted Whether to stop looking if current bucket is marked as deleted
     * @return True if the data is in the hash, false if it's not
     */
    // cout << debug_count++ << endl;
    for (int i = index = this->hashFunc(data) % m_length; index != i - 1 && (stopAtDeleted ? m_table[index].m_flag == OCCUPIED : m_table[index].m_flag) && m_table[index].m_data != data; index = ++index % m_length);

    // If item already in hash, return true, otherwise, return false
    if (m_table[index].m_flag == OCCUPIED && m_table[index].m_data == data)
        return true;

        // If the hash is full, set index to out of range indicator
    else if (m_table[index].m_flag == OCCUPIED)
        index = -1;
    return false;
}


#endif // PROBEHASHTABLE_CPP