/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*****************************************
 ** File:    DNode.h
 ** Project: CMSC 341 proj2, Spring 2017
 ** Author:  Uzoma Uwanamodo
 ** Date:    03/11/2018
 ** E-mail:  uu3@umbc.edu
 ** 
 ** This file contains the header for the DNode class.
 ** 
 ** 
 ** 
 ** 
 *********************************************/

#ifndef DNODE_H
#define DNODE_H

#include "Int341.h"


class DNode {
public:
    // default constructor
//    DNode();

    // Constructor with initialized variable
    DNode(Int341 data);
    
    // copy constructor
    DNode(const DNode& other);

    // overloaded assignment operator
    const DNode& operator=(const DNode& rhs);

    // destructor
    virtual ~DNode();
    
    // Retrieve the m_next node
    DNode * getNext();
   
    // Set the m_next node
    void setNext(DNode* next);

    // Retrieve the value of m_data
    Int341 * getData();
    
    // Set the value of m_data
    void setData(Int341 data);
    Int341  m_data;
    DNode * m_next;
private:

};

#endif /* DNODE_H */

