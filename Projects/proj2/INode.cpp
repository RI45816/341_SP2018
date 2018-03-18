/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*****************************************
 ** File:    INode.cpp
 ** Project: CMSC 341 proj2, Spring 2018
 ** Author:  Uzoma Uwanamodo
 ** Date:    03/11/2018
 ** E-mail:  uu3@umbc.edu
 ** 
 ** This file contains the definition for the INode class.
 ** 
 ** 
 ** 
 ** 
 *********************************************/
#include <iostream>
#include "INode.h"

using namespace std;

/*
 *  Method: INode::INode()
 *   Descr: Default constructor for INode
 */
INode::INode() : m_size(0) {
}

/*
 *  Method: INode::INode()
 *   Descr: Constructor that also initializes m_dNode to the specified 
 */
INode::INode(DNode * dNode, int size) : m_dNode(dNode), m_size(size)
{
}

/*
 *  Method: INode::INode()
 *   Descr: Copy constructor for INode
 */
INode::INode(const INode& other) : m_dNode(other.m_dNode), m_size(other.m_size) {
}

/*
 *  Method: INode::operator=()
 *   Descr: Overloaded assignment operator for INode
 */
const INode & INode::operator=(const INode &rhs) {
    m_dNode = new DNode;
    *m_dNode = *rhs.m_dNode;
    m_size = rhs.m_size;
    return *this;
}

/*
 *  Method: INode::INode()
 *   Descr: Destructor method for INode
 */
INode::~INode() {
    m_dNode = 0;
}


/*
 *  Method: INode::GetSize()
 *   Descr: Return the size of the list fragment
 */
int INode::GetSize() const {
    return m_size;
}

/*
 *  Method: INode::incrementSize()
 *   Descr: Increase the size by 1 and return the new size
 */
void INode::incrementSize()
{
    ++m_size;
}


/*
 *  Method: INode::GetDNode()
 *   Descr: Return the DNode of the current INode
 */
DNode * INode::GetDNode() const
{
    return m_dNode;
}

/*
 *  Method: INode::SetDNode()
 *   Descr: Set the DNode of the current INode
 */
void INode::SetDNode(DNode *dNode)
{
    m_dNode = dNode;
}






/*
 *  Method: INode::changeSize()
 *   Descr: Add delta to m_size;
 */
void INode::changeSize(int delta)
{
    m_size+=delta;
}


