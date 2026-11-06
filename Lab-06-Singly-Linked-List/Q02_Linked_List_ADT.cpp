#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node* next;

    Node(int value)
    {
        data = value;
        next = nullptr;
    }
};

class SinglyLinkedList
{
private:
    Node* head;

public:
    SinglyLinkedList()
    {
        head = nullptr;
    }

    void insertAtBeginning(int value)
    {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    void insertAtEnd(int value)
    {
        Node* newNode = new Node(value);
        if (head == nullptr)
        {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    bool deleteByValue(int value)
    {
        if (head == nullptr)
        {
            return false;
        }
        if (head->data == value)
        {
            Node* toDelete = head;
            head = head->next;
            delete toDelete;
            return true;
        }
        Node* temp = head;
        while (temp->next != nullptr && temp->next->data != value)
        {
            temp = temp->next;
        }
        if (temp->next == nullptr)
        {
            return false;
        }
        Node* toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
        return true;
    }

    void display()
    {
        if (head == nullptr)
        {
            cout << "List is empty" << endl;
            return;
        }
        Node* temp = head;
        while (temp != nullptr)
        {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    ~SinglyLinkedList()
    {
        Node* temp = head;
        while (temp != nullptr)
        {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }
};

int main()
{
    SinglyLinkedList list;

    list.insertAtEnd(20);
    list.insertAtEnd(30);
    list.insertAtEnd(40);
    cout << "After inserting 20, 30, 40 at end: ";
    list.display();

    list.insertAtBeginning(10);
    list.insertAtBeginning(5);
    cout << "After inserting 10, 5 at beginning: ";
    list.display();

    if (list.deleteByValue(30))
    {
        cout << "Deleted 30: ";
    }
    else
    {
        cout << "30 not found: ";
    }
    list.display();

    if (list.deleteByValue(5))
    {
        cout << "Deleted 5: ";
    }
    else
    {
        cout << "5 not found: ";
    }
    list.display();

    if (list.deleteByValue(100))
    {
        cout << "Deleted 100: ";
    }
    else
    {
        cout << "100 not found: ";
    }
    list.display();

    return 0;
}
