/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*****************************************
 ** File:    p3testXX.cpp
 ** Project: CMSC 341 proj3, Spring 2018
 ** Author:  Uzoma Uwanamodo
 ** Date:    4/9/2018
 ** E-mail:  uu3@umbc.edu
 **
 ** This file contains the main driver program for proj3.
 **
 **
 **
 **
 *********************************************/

#include <cstdlib>
#include <set>
#include <string>

#include "MinMaxHeap.h"

using namespace std;

template <typename T>
void sanityCheck(MinMaxHeap<T>& H) {
    int n = H.size();
    T minKey, maxKey, leftKey, rightKey;
    int minPos, maxPos, pos;

    bool passed = true;

    //   cout << "Sanity Check minHeap...\n" ;

    for (int i = 1; i <= n; i++) {
        H.locateMin(i, minKey, maxPos);
        H.locateMax(maxPos, maxKey, minPos);

        if (minKey != maxKey) {
            passed = false;
            cout << "Key mismatch at i = " << i << ": "
                    << "minKey = " << minKey << ", "
                    << "minPos = " << minPos << ", "
                    << "maxKey = " << maxKey << ", "
                    << "maxPos = " << maxPos
                    << endl;

            H.dump();
        }

        if (minPos != i) {
            passed = false;
            cout << "Position mismatch at i = " << i << ": "
                    << "minKey = " << minKey << ", "
                    << "minPos = " << minPos << ", "
                    << "maxKey = " << maxKey << ", "
                    << "maxPos = " << maxPos
                    << endl;

            H.dump();
        }

        if (2 * i <= n) { // has left child
            H.locateMin(2 * i, leftKey, pos);
            if (leftKey < minKey) { // left child smaller than root
                passed = false;
                cout << "Bad heap condition at i = " << i << ": "
                        << "root key = " << minKey << ", "
                        << "left key = " << leftKey
                        << endl;

                H.dump();
            }
        }

        if (2 * i + 1 <= n) { // has right child
            H.locateMin(2 * i + 1, rightKey, pos);
            if (rightKey < minKey) { // right child smaller than root
                passed = false;
                cout << "Bad heap condition at i = " << i << ": "
                        << "root key = " << minKey << ", "
                        << "right key = " << rightKey
                        << endl;

                H.dump();
            }
        }

    } // end of for (...)


    //   cout << "Sanity Check maxHeap...\n" ;

    for (int i = 1; i <= n; i++) {
        H.locateMax(i, maxKey, minPos);
        H.locateMin(minPos, minKey, maxPos);

        if (minKey != maxKey) {
            passed = false;
            cout << "Key mismatch at i = " << i << ": "
                    << "minKey = " << minKey << ", "
                    << "minPos = " << minPos << ", "
                    << "maxKey = " << maxKey << ", "
                    << "maxPos = " << maxPos
                    << endl;

            H.dump();
        }

        if (maxPos != i) {
            passed = false;
            cout << "Position mismatch at i = " << i << ": "
                    << "minKey = " << minKey << ", "
                    << "minPos = " << minPos << ", "
                    << "maxKey = " << maxKey << ", "
                    << "maxPos = " << maxPos
                    << endl;

            H.dump();
        }

        if (2 * i <= n) { // has left child
            H.locateMax(2 * i, leftKey, pos);
            if (leftKey > maxKey) { // left child bigger than root
                passed = false;
                cout << "Bad heap condition at i = " << i << ": "
                        << "root key = " << maxKey << ", "
                        << "left key = " << leftKey
                        << endl;

                H.dump();
            }
        }

        if (2 * i + 1 <= n) { // has right child
            H.locateMax(2 * i, rightKey, pos);
            if (rightKey > maxKey) { // right child bigger than root
                passed = false;
                cout << "Bad heap condition at i = " << i << ": "
                        << "root key = " << maxKey << ", "
                        << "right key = " << rightKey
                        << endl;

                H.dump();
            }
        }
    } // end of for (...)


    if (passed) {
        cout << "Passed sanityCheck()\n";
    } else {
        cout << "*** Failed sanityCheck()\n";
    }
}

