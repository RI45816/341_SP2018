/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*****************************************
 ** File:    QTNode.cpp
 ** Project: CMSC 341 proj3, Spring 2018
 ** Author:  Uzoma Uwanamodo
 ** Date:    03/31/2018
 ** E-mail:  uu3@umbc.edu
 ** 
 ** This file contains the definition for the QTNode class.
 ** 
 ** 
 ** 
 ** 
 *********************************************/
#include <iostream>
#include "QTNode.h"

using namespace std;

int QTNode::debug_count = 0;

/*
 *  Method: QTNode::iterator::iterator()
 *   Descr: Constructor method for QTNode::iterator
 */
QTNode::iterator::iterator() {
}

/*
 *  Method: QTNode::iterator::operator==()
 *   Descr: Determine if iterators are equal
 */
bool QTNode::iterator::operator==(const QTNode::iterator &other) {
    return m_position == other.m_position && m_node == other.m_node;
}

/*
 *  Method: QTNode::iterator::operator!=()
 *   Descr: Determine if iterators are not equal
 */
bool QTNode::iterator::operator!=(const QTNode::iterator &other) {
    return !(m_position == other.m_position && m_node == other.m_node);
}

/*
 *  Method: QTNode::iterator::operator++()
 *   Descr: Increment iterator prefix
 */
QTNode::iterator & QTNode::iterator::operator++() {
    m_position++;
    return *this;
}

/*
 *  Method: QTNode::iterator::operator++()
 *   Descr: Increment iterator postfix
 */
QTNode::iterator QTNode::iterator::operator++(int dummy) {
    m_position++;
    return *this;
}

/*
 *  Method: QTNode::iterator::operator*()
 *   Descr: Iterator function that derefences iterator
 */
QTNode *& QTNode::iterator::operator*() {
    return m_node->m_nodes[m_position];
}

/*
 *  Method: QTNode::QTNode()
 *   Descr: Default constructor for QTNode
 */
QTNode::QTNode() : m_isLeaf(false), m_point(0, 0), m_bounds(m_point, 1), m_data(0),m_nodes() {
    // Initialize array of null points
    for (int i = 0; i < QT_NUM_KIDS; i++)
        m_nodes[i] = 0;
}

/*
 *  Method: QTNode::~QTNode()
 *   Descr: Destructor for QTNode
 */
QTNode::~QTNode() {
    for (int i = 0; i < QT_NUM_KIDS; i++) delete m_nodes[i];
}

/*
 *  Method: QTNode::add()
 *   Descr: Add point and data to tree
 */
