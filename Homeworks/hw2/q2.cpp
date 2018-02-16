#include <iostream>
using namespace std;

//
// INSERT YOUR binarySearch IMPLEMENTATION HERE
int binarySearch(int * myNums, int cnt,int value) {
    
    // pos current position in array
    int pos=cnt/2;
    
    if ()
}
//

int main() {

    int val, myNums[1000]; // Yuck--magic number!
    int pos, cnt = -1;

    cout << "Enter numbers from smallest to largest, 0 to stop\n";
    do {
        cin >> myNums[++cnt];
    } while (myNums[cnt] != 0);

    do {
        cout << "Enter number to search for: ";
        cin >> val;
        if (val != 0) {
            pos = binarySearch(myNums, cnt, val);
            cout << "binarySearch reported " << pos << endl;
        }
    } while (val != 0);

    return 0;
}