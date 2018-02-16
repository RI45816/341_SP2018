#include <iostream>
using namespace std;

class Node {
public:
    int m_data;
    Node *m_next;
};

//
// INSERT YOUR getListFromUser IMPLEMENTATION HERE

Node * getListFromUser() {
    Node *head = NULL;
    int userInput;
    do {
        cout << "\nEnter a number (0 to stop): ";
        cin >> userInput;
        if (userInput != 0) {
            Node * newNode = new Node();
            newNode->m_data = userInput;
            if (!head)
                head = newNode;
            else {
                Node * curr = head;
                for (; curr->m_next; curr = curr->m_next);
                curr->m_next = newNode;
            }
        }
    } while (userInput != 0);
    return head;
}
//

int main() {

    Node *head, *curr, *next;

    head = getListFromUser();
    next = head;
    while (next != NULL) {
        curr = next;
        next = curr->m_next;
        cout << "Next #: " << curr->m_data << endl;
        delete curr;
    }
    delete next;
    return 0;
}