bool QTNode::add(const Point &pt, int data) {

    Point pt2 = pt; // Can't use const Point in functions

    // If there are no sub-nodes, operate on current node
    if (isEmpty()) {

        // if current node is a leaf node
        if (m_isLeaf) {

            // If the points are the same, replace data values and return false
            if (pt2 == m_point) {
                m_data = data;
                return false;
            }// Different points
            else {
                m_isLeaf = false; // Inserting another node at current node means this node can longer be a leaf

                // If the new point is in the current bounding box
                if (m_bounds.inBounds(pt2)) {

                    // thisIndex index of the sub-node for current point
                    // newIndex index of the sub-node for new point
                    int thisIndex = sortPoint(m_point), newIndex = sortPoint(pt2);

                    // Points in the same quadrant
                    if (thisIndex == newIndex) {

                        // Recurse this function into a subquadrant
                        m_nodes[thisIndex] = new QTNode(pt2, data, m_bounds.m_dim >> 1);
                        m_nodes[thisIndex]->add(pt2, data);
                    }// Points in different quadrant
                    else {

                        // Set current and new leaf nodes into respective quadrants
                        m_nodes[thisIndex] = new QTNode(m_point, m_data, m_bounds.m_dim >> 1);
                        m_nodes[newIndex] = new QTNode(pt2, data, m_bounds.m_dim >> 1);
                    }

                    // New point is not in current bounding box
                } else {
                    m_bounds.resize(m_point, pt2);
                    m_nodes[sortPoint(m_point)] = new QTNode(m_point, m_data, m_bounds.m_dim >> 1);
                    m_nodes[sortPoint(pt2)] = new QTNode(pt2, data, m_bounds.m_dim >> 1);
                }
            }

            // Not a leaf node
        } else {
            int BB2 = 0; // The nearest power of two of the  greater of the two coordinate dimensions
            for (int pattern = (pt2.m_x > pt2.m_y ? pt2.m_x : pt2.m_y), i = 16; i; i >>= 1)
                if (pattern >> BB2 + i) BB2 += i;

            BB2 = 1 << BB2; // Turn BB2 into a power of 2
            m_bounds.resize(Point(BB2, BB2), pt2); // Create a box big enough to store 

            m_data = data;
            m_point = pt2;
            m_isLeaf = true;
        }

        // There are subnodes
    } else {

        // New point is within current bounding box
        if (m_bounds.inBounds(pt2)) {

            int thisIndex = sortPoint(pt2); // Quadrant the point belongs in

            // Quadrant for new point is empty
            if (!m_nodes[thisIndex])
                m_nodes[thisIndex] = new QTNode(pt2, data, m_bounds.m_dim >> 1); // Populate that subnode with new point

                // Quadrant for new point is already populate
            else
                m_nodes[thisIndex]->add(pt2, data); // Recurse insert equation in that quadrant

            // New point is not within current bounding box
        } else {
            BBox oldBoundingBox = m_bounds; // Save the current bounding box
            QTNode * oldNodes[QT_NUM_KIDS];

            // Clear subnodes
            for (int i = 0; i < QT_NUM_KIDS; i++) {
                oldNodes[i] = m_nodes[i];
                m_nodes[i] = 0;
            }
            m_bounds.resize(m_bounds.m_bL, pt2); // Create new bounding box

            // thisIndex index of the sub-node for current point
            // newIndex index of the sub-node for new point
            int thisIndex = sortPoint(oldBoundingBox.m_bL), newIndex = sortPoint(pt2);

            // Assign to respective quadrants
            m_nodes[newIndex] = new QTNode(pt2, data, m_bounds.m_dim >> 1);
            m_nodes[thisIndex] = new QTNode(oldNodes, oldBoundingBox, m_bounds.m_dim >> 1);

        }

    }
    return true;
}

/*
 *  Method: QTNode::remove()
 *   Descr: 
 */
bool QTNode::remove(const Point &pt, bool &empty) {
    Point pt2 = pt; // Can't use const Point in functions

    // Looking for point
    if (empty) {
        int quad = sortPoint(pt2);

        // Point is on leaf node just one level below root of tree
        if (m_nodes[quad]->m_isLeaf) {
            delete m_nodes[quad];
            m_nodes[quad] = 0;

            QTNode * newRoot[QT_NUM_KIDS] = {0}; // Change the root
            bool replaced = false; // Wheter or not we have the new root

            // Get number of non-empty quadrants
            // numRemainingFull number of non-empty quadrants
            // remainingIndex quadrant of the remaining node if there's only the deleted node and one other node
            // numRemainingLeaves is how many leaves remain at this level
            int numRemainingFull = 0, remainingIndex, numRemainingLeaves = 0;
            for (int i = 0; i < QT_NUM_KIDS; i++)
                if (m_nodes[i]) {
                    if (m_nodes[i]->m_isLeaf)
                        numRemainingLeaves++;
                    numRemainingFull++;
                    remainingIndex = i;
                }


            // Only one node left after point was deleted
            if (numRemainingFull == 1 && !numRemainingLeaves) {

                // Traverse tree to find either leaf node or subtree with multple subtrees
                for (QTNode ** curNode = m_nodes[remainingIndex]->m_nodes; !replaced; curNode = curNode[remainingIndex]->m_nodes)

                    // Loop through subtrees quadrants
                    for (int i = 0, numRemainingFull = 0; i < QT_NUM_KIDS; i++) {

                        // Quadrant isn't empty
                        if (curNode[i]) {

                            // Mulitple occupied quadrants
                            // Search over
                            // Bring this subtree up
                            if (numRemainingFull++) {

                                for (int j = 0; j < QT_NUM_KIDS; j++) {

                                    newRoot[j] = curNode[j];
                                    curNode[j] = 0;
                                }
                                replaced = true;
                                break;
                            } else remainingIndex = i;
                        }
                    }
            
                // Delete the useless branch to nowhere
                delete m_nodes[remainingIndex];


                // Change root subtrees
                for (int i = 0; i < QT_NUM_KIDS; i++)
                    m_nodes[i] = newRoot[i];

                m_bounds = m_nodes[remainingIndex]->m_bounds;
                m_bounds.grow();
            }
        }// Point is buried deeper in the tree
        else {
            empty = false;
            m_nodes[quad]->remove(pt, empty);
        }

    }// Recursing to find point 
    else {
        int quad = sortPoint(pt2);

        // Point is on leaf node just one level below root of tree
        if (m_nodes[quad]->m_isLeaf) {
            delete m_nodes[quad];
            m_nodes[quad] = 0;

            // Get number of non-empty quadrants and leaves
            // numRemainingFull number of non-empty quadrants
            // remainingIndex quadrant of the remaining node if there's only the deleted node and one other node
            // numRemainingLeaves is how many leaves remain at this level
            int numRemainingFull = 0, remainingIndex, numRemainingLeaves = 0;
            for (int i = 0; i < QT_NUM_KIDS; i++)
                if (m_nodes[i]) {
                    if (m_nodes[i]->m_isLeaf)
                        numRemainingLeaves++;
                    numRemainingFull++;
                    remainingIndex = i;
                }

            // If all that's left is a subtree with only one leaf, bring that leaf up
            if (numRemainingFull == 1 && numRemainingLeaves) {
                m_bounds = m_nodes[remainingIndex]->m_bounds;
                m_data = m_nodes[remainingIndex]->m_data;
                m_isLeaf = true;
                m_point = m_nodes[remainingIndex]->m_point;
                m_bounds.grow();
                delete m_nodes[remainingIndex];
                m_nodes[remainingIndex] = 0;
            }
        } else m_nodes[quad]->remove(pt, empty);
    }
    return true;
}

