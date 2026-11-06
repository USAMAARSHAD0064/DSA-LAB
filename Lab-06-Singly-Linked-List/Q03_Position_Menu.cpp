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

class LinkedList
{
private:
    Node* head;

public:
    LinkedList()
    {
        head = nullptr;
    }

    int countNodes()
    {
        int count = 0;
        Node* temp = head;
        while (temp != nullptr)
        {
            count++;
            temp = temp->next;
        }
        return count;
    }

    bool insertAtPosition(int value, int position)
    {
        int total = countNodes();
        if (position < 1 || position > total + 1)
        {
            return false;
        }
        Node* newNode = new Node(value);
        if (position == 1)
        {
            newNode->next = head;
            head = newNode;
            return true;
        }
        Node* temp = head;
        for (int i = 1; i < position - 1; i++)
        {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
        return true;
    }

    bool deleteAtPosition(int position)
    {
        int total = countNodes();
        if (position < 1 || position > total)
        {
            return false;
        }
        Node* toDelete;
        if (position == 1)
        {
            toDelete = head;
            head = head->next;
            delete toDelete;
            return true;
        }
        Node* temp = head;
        for (int i = 1; i < position - 1; i++)
        {
            temp = temp->next;
        }
        toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
        return true;
    }

    int search(int value)
    {
        int position = 1;
        Node* temp = head;
        while (temp != nullptr)
        {
            if (temp->data == value)
            {
                return position;
            }
            temp = temp->next;
            position++;
        }
        return -1;
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

    ~LinkedList()
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
    LinkedList list;
    int choice, value, position;

    do
    {
        cout << endl;
        cout << "===== Singly Linked List Menu =====" << endl;
        cout << "1. Insert node at a specific position" << endl;
        cout << "2. Delete node at a specific position" << endl;
        cout << "3. Search for an element" << endl;
        cout << "4. Count total number of nodes" << endl;
        cout << "5. Display list" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        if (!(cin >> choice))
        {
            if (cin.eof())
            {
                break;
            }
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a number" << endl;
            choice = -1;
            continue;
        }

        switch (choice)
        {
        case 1:
            cout << "Enter value: ";
            cin >> value;
            cout << "Enter position: ";
            cin >> position;
            if (list.insertAtPosition(value, position))
            {
                cout << "Node inserted successfully" << endl;
            }
            else
            {
                cout << "Invalid position" << endl;
            }
            list.display();
            break;
        case 2:
            cout << "Enter position: ";
            cin >> position;
            if (list.deleteAtPosition(position))
            {
                cout << "Node deleted successfully" << endl;
            }
            else
            {
                cout << "Invalid position" << endl;
            }
            list.display();
            break;
        case 3:
            cout << "Enter value to search: ";
            cin >> value;
            position = list.search(value);
            if (position == -1)
            {
                cout << value << " not found in the list" << endl;
            }
            else
            {
                cout << value << " found at position " << position << endl;
            }
            break;
        case 4:
            cout << "Total number of nodes: " << list.countNodes() << endl;
            break;
        case 5:
            list.display();
            break;
        case 0:
            cout << "Exiting program" << endl;
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice != 0);

    return 0;
}
