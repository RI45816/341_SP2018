/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*****************************************
 ** File:    ProbeHashTable.h
 ** Project: CMSC 341 proj5, Spring 2017
 ** Author:  Uzoma Uwanamodo
 ** Date:    05/11/2018
 ** E-mail:  uu3@umbc.edu
 ** 
 ** This file contains the header for the ProbeHashTable class.
 ** 
 ** 
 ** 
 ** 
 *********************************************/

#ifndef PROBEHASHTABLE_H
#define PROBEHASHTABLE_H

#include "HashTable.h"
#include <vector>

using namespace std;

    extern int debug_count;
enum {DELETED = -1, EMPTY, OCCUPIED};

template <typename T>
class ProbeHashTable : public HashTable<T> {
public:
    
    class HashTableEntry {
    public:
        int m_flag;
        T m_data;
        
        // Constructor
        HashTableEntry(const T &data);
        
        HashTableEntry();
    };
    
    // default constructor
    ProbeHashTable(unsigned int (*hashFunc)(const T &data), int n = 101);

    // copy constructor
    ProbeHashTable(const ProbeHashTable& other);

    // overloaded assignment operator
    const ProbeHashTable& operator=(const ProbeHashTable& rhs);

    // destructor
    ~ProbeHashTable();


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

    // Convience function to look for the item only once
    bool locate(const T& data, int &index, bool stopAtDeleted=true);
    
    
private:
    HashTableEntry * m_table; // Store the hash chains
    int m_length; // Number of buckets in hashtable
    int m_size; // Number of items in the hashtable
};


#include "ProbeHashTable.cpp"
#endif /* PROBEHASHTABLE_H */

