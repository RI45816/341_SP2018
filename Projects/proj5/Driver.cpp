/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*****************************************
 ** File:    p5testXX.cpp
 ** Project: CMSC 341 proj5, Spring 2018
 ** Author:  Uzoma Uwanamodo
 ** Date:    00/12/2018
 ** E-mail:  uu3@umbc.edu
 ** 
 ** This file contains the main driver program for proj5.
 ** 
 ** 
 ** 
 ** 
 *********************************************/

#include <cstdlib>
#include <iostream>
#include <cstring>

#include "ChainHashTable.h"
#include "ProbeHashTable.h"
#include "Int341.h"

using namespace std;

int debug_count = 0;

typedef unsigned int (*Hash)(const Int341 &data);

unsigned int hashFunction1(const Int341& data) {
    return data.m_data;
}

unsigned int hashFunction2(const Int341& data) {
    return data.m_data + 1;
}

unsigned int hashFunction3(const Int341& data) {
    return (3 * data.m_data + 5);
}




/*
 * 
 */
int main(int argc, char** argv) {
    cout << debug_count++ << endl;
    cout << -1 % 10 << endl;
    /*
     * cmd, arg,arg{2..5} User inputed arguments
     * dump Wheter or not to dump after every action
     * key Store random generated integer
     * hashes array of pointers to the various hash functions
     */
    char cmd[2];
    int arg, arg2, arg3, arg4, key;
    bool dump = false;
    long arg5;
    Hash hashes[] = {hashFunction1,hashFunction2,hashFunction3};


    /*
     * arg Choose between ChainHashTable (1) and ProbeHashTable (2)
     * arg2 Choose a hash function
     * arg3 Size of the hashtable
     */
    cin >> arg >> arg2 >> arg3;
    cout << debug_count++ << endl;
    HashTable<Int341> * HT;


    switch (arg) {
        case 1:
            HT = new ChainHashTable<Int341>(hashes[arg2 - 1], arg3);
            break;
        case 2:
            HT = new ProbeHashTable<Int341>(hashes[arg2 - 1], arg3);
            break;
    }
    cout << debug_count++ << endl;
    while (!cin.eof()) {
        cin >> cmd;
        cout << debug_count++ << endl;

        // Insert item
        /*
         * arg item to be inserted
         */
        if (!strcmp(cmd, "a")) {
            cin >> arg;
            if (HT->insert(arg))
                cout << "Inserted " << arg << " into the heap" << endl;
            else
                cout << "Failed to insert " << arg << " into the heap" << endl;
        }
            // Dump Hash
        else if (!strcmp(cmd, "d"))
            HT->dump();



            /* Generate random integers for hash
             * arg2 minimum integer
             * arg3 maximum integer
             * arg4 how many random numbers
             */
        else if (!strcmp(cmd, "r")) {
            cin >> arg2 >> arg3 >> arg4;
            srand(time(NULL));
            for (int i = 0; i < arg4 - 1; i++) {
                key = rand() % (arg3 - arg2 + 1) + arg2 - 1;
                if (HT->insert(key))
                    cout << "Inserted " << key << " into the heap" << endl;
                else
                    cout << "Failed to insert " << key << " into the heap" << endl;
                if (dump)
                    HT->dump();
            }
            key = rand() % (arg3 - arg2 + 1) + arg2 - 1;
            if (HT->insert(key))
                cout << "Inserted " << key << " into the heap" << endl;
            else
                cout << "Failed to insert " << key << " into the heap" << endl;            
        }
            /* Generate random intergers, but use a custom seed
             * arg2 minimum integer
             * arg3 maximum integer
             * arg4 how many random numbers
             * arg5 seed number
             */
        else if (!strcmp(cmd, "rs")) {
            cin >> arg2 >> arg3 >> arg4 >> arg5;
            srand(arg5);
            for (int i = 0; i < arg4; i++) {
                key = rand() % (arg3 - arg2 + 1) + arg2 - 1;
                if (HT->insert(key))
                    cout << "Inserted " << key << " into the heap" << endl;
                else
                    cout << "Failed to insert " << key << " into the heap" << endl;
                if (dump)
                    HT->dump();
            }
            key = rand() % (arg3 - arg2 + 1) + arg2 - 1;
            if (HT->insert(key))
                cout << "Inserted " << key << " into the heap" << endl;
            else
                cout << "Failed to insert " << key << " into the heap" << endl;
            }            
        
        // Whether or not to dump after every action
        else if (!strcmp(cmd, "dd")) {
            cin >> dump;
            continue;
        }
        
        /* Remove item from hash
         * arg Data to be removed
         */
        else if (!strcmp(cmd,"rm")) {
            cin >> arg;
            bool removed;
            Int341 data = HT->remove(arg,removed);
            if (removed)
                cout << "Removed "<< data << " from the heap" << endl;
            else
                cout << "Failed to remove "<< arg << " from the heap" << endl;
        }
        
        /* Delete hash and start a new
        * arg Choose between ChainHashTable (1) and ProbeHashTable (2)
        * arg2 Choose a hash function
        * arg3 Size of the hashtable             
         */
        else if (!strcmp(cmd, "z")) {
            delete HT;
//            (HT)->~HashTable();
            cin >> arg >> arg2 >> arg3;
            switch (arg) {
                case 1:
                    HT = new ChainHashTable<Int341>(hashes[arg2 - 1], arg3);
                    break;
                case 2:
                    HT = new ProbeHashTable<Int341>(hashes[arg2 - 1], arg3);
                    break;
            }
            continue;
        } else {
            if (dump)
                HT->dump();
            Int341::report();
            return 0;
        }
        cmd == "";
        if (dump)
            HT->dump();
    }
    delete HT;
    Int341::report();
    return 0;
}

