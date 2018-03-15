//File: test341.cpp
//
// UMBC Spring 2018 CMSC 341 Project2
//
// Use the Int341 class to monitor the amount of copying
// that takes place when you use the STL list class.
//

#include <iostream>
#include <list>
#include "Int341.h"

using namespace std ;



int main() {
   list<Int341> L ;

   Int341::m_debug = true ;

   L.push_back(Int341()) ;
   L.push_back(Int341()) ;
   L.push_back(Int341()) ;
   cout << "End of push_back's\n" ;
   Int341::report() ;

   cout << "\nMethod #1\n" ;
   Int341 a ;
   a = L.back() ;
   Int341::report()  ;

   cout << "\nMethod #2\n" ;
   Int341 b = L.back() ;
   Int341::report()  ;

   cout << "\nMethod #3\n" ;
   Int341 c(L.back()) ;
   Int341::report()  ;

   cout << "\nMethod #4\n" ;
   Int341 &ref = L.back() ;
   Int341::report()  ;

   cout << "\nMethod #5\n" ;
   Int341 *ptr ;
   ptr = &L.back() ;
   Int341::report()  ;

   cout << "\nEnd of main\n" ;

   return 0 ;
}
