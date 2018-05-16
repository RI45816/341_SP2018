/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*****************************************
 ** File:    ChainHashTable.h
 ** Project: CMSC 341 proj5, Spring 2017
 ** Author:  Uzoma Uwanamodo
 ** Date:    05/11/2018
 ** E-mail:  uu3@umbc.edu
 ** 
 ** This file contains the header for the ChainHashTable class.
 ** 
 ** 
 ** 
 ** 
 *********************************************/

#ifndef CHAINHASHTABLE_H
#define CHAINHASHTABLE_H

#include "HashTable.h"
#include <list>
#include <vector>

using namespace std;
    extern int debug_count;

template <typename T>
class ChainHashTable : public HashTable<T> {
public:
    // default constructor
   ChainHashTable(unsigned int (*hashFunc)(const T&), int n=101);
   
    // copy constructor
    ChainHashTable(const ChainHashTable& other);

    // overloaded assignment operator
    const ChainHashTable& operator=(const ChainHashTable& rhs);

    // destructor
    ~ChainHashTable();

    // Retreive the number of items stored at the index slot of the hash table
    int at(int index, vector<T>& contents);

    // Print out the contents of the dump hashtable
    void dump();

    // Look for data in the hash table
    bool find(const T& data);

    // Insert data into the hashtable
    bool insert(const T& data);

    // Remove data from the hashtable if found
    T remove(const T& data, bool& found);

private:
    list<T> * m_table; // Store the hash chains
    int m_length; // Number of buckets in hashtable
    int m_size; // Number of items in the hashtable
};

#include "ChainHashTable.cpp"
#endif /* CHAINHASHTABLE_H */

