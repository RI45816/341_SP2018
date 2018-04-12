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
#include <string>

#include "QTree.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    string cmd;
    int argX, argY, arg;
    QTree qt;
    while (!cin.eof()) {
        Point pt;
        cout << "<cmd arg>: ";
        cin >> cmd;

        if (~cmd.find("far")) {
            cin >> argX >> argY;
            pt(argX, argY);
        }

        if (cmd == "a") {
            cin >> arg;
            qt.add(pt, arg);
            qt.dump();
        } else if (cmd == "r") {
            if (qt.remove(pt))
                cout << "remove(" << pt << ") was successful" << endl;
            else
                cout << "remove(" << pt << ") wasn't successful, point does not exist" << endl;
            
            qt.dump();
        } else if (cmd == "f") {
            int data;
            if (qt.find(pt,data))
                cout << "find(" << pt << ") returned " << data << endl;
            else
                cout << "No data at " << pt << endl;
        } else if (cmd == "fp") {

        } else if (cmd == "d")
            qt.dump();
        else {
            cout << endl;
            break;
        }
    }

    return 0;
}

