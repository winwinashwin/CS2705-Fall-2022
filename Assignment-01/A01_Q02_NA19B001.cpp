/**
 * @file     A01_Q02_NA19B001.cpp
 * @author   Ashwin A Nayar (na19b001@smail.iitm.ac.in)
 */

#include <iostream>

using namespace std;

namespace ll {
    // Element datatype
    using data_t = int;

    class Node {
        public:
            data_t data;
            Node *prev, *next;

            Node();
            Node(data_t v);
            void print() const;
    };

    class DLinkedList {
        public:
            DLinkedList();

            void insert_at_tail(data_t v);
            void println() const;
            void println_reverse() const;

        private:
            Node *_head, *_tail;
            friend void merge_lists(DLinkedList &l1, DLinkedList &l2, const pair<char, int> &pos);
    };

    /**
     * Merges list l2 to l1 conforming to pos
     */
    void merge_lists(DLinkedList &l1, DLinkedList &l2, const pair<char, int> &pos);

    /************************************************************************************/

    Node::Node() {
        Node(0);
    }

    Node::Node(data_t v) {
        data = v;
        prev = nullptr;
        next = nullptr;
    }

    void Node::print() const {
        cout << data << " ";
    }

    DLinkedList::DLinkedList() {
        _head = nullptr;
        _tail = nullptr;
    }

    void DLinkedList::insert_at_tail(data_t v) {
        Node *ptr = new Node(v);
        if (!_head) {
            _head = ptr;
            _tail = ptr;
            return;
        }

        _tail->next = ptr;
        ptr->prev = _tail;
        _tail = ptr;
    }

    void DLinkedList::println() const {
        for (Node *ptr = _head; ptr; ptr = ptr->next) {
            ptr->print();
        }
        cout << endl;
    }

    void DLinkedList::println_reverse() const {
        for (Node *ptr = _tail; ptr; ptr = ptr->prev) {
            ptr->print();
        }
        cout << endl;
    }

    void merge_lists(DLinkedList &l1, DLinkedList &l2, const pair<char, int> &pos) {
        Node *ptr;
        int i;
        switch (pos.first) {
            case 'L': 
                for (i = 1, ptr = l1._head; i < pos.second; ++i, ptr = ptr->next);
                break;
            case 'R':
                for (i = 1, ptr = l1._tail; i < pos.second; ++i, ptr = ptr->prev);
                break;
            default:
                break;
        }
        ptr->prev->next = l2._head;
        l2._head->prev = ptr->prev;
        ptr->prev = l2._tail;
        l2._tail->next = ptr;
    }
}

int main(int argc, char **argv) {

    int n1, n2;
    cin >> n1 >> n2;

    int x;
    ll::DLinkedList l1, l2;

    // Populate list l1
    for (int i = 0; i < n1; ++i) {
        cin >> x;
        l1.insert_at_tail(x);
    }

    // Populate list l2
    for (int i = 0; i < n2; ++i) {
        cin >> x;
        l2.insert_at_tail(x);
    }

    pair<char, int> pos;
    cin >> pos.first >> pos.second;

    // merge l2 to l1
    merge_lists(l1, l2, pos);

    l1.println();
    l1.println_reverse();

    return EXIT_SUCCESS;
}
