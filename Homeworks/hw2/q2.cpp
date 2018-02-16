#include <iostream>
using namespace std;

//
// INSERT YOUR binarySearch IMPLEMENTATION HERE
int binarySearch(int * myNums, int cnt,int value) {
    
    // pos current position in array
    int pos=cnt/2;
    if (cnt == 1)
        if (myNums[0]==value)
            return 0;
        else
            return -1;
    
    if (myNums[pos] == value)
        return pos;
    if (myNums[pos]>value) {
        int length, newNums[pos];
        for (length =0;length < pos; length++)
            newNums[length] = myNums[length];
        return binarySearch(newNums,length,value);
    } else {
        int length = 0, newNums[pos];
        for (int i=pos;i < cnt; length++,i++)
            newNums[length] = myNums[i];
         return ~binarySearch(newNums,length,value) ? pos + binarySearch(newNums,length,value) : -1;
    }
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