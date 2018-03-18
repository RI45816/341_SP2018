/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*****************************************
 ** File:    DNode.cpp
 ** Project: CMSC 341 proj2, Spring 2018
 ** Author:  Uzoma Uwanamodo
 ** Date:    03/11/2018
 ** E-mail:  uu3@umbc.edu
 ** 
 ** This file contains the definition for the DNode class.
 ** 
 ** 
 ** 
 ** 
 *********************************************/
#include <iostream>
#include "DNode.h"

using namespace std;

/*
 *  Method: DNode::DNode()
 *   Descr: Default constructor for DNode
 */
DNode::DNode() : m_next(0) {
}



/*
 *  Method: DNode::DNode()
 *   Descr: Copy constructor for DNode
 */
DNode::DNode(const DNode& other) : m_data(Int341(other.m_data)), m_next(0) {
}

/*
 *  Method: DNode::operator=()
 *   Descr: Overloaded assignment operator for DNode
 */
const DNode & DNode::operator=(const DNode &rhs) {
    m_data = rhs.m_data;
    return *this;
}


/*
 *  Method: DNode::DNode()
 *   Descr: Destructor method for DNode
 */
DNode::~DNode() {
    m_next = 0;
}

/*
 *  Method: DNode::DNode()
 *   Descr: Constructor for DNode and sets m_data to data value
 */
DNode::DNode(Int341 data) : m_data(Int341(data)), m_next(NULL)
{
}


/*
 *  Method: DNode::getNext()
 *   Descr: Return the pointer to the next node
 */
DNode * DNode::getNext()
{
    return m_next;
}

/*
 *  Method: DNode::setNext()
 *   Descr: Set the pointer to the next node
 */
void DNode::setNext(DNode *next)
{
    m_next = next;
}

/*
 *  Method: DNode::setData()
 *   Descr: Set the value of m_data
 */
void DNode::setData(Int341 data)
{
    m_data = data;
}


/*
 *  Method: DNode::getData()
 *   Descr: Return the value of m_data
 */
Int341 * DNode::getData()
{
    return &m_data;
}




