/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*****************************************
 ** File:    INode.h
 ** Project: CMSC 341 proj2, Spring 2017
 ** Author:  Uzoma Uwanamodo
 ** Date:    03/11/2018
 ** E-mail:  uu3@umbc.edu
 ** 
 ** This file contains the header for the INode class.
 ** 
 ** 
 ** 
 ** 
 *********************************************/

#ifndef INODE_H
#define INODE_H

#include "DNode.h"


class INode {
public:
    // default constructor
    INode();
    
    // Create a new INode at a certain DNode 
    INode(DNode * dNode, int size = 1);

    // copy constructor
    INode(const INode& other);

    // overloaded assignment operator
    const INode& operator=(const INode& rhs);

    // destructor
    virtual ~INode();
    
    // Retrieve the size of the list segment
    int GetSize() const;
    
    // Increase the size of the list segment by 1
    void incrementSize();
    
    // Retrieve the pointer to the first node in this segment
    DNode* GetDNode() const;
    
    // Set the pointer to first node in this segment
    void SetDNode(DNode* dNode);
    
    // Change the size by the specified amount
    void changeSize(int delta);
    
    DNode * m_dNode;
    int m_size;
    
private:
};

#endif /* INODE_H */

