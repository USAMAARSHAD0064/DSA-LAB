#include <iostream>
#include <cstring>
using namespace std;

const int MAX_JOBS = 20;
const int NAME_SIZE = 100;

class PrintQueue
{
private:
    char documents[MAX_JOBS][NAME_SIZE];
    int frontIndex;
    int rearIndex;
    int count;

public:
    PrintQueue()
    {
        frontIndex = 0;
        rearIndex = -1;
        count = 0;
    }

    bool isEmpty() const
    {
        return count == 0;
    }

    bool isFull() const
    {
        return count == MAX_JOBS;
    }

    void enqueue(const char document_name[])
    {
        if (strlen(document_name) == 0)
        {
            cout << "Document name cannot be empty" << endl;
            return;
        }
        if (isFull())
        {
            cout << "Print queue is full" << endl;
            return;
        }
        rearIndex = (rearIndex + 1) % MAX_JOBS;
        strcpy(documents[rearIndex], document_name);
        count++;
        cout << "\"" << document_name << "\" added to the print queue" << endl;
    }

    void dequeue()
    {
        if (isEmpty())
        {
            cout << "No documents to print" << endl;
            return;
        }
        cout << "Printing \"" << documents[frontIndex] << "\"... done" << endl;
        frontIndex = (frontIndex + 1) % MAX_JOBS;
        count--;
    }

    void front() const
    {
        if (isEmpty())
        {
            cout << "Print queue is empty" << endl;
            return;
        }
        cout << "Next document: \"" << documents[frontIndex] << "\"" << endl;
    }

    void display() const
    {
        if (isEmpty())
        {
            cout << "Print queue is empty" << endl;
            return;
        }
        cout << "Print jobs in queue:" << endl;
        for (int i = 0; i < count; i++)
        {
            cout << "   " << i + 1 << ". " << documents[(frontIndex + i) % MAX_JOBS] << endl;
        }
    }
};

int main()
{
    PrintQueue printer;
    int choice;
    char name[NAME_SIZE];

    do
    {
        cout << endl << "===== Printer Queue =====" << endl;
        cout << "1. Add new print job" << endl;
        cout << "2. Print next document" << endl;
        cout << "3. Check next document" << endl;
        cout << "4. Display remaining print jobs" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";
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
        cin.ignore(1000, '\n');

        switch (choice)
        {
        case 1:
            cout << "Enter document name: ";
            cin.getline(name, NAME_SIZE);
            printer.enqueue(name);
            break;
        case 2:
            printer.dequeue();
            break;
        case 3:
            printer.front();
            break;
        case 4:
            printer.display();
            break;
        case 5:
            cout << "Exiting" << endl;
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice != 5);

    return 0;
}