/*
 *  Method: QTNode::find()
 *   Descr: Get data for point in subtree if point is in subtree
 */
bool QTNode::find(const Point &pt, int &data) {
    bool dummy;

    Point pt2 = pt; // Can't use const Point in functions

    // Current node has no subnodes
    if (isEmpty())

        // Current node is a leaf
        if (m_isLeaf) {

            // Leaf's point matches request point
            if (m_point == pt2) {
                data = m_data; // Return data value
                return true;
            }

            // Something went wrong, return false
        } else return false;

        // Node has subnodes
    else {

        int quadIndex = sortPoint(pt2); // Quadrent the point would be in

        // Quadrent isn't empty
        if (m_nodes[quadIndex])
            return m_nodes[quadIndex]->find(pt, data); // Search the proper quadrant

            // Quadrent is empty
        else
            return false; // Point is not in tree
    }
}

/*
 *  Method: QTNode::findPoints()
 *   Descr: Find all the points within a bounded box
 */
int QTNode::findPoints(const BBox &region, std::vector<Point> &found) {
    int points = 0;

    // No subtrees
    if (isEmpty()) {

        // Current node is leaf node
        if (m_isLeaf) {

            // Point is within region
            if (region.inBounds(m_point)) {
                found.push_back(m_point);
                return 1;
            }
        }
    }// There are subtrees
    else
        // Loop through all quadrants and recurse findPoints
        for (int i = 0; i < QT_NUM_KIDS; i++)
            if (m_nodes[i] && region.overlaps(m_nodes[i]->m_bounds))
                points += m_nodes[i]->findPoints(region, found);

    return points;
}

/*
 *  Method: QTNode::dump()
 *   Descr: Print out contents of entire subtree
 */
void QTNode::dump() {
    
    // If the current node is a leaf, print out the leaf info
    if (m_isLeaf)
        cout << "[QTNode bounds=" << m_bounds << " is LEAF: pt=" << m_point << ", data=" << m_data << "]" << endl;

        // Otherwise, print all 4 subtrees (or NULL, if a particular subtree doesn't exist)
    else {
        cout << "[QTNode bounds=" << m_bounds << " is INTERNAL:" << endl;

        // Print out the info for the Bottom-Left node
        cout << "Bottom-Left child:" << endl;
        if (m_nodes[BL])
            m_nodes[BL]->dump();
        else
            cout << "[NULL]" << endl;

        // Print out the info for the Bottom-Right node
        cout << "Bottom-Right child:" << endl;
        if (m_nodes[BR])
            m_nodes[BR]->dump();
        else
            cout << "[NULL]" << endl;

        // Print out the info for the Top-Left node
        cout << "Top-Left child:" << endl;
        if (m_nodes[TL])
            m_nodes[TL]->dump();
        else
            cout << "[NULL]" << endl;

        // Print out the info for the Top-Right node
        cout << "Top-Right child:" << endl;
        if (m_nodes[TR])
            m_nodes[TR]->dump();

        else
            cout << "[NULL]" << endl;

        cout << "]" << endl;
    }
}

