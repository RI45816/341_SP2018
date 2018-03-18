/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*****************************************
 ** File:    SqList.cpp
 ** Project: CMSC 341 proj2, Spring 2018
 ** Author:  Uzoma Uwanamodo
 ** Date:    03/11/2018
 ** E-mail:  uu3@umbc.edu
 ** 
 ** This file contains the definition for the SqList class.
 ** 
 ** 
 ** 
 ** 
 *********************************************/
#include <iostream>
#include <stdio.h>
#include <list>
#include <stdexcept>
#include <math.h>
#include "SqList.h"

using namespace std;

int SqList::debug_count = 0;

/*
 *  Method: SqList::SqList()
 *   Descr: Default constructor for SqList
 */
SqList::SqList() :m_size(0) {
    
}

/*
 *  Method: SqList::SqList()
 *   Descr: Copy constructor for SqList
 */
SqList::SqList(const SqList& other) : m_size(other.m_size), m_first(new DNode(*other.m_first)) {
   
    // Create copies of all the nodes in other and link them to the new list
    for (DNode * curNode = m_first, * curOtherNode = other.m_first->getNext(); curOtherNode; curNode = curNode->getNext(), curOtherNode = curOtherNode->getNext()) {
        curNode->m_next = (new DNode(*curOtherNode));
    }
    
    
    
    // Create the upper level list
    m_iList.push_back(INode(m_first));
    for (list<INode>::const_iterator it = ++other.m_iList.begin(), it2 = m_iList.begin(); it != other.m_iList.end(); it++, it2++) {
        m_iList.push_back(INode(getNthNodeInSegment(it2, it2->GetSize()), it->GetSize()));
    }
    
    // Set m_last to the last element in the new list
    m_last = getNthNodeInSegment(--m_iList.end(), m_iList.back().GetSize() - 1);
}



/*
 *  Method: SqList::operator=()
 *   Descr: Overloaded assignment operator for SqList
 */
const SqList & SqList::operator=(const SqList &rhs) {

    if (this != &rhs) {

        //      
        m_first = new DNode;
        *m_first = *rhs.m_first;
        m_size = rhs.m_size;
        for (DNode * curNode = m_first, * curOtherNode = rhs.m_first->getNext(); curOtherNode; curNode = curNode->getNext(), curOtherNode = curOtherNode->getNext()) {
            DNode * newNode = new DNode;
            *newNode = *curOtherNode;
            curNode->setNext(newNode);
        }


        m_iList.push_back(INode(m_first));
        for (list<INode>::const_iterator it = ++rhs.m_iList.begin(), it2 = m_iList.begin(); it != rhs.m_iList.end(); it++, it2++) {
            m_iList.push_back(INode(getNthNodeInSegment(it2, it2->GetSize()), it->GetSize()));
        }
        m_last = getNthNodeInSegment(--m_iList.end(),m_iList.back().GetSize()-1);
        
        return *this;
    }
}



/*
 *  Method: SqList::SqList()
 *   Descr: Destructor method for SqList
 */
SqList::~SqList() {
    DNode * curNode = m_first;
    DNode * delNode;
    while (curNode) {
        delNode = curNode;
        curNode = curNode->getNext();
        delete delNode;
        delNode = 0;
    }
        m_last = 0;
        m_first = 0;
        curNode =0;
        delNode = 0;
    m_iList.clear();
}
/*
 *  Method: SqList::add()
 *   Descr: 
 */
void SqList::add(const Int341 &data)
{
    // if the list is empty, create 
    if (!m_size++) {
        m_first = m_last = new DNode(data);
        m_iList.push_back(INode(m_first));
        return;
    }

    
    // Insert at the front if data is the infimum of the list's data set
    if (data < *m_first->getData()) {
        m_first = new DNode(data);
        m_first->setNext(m_iList.front().GetDNode());
        m_iList.front().SetDNode(m_first);
        m_iList.front().incrementSize();
    
        // Insert at the back if data is the supremum of the list's data set
    } else
        if (data > *m_last->getData()) {
        m_last->setNext(new DNode(data));
        m_last = m_last->getNext();
        m_iList.back().incrementSize();
    
        // Find the nearest node and insert
        } else {
        int segment = findNearestSegment(data);
        DNode * curNode = findNearest(data), * newNode = new DNode(data);
        newNode->setNext(curNode->getNext());
        curNode->setNext(newNode);
        getSegmentFromIndex(segment)->incrementSize();
    }
    
    consolidate();
    }


