/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*****************************************
 ** File:    p2testXX.cpp
 ** Project: CMSC 341 proj2, Spring 2018
 ** Author:  Uzoma Uwanamodo
 ** Date:    00/11/2018
 ** E-mail:  uu3@umbc.edu
 ** 
 ** This file contains the main driver program for proj2.
 ** 
 ** 
 ** 
 ** 
 *********************************************/

#include <cstdlib>
#include <stdio.h>
#include <iostream>

#include "SqList.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    string cmd;
    int arg;
    SqList sql;

    while (!cin.eof()) {
        cout << "<cmd arg>: ";
        cin >> cmd >> arg;
                if (cmd == "a") {
                    sql.add(arg);
                    sql.dump();
                } else if (cmd == "r") {
                    printf("remove(%i) returned %i\n", arg, sql.remove(arg).m_data);
                    sql.dump();
                } else if (cmd == "ra") {
                    printf("removeAt(%i) returned %i\n", arg, sql.removeAt(arg).m_data);
                    sql.dump();
                } else if (cmd == "f") {
                    printf("indexOf(%i) return %i\n",arg,sql.indexOf(arg));
                }
                else if (cmd == "fa") {
                    printf("sql[%i]=%i\n", arg, sql[arg].m_data);
                } else if (cmd == "d") {
                    sql.dump();
                } else if (cmd == "n") {
                    printf("number of items = %i\n", sql.numItems());
                } else {
                    cout << endl;
                    Int341::report();
                    break;
                }
        }

    return 0;
}