/*
 *  Method: QTNode::begin()
 *   Descr: Return an iterator to the beginning
 */
QTNode::iterator QTNode::begin() {
    QTNode::iterator it;
    it.m_node = this;
    it.m_position = 0;

    return it;
}

/*
 *  Method: QTNode::end()
 *   Descr: Return an iterator to the end
 */
QTNode::iterator QTNode::end() {
    QTNode::iterator it;
    it.m_node = this;
    it.m_position = QT_NUM_KIDS;

    return it;
}

/*
 *  Method: QTNode::isEmpty()
 *   Descr: Determine whether or not there are sub-nodes
 */
bool QTNode::isEmpty() {
    
    for (int i = 0; i < QT_NUM_KIDS; i++) {
        if (m_nodes[i])
            return false;
    }
    return true;
}

/*
 *  Method: QTNode::sortPoint()
 *   Descr: Determine the index of the sub-node a point should be sorted into
 */
int QTNode::sortPoint(Point & pt) {

    /*
     * x,y   Extract x,y value from point
     * index    Index of the sub-node
     * dim  Dimension size of current bounding box
     * BBx,BBy  x,y value of the point of the bottom left corner of the bounding box
     */
    int x = pt.m_x, y = pt.m_y, index = 0, dim = m_bounds.m_dim >> 1, BBx = m_bounds.m_bL.m_x, BBy = m_bounds.m_bL.m_y;


    // x is in the right hand quadrants
    if (x >= BBx + dim)
        index++; // bottom left + 1 = bottom righr

    // y is in the top quadrants
    if (y >= BBy + dim)
        index += 2; // bottom left + 2 = top left, bottom right + 2 = top right

    return index;
}

/*
 *  Method: QTNode::QTNode()
 *   Descr:Create a leaf node at a certain dimension 
 */
QTNode::QTNode(Point &pt, int data, int dim) : m_point(pt), m_data(data), m_bounds(pt, dim >> 1), m_isLeaf(true),m_nodes() {

    // Initialize array of null points
    for (int i = 0; i < QT_NUM_KIDS; i++)
        m_nodes[i] = 0;

    // Make sure the bounding box has the correct bottom left value
    if (m_bounds.m_dim)
        m_bounds.grow();

    else
        m_bounds.m_dim = 1;
}

/*
 *  Method: QTNode::QTNode()
 *   Descr:Create a sub-node
 */
QTNode::QTNode(QTNode * nodes[], BBox bounds, int dim) : m_bounds(bounds), m_isLeaf(false), m_point(0, 0), m_data(0),m_nodes() {

    // Initialize array of null points
    for (int i = 0; i < QT_NUM_KIDS; i++)
        m_nodes[i] = 0;

    if (m_bounds.m_dim != dim) {
        m_bounds.m_dim = dim >> 1;
        m_bounds.grow();
        m_nodes[sortPoint(bounds.m_bL)] = new QTNode(nodes, bounds, dim >> 1);
    } else
        for (int i = 0; i < QT_NUM_KIDS; i++)
            m_nodes[i] = nodes[i];
}




/*
 *  Method: QTNode::iterator::operator++()
 *   Descr: 
 */
iterator & QTNode::iterator::operator++()
{
}


/*
 *  Method: QTNode::iterator::operator++()
 *   Descr: 
 */
iterator QTNode::iterator::operator++(int dummy)
{
    iterator dummy;

    return dummy;
}


/*
 *  Method: QTNode::begin()
 *   Descr: 
 */
iterator QTNode::begin()
{
    iterator dummy;

    return dummy;
}


/*
 *  Method: QTNode::end()
 *   Descr: 
 */
iterator QTNode::end()
{
    iterator dummy;

    return dummy;
}


