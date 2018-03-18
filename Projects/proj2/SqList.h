/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*****************************************
 ** File:    SqList.h
 ** Project: CMSC 341 proj2, Spring 2017
 ** Author:  Uzoma Uwanamodo
 ** Date:    03/11/2018
 ** E-mail:  uu3@umbc.edu
 ** 
 ** This file contains the header for the SqList class.
 ** 
 ** 
 ** 
 ** 
 *********************************************/

#ifndef SQLIST_H
#define SQLIST_H

#include <list>
#include <bits/list.tcc>
#include <bits/stl_list.h>
#include "INode.h"

using namespace std;

class SqList {
public:
    // default constructor
    SqList();

    // copy constructor
    SqList(const SqList& other);

    // overloaded assignment operator
    const SqList& operator=(const SqList& rhs);

    // destructor
    virtual ~SqList();

    // Member function to insert an item into the appropriate sorted position in a SqList.
    void add(const Int341& data);

    // Member function to remove a value from a SqList and return its value.
    Int341 remove(const Int341& data);

    // Member function to remove an item from a given position of a SqList and return its value.
    Int341 removeAt(int pos);

    // Overloaded [] operator.
    Int341& operator[](int pos);

    // Member function that returns the position of the first occurrence of a value in a SqList.
    int indexOf(const Int341& data);

    // Member function that returns the number of items in SqList.
    int numItems();

    // Debugging member function:
    void dump();

    // Member function that joins or separates lists in order to keep the list square
    void consolidate();
    
    // Instructor implemented function
    void inspector();
    
   // Run a binary search to find the nearest index
    DNode *  findNearest(Int341 data);
   
   // Run a binary search to find the nearest column
   int  findNearestSegment(Int341 findTo);
   
   // Retrieve the segment at the specified index
   list<INode>::iterator getSegmentFromIndex(int index);
   
   // Retreive the nth Node in the segment
   DNode * getNthNodeInSegment(list<INode>::const_iterator it, int n);
   
   
    list <INode> m_iList; // list of INodes to help keep the list square
    int m_size; // Size of the entire list
    DNode * m_first; // Point to the first node in the list
    DNode * m_last; // Point to the last node in the list
private:
    static int debug_count;
};

#endif /* SQLIST_H */

