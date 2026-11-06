#include <iostream>
#include <cstring>
using namespace std;

template <typename T>
class Queue
{
protected:
    T* arr;
    int maxSize;
    int currentSize;

public:
    Queue(int maxQueueSize)
    {
        if (maxQueueSize <= 0)
        {
            maxQueueSize = 5;
        }
        maxSize = maxQueueSize;
        currentSize = 0;
        arr = new T[maxSize];
    }

    virtual void enqueue(T data) = 0;
    virtual T dequeue() = 0;
    virtual T peek() = 0;
    virtual bool isFull() = 0;
    virtual bool isEmpty() = 0;

    virtual ~Queue()
    {
        delete[] arr;
    }
};

template <typename T>
class MyQueue : public Queue<T>
{
private:
    int frontIndex;
    int rearIndex;

public:
    MyQueue(int maxQueueSize) : Queue<T>(maxQueueSize)
    {
        frontIndex = 0;
        rearIndex = -1;
    }

    bool isFull() override
    {
        return this->currentSize == this->maxSize;
    }

    bool isEmpty() override
    {
        return this->currentSize == 0;
    }

    void enqueue(T data) override
    {
        if (isFull())
        {
            cout << "Queue Overflow! The queue is full" << endl;
            return;
        }
        rearIndex = (rearIndex + 1) % this->maxSize;
        this->arr[rearIndex] = data;
        this->currentSize++;
    }

    T dequeue() override
    {
        if (isEmpty())
        {
            cout << "Queue Underflow! The queue is empty" << endl;
            return T();
        }
        T data = this->arr[frontIndex];
        frontIndex = (frontIndex + 1) % this->maxSize;
        this->currentSize--;
        return data;
    }

    T peek() override
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return T();
        }
        return this->arr[frontIndex];
    }

    int size() const
    {
        return this->currentSize;
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return;
        }
        for (int i = 0; i < this->currentSize; i++)
        {
            cout << "   " << i + 1 << ". ";
            this->arr[(frontIndex + i) % this->maxSize].print();
        }
    }
};

struct PrintJob
{
    int jobID;
    char userName[50];
    int pages;

    void print() const
    {
        cout << "Job " << jobID << " | User: " << userName << " | Pages: " << pages << endl;
    }
};

int main()
{
    int size;
    cout << "Enter maximum number of print jobs: ";
    cin >> size;

    MyQueue<PrintJob> printer(size);
    int choice;

    do
    {
        cout << endl << "===== Printer Menu =====" << endl;
        cout << "1. Submit a new print job" << endl;
        cout << "2. Process the next print job" << endl;
        cout << "3. Display the next print job" << endl;
        cout << "4. Display all pending print jobs" << endl;
        cout << "5. Show the total number of pending print jobs" << endl;
        cout << "6. Exit" << endl;
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

        switch (choice)
        {
        case 1:
            if (printer.isFull())
            {
                cout << "Queue Overflow! Printer queue is full" << endl;
                break;
            }
            {
                PrintJob p;
                cout << "Enter job ID: ";
                cin >> p.jobID;
                cin.ignore(1000, '\n');
                cout << "Enter user name: ";
                cin.getline(p.userName, 50);
                cout << "Enter number of pages: ";
                cin >> p.pages;
                if (p.pages <= 0)
                {
                    cout << "Pages must be at least 1" << endl;
                    break;
                }
                printer.enqueue(p);
                cout << "Print job " << p.jobID << " submitted" << endl;
            }
            break;
        case 2:
            if (printer.isEmpty())
            {
                cout << "Queue Underflow! No print jobs pending" << endl;
            }
            else
            {
                PrintJob p = printer.dequeue();
                cout << "Printed and removed: ";
                p.print();
            }
            break;
        case 3:
            if (printer.isEmpty())
            {
                cout << "No print jobs pending" << endl;
            }
            else
            {
                cout << "Next print job: ";
                printer.peek().print();
            }
            break;
        case 4:
            cout << "Pending print jobs:" << endl;
            printer.display();
            break;
        case 5:
            cout << "Total pending print jobs: " << printer.size() << endl;
            break;
        case 6:
            cout << "Exiting" << endl;
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice != 6);

    return 0;
}