template <typename T>
void checkAgainstSet(MinMaxHeap<T>& H, multiset<T>& origS) {
    multiset<T> S;
    typename multiset<T>::iterator it;

    int n = H.size();
    int pos;
    int key;

    bool passed = true;

    S = origS; // make copy

    if (n != S.size()) {
        passed = false;
        cout << "Heap and multiset sizes do not match!\n";
        cout << "   Heap size = " << n << endl;
        cout << "   Set size  = " << S.size() << endl;
    }


    for (int i = 1; i <= n; i++) {
        H.locateMin(i, key, pos);
        it = S.find(key);
        if (it == S.end()) {
            passed = false;
            cout << "Key " << key << " in the min-heap but not in the multiset.\n";
        } else {
            S.erase(it);
        }
    }

    if (S.size() > 0) {
        cout << "There are " << S.size()
                << " items in multiset that not in the min-heap.\n";
        for (it = S.begin(); it != S.end(); it++) {
            cout << *it << " ";
        }
        cout << endl;
    }


    S = origS; // start over

    for (int i = 1; i <= n; i++) {
        H.locateMax(i, key, pos);
        it = S.find(key);
        if (it == S.end()) {
            passed = false;
            cout << "Key " << key << " in the max-heap but not in the multiset.\n";
        } else {
            S.erase(it);
        }
    }

    if (S.size() > 0) {
        cout << "There are " << S.size()
                << " items in multiset that not in the max-heap.\n";
        for (it = S.begin(); it != S.end(); it++) {
            cout << *it << " ";
        }
        cout << endl;
    }

    if (passed) {
        cout << "Passed check against multiset\n";
    } else {
        cout << "***Failed check against multiset\n";
    }

}

/*
 *
 */
int main(int argc, char** argv) {

    string cmd;
    int arg, arg2, arg3, arg4;
    unsigned long arg5;
    MinMaxHeap<int> MMX(1000);
    multiset<int> S;
    multiset<int>::iterator it;
    int key;
    bool passed;
    while (!cin.eof()) {
        cin >> cmd;
        if (cmd == "a") {
            cin >> arg;
            MMX.insert(arg);
            S.insert(arg);
            //            MMX.dump();
        } else if (cmd == "rm") {
            cin >> arg;
            passed = true;
            for (int i = 0; i < arg; i++) {
                key = MMX.deleteMin();
                if (key != *S.begin()) {
                    passed = false;
                    cout << "deleteMax() returns key that is not the smallest  key! Printed: " << key << ", but should've printed: " << *S.begin() << "" << endl;
                } else {
                    cout << "Removed min item " << key << " from MinMaxHeap" << endl;
                    S.erase(S.begin());
                    sanityCheck(MMX);
                }
            }
            sanityCheck(MMX);

            if (passed) {
                checkAgainstSet(MMX, S);
            } else {
                cout << "***Failed deleteMin() test!\n";
                cout << "Skipped check against multiset\n";
            }
        } else if (cmd == "rx") {
            cin >> arg;
            passed = true;
            for (int i = 0; i < arg; i++) {
                key = MMX.deleteMax();
                if (key != *--S.end()) {
                    passed = false;
                    cout << "deleteMax() returns key that is not the largest key! Printed: " << key << ", but should've printed: " << *--S.end() << "" << endl;
                } else {
                    cout << "Removed max item " << key << " from MinMaxHeap" << endl;
                    S.erase(--S.end());
                    sanityCheck(MMX);
                }
            }
            sanityCheck(MMX);

            if (passed) {
                checkAgainstSet(MMX, S);
            } else {
                cout << "***Failed deleteMin() test!\n";
                cout << "Skipped check against multiset\n";
            }
        } else if (cmd == "r") {
            cin >> arg2 >> arg3 >> arg4;
            srand(time(NULL));
            for (int i = 0; i < arg4; i++) {
                key = rand() % (arg3 - arg2 + 1) + arg2 - 1;
                MMX.insert(key);
                S.insert(key);
            }
        } else if (cmd == "rs") {
            cin >> arg2 >> arg3 >> arg4 >> arg5;
            srand(arg5);
            for (int i = 0; i < arg4; i++) {
                key = rand() % (arg3 - arg2 + 1) + arg2 - 1;
                MMX.insert(key);
                S.insert(key);
            }
        } else if (cmd == "d")
            MMX.dump();
        else if (cmd == "dd")
            for (it = S.begin(); it != S.end(); it++)
                cout << *it << " ";
        else if (cmd == "c" || cmd == "ch") {
            sanityCheck(MMX);
            checkAgainstSet(MMX, S);
        } else if (cmd == "z") {
            (&MMX)->~MinMaxHeap<int>();
            new (&MMX) MinMaxHeap<int>(1000);
            S.clear();
        } else {
            break;
        }
    }
    return 0;
}

