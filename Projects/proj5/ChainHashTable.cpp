/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*****************************************
 ** File:    ChainHashTable.cpp
 ** Project: CMSC 341 proj5, Spring 2018
 ** Author:  Uzoma Uwanamodo
 ** Date:    05/11/2018
 ** E-mail:  uu3@umbc.edu
 ** 
 ** This file contains the definition for the ChainHashTable class.
 ** 
 ** 
 ** 
 ** 
 *********************************************/

#ifndef CHAINHASHTABLE_CPP
#define CHAINHASHTABLE_CPP


#include <iostream>
#include <stdexcept>
#include "ChainHashTable.h"
#include "Int341.h"


using namespace std;

/*
 *  Method: ChainHashTable::ChainHashTable()
 *   Descr: Default constructor for ChainHashTable
 */
template <typename T>
ChainHashTable<T>::ChainHashTable(unsigned int(*hashFunc)(const T &data), int n) : m_table(new list<T>[n]), m_length(n), m_size(0) {
    // cout << debug_count++ << endl;
    this->hashFunc = hashFunc;
}

/*
 *  Method: ChainHashTable::ChainHashTable()
 *   Descr: Copy constructor for ChainHashTable
 */
template <typename T>
ChainHashTable<T>::ChainHashTable(const ChainHashTable<T> &other) : m_table(new list<T>[other.m_length]), m_length(other.m_length), m_size(other.m_size) {
    {
        this->hashFunc = other.hashFunc;
        for (int i = 0; i < m_length; i++) {
            list<T> * bucket = &other.m_table[i];
            for (typename list<T>::iterator it = bucket->begin(); it!=bucket->end;it++)
                m_table[i].push_back(*it);
        }
    }
}

/*
 *  Method: ChainHashTable::operator=()
 *   Descr: Overloaded assignment operator for ChainHashTable
 */
template <typename T>
const ChainHashTable<T> & ChainHashTable<T>::operator=(const ChainHashTable<T> &rhs) {
    this->hashFunc = rhs.hashFunc;
    m_length = rhs.m_length;
    m_size = rhs.m_size;
    m_table = new list<T>[m_length];
    for (int i = 0; i < m_length; i++) {
            list<T> * bucket = &rhs.m_table[i];
            for (typename list<T>::iterator it = bucket->begin(); it!=bucket->end;it++)
                m_table[i].push_back(*it);
        }
}

/*
 *  Method: ChainHashTable::ChainHashTable()
 *   Descr: Destructor method for ChainHashTable
 */
template <typename T>
ChainHashTable<T>::~ChainHashTable() {
    delete [] m_table;
}

	/*------------------------------------------------------------------------------*/

/*
 *  Method: ChainHashTable::at()
 *   Descr: Return number of items stored at index
 */
template <typename T>
int ChainHashTable<T>::at(int index, vector<T> &contents)
{
    if (index < 0 || index > m_length)
        throw out_of_range("Invalid index");
    
    list<T> bucket = m_table[index];
    for (typename list<T>::iterator it=bucket.begin();it!=bucket.end();it++)
        contents.push_back(*it);
    
    return bucket.size();
}


/*
 *  Method: ChainHashTable::dump()
 *   Descr: Print hashtable to console
 */
template <typename T>
void ChainHashTable<T>::dump() {
    cout << "ChainHashTable dump; size: " << m_length << " buckets" << endl;
    for (int i = 0; i < m_length;i++) {
        cout << "[" << i << "]: ";
        for (typename list<T>::iterator it = m_table[i].begin(); it != m_table[i].end(); it++)
            cout << *it << ", ";
        cout << endl;
    }
    cout << "Total items: " << m_size << "" << endl;
}


/*
 *  Method: ChainHashTable::find()
 *   Descr: Return true if data is in m_table or false if not
 */
template <typename T>
bool ChainHashTable<T>::find(const T &data) {
    // cout << debug_count++ << endl;
    list<T> bucket = m_table[this->hashFunc(data) % m_length];
    for (typename list<T>::iterator it = bucket.begin(); it != bucket.end(); it++)
        if (*it == data)
            return true;
    return false;
}


/*
 *  Method: ChainHashTable::insert()
 *   Descr: Return true if item successfully inserted and false if not
 */
template <typename T>
bool ChainHashTable<T>::insert(const T &data)
{
    if (find(data))
        return false;
    
    // cout << debug_count++ << endl;
    m_size++;
    m_table[this->hashFunc(data) % m_length].push_front(data);

    return true;
}


/*
 *  Method: ChainHashTable::remove()
 *   Descr: Return the removed item
 */
template <typename T>
T ChainHashTable<T>::remove(const T &data, bool &found) {
    // cout << debug_count++ << endl;
    
    if (!m_size){
        found = false;
        return data;
    }    
    list<T>  * bucket = &m_table[this->hashFunc(data) % m_length];
    for (typename list<T>::iterator it=bucket->begin();it!=bucket->end();it++) {
        if (*it != data)
            continue;
        
        
        found = true;
        bucket->erase(it);
        m_size--;
        return data;
    }
    
    found = false;



}

	/*------------------------------------------------------------------------------*/

#endif // CHAINHASHTABLE_CPP