/*
 *  Method: SqList::remove()
 *   Descr: Return the element removed from the list
 */
Int341 SqList::remove(const Int341 &data)
{
    // Find the index of the element and the just do a removeAt at that index
    int index = indexOf(data); 
    if (!~index)
        throw out_of_range("Element is not in list");
    
    return removeAt(index);
    
}


/*
 *  Method: SqList::removeAt()
 *   Descr: 
 */
Int341 SqList::removeAt(int pos) {


    // If the index is invalid, throw an error
    if (pos >= m_size || pos < -1)
        throw out_of_range("Invalid index");


    Int341 element; // Store the element to be return

    // If the index is 0, do a special deletion
    if (!pos) {
        DNode * curNode = m_first;
        element = *m_first->getData();
        m_first = m_first->getNext();
        m_iList.front().changeSize(-1);
        m_iList.front().SetDNode(m_first);
        delete curNode;
        curNode = 0;
    } else if (pos == m_size - 1) {
        DNode * curNode = m_last;
        element = *curNode->getData();
        m_iList.back().changeSize(-1);
        m_last = getNthNodeInSegment(--m_iList.end(),m_iList.back().GetSize()-1);
        m_last->setNext(0);
        delete curNode;
        curNode = 0;
    } else {

        // Loop through INodes until the segment with the number is found
        list<INode>::iterator start = m_iList.begin();
        int size = 0;
        for (; size + start->GetSize() < pos; size += start++->GetSize());

        // Update the INode's size variable
        if (size + start->GetSize() != pos)
            start->changeSize(-1);
        else {
            start++;
            start--->changeSize(-1);
        }

        // Delete the requested node and bridge the gap 
        if (size + start->GetSize() != pos) {
            DNode * curNode = getNthNodeInSegment(start, pos - size - 1);

            if (curNode) {
                DNode * removeNode = curNode->getNext();
                element = *removeNode->getData();
                curNode->setNext(removeNode->getNext());
                delete removeNode;
                removeNode = 0;
            }
        } else {
            DNode * curNode = getNthNodeInSegment(start++, start->GetSize() - 1);

            if (curNode) {
                DNode * removeNode = start->GetDNode();
                element = *removeNode->getData();
                curNode->setNext(removeNode->getNext());
                start->SetDNode(curNode->getNext());
                delete removeNode;
                removeNode = 0;
            }
        }

        //    if (pos == m_size-1) {
        //        Int341 element = m_last->m_data;
        //        m_iList.back().changeSize(-1);
        //        m_size--;
        //        getNthNodeInSegment(m_iList.end(),pos-m_iList.back().GetSize()-1);
        //    }   
    }
    m_size--;
    consolidate();
    return element;
}


/*
 *  Method: SqList::operator[]()
 *   Descr: 
 */
Int341 & SqList::operator[](int pos)
{
    
    // If index out of bounds throw out of range error
    if (pos >= m_size || pos < -1)
        throw out_of_range("Invalid index");
    
    // Special positions
    if (!pos)
        return *m_first->getData();
    if (!(~pos))
        return *m_last->getData();
    
    // Find the segment that contains the requested index
    list<INode>::iterator start = m_iList.begin();
    int size = 0;
    for (;size + start->GetSize() < pos;size+=start++->GetSize());

    //    --start;
    DNode * curNode = getNthNodeInSegment(start,pos-size);
    if (curNode) {
        return curNode->m_data; 
    }
}


/*
 *  Method: SqList::indexOf()
 *   Descr: Return the index of the data item
 */
int SqList::indexOf(const Int341 &data)
{
    // Get nearest segment
    int segment = findNearestSegment(data);
    
    
    
    // Get the combined indices of all the previous segments
    list<INode>::iterator start = m_iList.begin();
    int pos =0;
    for (int i = 0;i<segment;i++,pos+=start++->GetSize());
    
    
    // Return the index of data (if it exists, otherwise return -1)
    DNode * curNode = start->GetDNode();
    for (; curNode && curNode->getNext() && *curNode->getNext()->getData() <= data;pos++,curNode = curNode->getNext());
    return *curNode->getData() == data ? pos : -1;
    
}


