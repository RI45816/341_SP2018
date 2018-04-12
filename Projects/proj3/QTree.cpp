/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*****************************************
 ** File:    QTree.cpp
 ** Project: CMSC 341 proj3, Spring 2018
 ** Author:  Uzoma Uwanamodo
 ** Date:    03/31/2018
 ** E-mail:  uu3@umbc.edu
 ** 
 ** This file contains the definition for the QTree class.
 ** 
 ** 
 ** 
 ** 
 *********************************************/
#include <iostream>
#include "QTree.h"

using namespace std;

/*
 *  Method: QTree::QTree()
 *   Descr: Default constructor for QTree
 */
QTree::QTree() : m_size(0), 
        m_root(new QTNode())
{
}


/*
 *  Method: QTree::~QTree()
 *   Descr: Destructor method for QTree
 */
QTree::~QTree()
{
    delete m_root;
}


/*
 *  Method: QTree::add()
 *   Descr: Add point to tree
 */
bool QTree::add(const Point &pt, int data)
{
    if (m_root->add(pt,data)) {
        m_size++;
        return !0;
    } else
        return !1;

}


/*
 *  Method: QTree::remove()
 *   Descr: Remove point from tree
 */
bool QTree::remove(const Point &pt)
{
    int data;
    if (m_root->find(pt,data)) {
        bool empty =true;
        return m_root->remove(pt,empty);
    } else return false; // Point is not inbounds of m_root, and thus is not in the tree
}


/*
 *  Method: QTree::find()
 *   Descr: Get data for point in tree if point is in tree
 */
bool QTree::find(const Point &pt, int &data)
{
    
    // If point is not in range of the root, obviously the point is not in the tree
    if (!m_root->m_bounds.inBounds(pt))
        return false;
    else
    
    return m_root->find(pt,data);
}


/*
 *  Method: QTree::findPoints()
 *   Descr: Get all the points within a bounding box
 */
int QTree::findPoints(const BBox &region, std::vector<Point> &found)
{
    
    // Bounding overlaps with box of root
    if (region.overlaps(m_root->m_bounds))
        return m_root->findPoints(region,found); // Search tree for points
    else return 0; // No points found
    
}


/*
 *  Method: QTree::dump()
 *   Descr: Dump to allow user to inspect tree
 */
void QTree::dump() {
    cout << "============================================================" << endl;
    cout << "START Dump of quadtree" << endl;
    cout << "------------------------------------------------------------" << endl;
    m_root->dump();
    cout << "------------------------------------------------------------" << endl;
    cout << "END Dump of quadtree" << endl;
    cout << "============================================================" << endl;
}