/*
 *  Method: SqList::numItems()
 *   Descr: Return the number of items in the square list 
 */
int SqList::numItems()
{
    return m_size;
}


/*
 *  Method: SqList::dump()
 *   Descr: 
 */
void SqList::dump()
{
    printf("\n----- SqList dump() -----\nnumber of items = %i\n-------------------------\n", m_size);
    DNode * curNode = m_first;
    int i = 0;
    for (list<INode>::iterator it=m_iList.begin();it!=m_iList.end();it++,i++) {
        printf("%i (%i) : ",i,it->GetSize());
        for (int i = 0; i < it->GetSize() && curNode; i++,curNode = curNode->getNext())
            cout << curNode->getData()->m_data << " ";
        cout << endl;
    }
}


/*
 *  Method: SqList::consolidate()
 *   Descr: Resize the list segments so that no 
 */
void SqList::consolidate() {


    double square_dimension = sqrt(m_size);

    // Keep on consolidating
    //    bool all_clear = false;
    //    while (!all_clear) {
    // Go through top level list and find any empty, short, or long lisr segments
    for (list<INode>::iterator it = m_iList.begin(); it != m_iList.end(); it++) {
        int size = it->GetSize(); // Size of current list segment

        // If the list segment is empty, erase it
        if (!size) {
            m_iList.erase(it--);
            if (++it == m_iList.end())
                m_last = getNthNodeInSegment(--m_iList.end(),m_iList.back().GetSize()-1);
            else
                --it;
        }
            // If the list segment is long, split it in half
        else if (size >= 2 * square_dimension) {
            m_iList.insert(it, INode(getNthNodeInSegment(it++, size - (size / 2)), (size / 2)));
            --it;
            --it;
            it->changeSize(-(size / 2));


            // If there are two adjacent short lists, combine them
        } else if (size <= square_dimension / 2)
            if (++it != m_iList.end() && it->GetSize() <= square_dimension / 2) {
                size = it->GetSize();
                m_iList.erase(it--);
                it++->changeSize(size);
            } else {
                --it;
            }
    }
    //    }
}



/*
 *  Method: SqList::findNearestSegment()
 *   Descr: return the list segment the specified value is most likely to be in
 */
int SqList::findNearestSegment(Int341 findTo) {
    int data = findTo.m_data;
    int pos = m_iList.size() / 2;
    list<INode>::iterator it = getSegmentFromIndex(pos);

    // loop through array to execute binary search
    // minIndex  the lower bound of the array to check
    // maxIndex the upper bound of the array to check
    // curValue the value at the current position in array
    for (int minIndex = 0, maxIndex = m_iList.size(), curValue = it->GetDNode()->getData()->m_data; curValue != data; pos = minIndex + (maxIndex - minIndex) / 2, it = m_iList.begin(), curValue = getSegmentFromIndex(pos)->GetDNode()->getData()->m_data) {

        if (minIndex == maxIndex || ((pos == minIndex) && (minIndex == maxIndex - 1))) {
            return minIndex;
        }
        if (curValue > data)
            maxIndex = pos;
        else
            minIndex = pos;
    }

    return pos;

    }


/*
 *  Method: SqList::findNearest()
 *   Descr: return the index of the highest element that's still less than 0
 */
DNode * SqList::findNearest(Int341 data) {
    int segment = findNearestSegment(data);
    
    list<INode>::iterator it = getSegmentFromIndex(segment);
    DNode * curNode = it->GetDNode();
    for (; curNode && curNode->getNext() && *curNode->getNext()->getData() < data;curNode = curNode->getNext());
    return curNode;
    
}

/*
 *  Method: SqList::getSegmentFromIndex()
 *   Descr: return the iterator value of the INode at the specified index
 */
list<INode>::iterator SqList::getSegmentFromIndex(int index) {
    list<INode>::iterator start = m_iList.begin();
    advance(start,index);
    return start;
}

/*
 *  Method: SqList::getNthNodeInSegment()
 *   Descr: return the nth DNode in the segment
 */
DNode* SqList::getNthNodeInSegment(list<INode>::const_iterator it, int n) {
    DNode * curNode = it->GetDNode();
    for (int i=0; i < n && curNode;i++,curNode=curNode->getNext());
    return curNode;
}



