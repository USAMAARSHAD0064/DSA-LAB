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

struct Customer
{
    char name[50];
    char transaction[50];

    void print() const
    {
        cout << name << " - " << transaction << endl;
    }
};

int main()
{
    int size;
    cout << "Enter maximum number of customers in line: ";
    cin >> size;

    MyQueue<Customer> bankQueue(size);
    int choice;

    do
    {
        cout << endl << "===== Bank Queue Menu =====" << endl;
        cout << "1. Add a customer" << endl;
        cout << "2. Serve a customer" << endl;
        cout << "3. Display all waiting customers" << endl;
        cout << "4. Show total customers waiting" << endl;
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
            if (bankQueue.isFull())
            {
                cout << "Queue Overflow! The queue is full. Customer cannot be added" << endl;
                break;
            }
            {
                Customer c;
                cout << "Enter customer name: ";
                cin.getline(c.name, 50);
                cout << "Enter transaction type (Deposit / Withdrawal / Loan Inquiry): ";
                cin.getline(c.transaction, 50);
                bankQueue.enqueue(c);
                cout << c.name << " joined the queue" << endl;
            }
            break;
        case 2:
            if (bankQueue.isEmpty())
            {
                cout << "Queue Underflow! No customers to serve" << endl;
            }
            else
            {
                Customer c = bankQueue.dequeue();
                cout << "Served: " << c.name << " (" << c.transaction << ")" << endl;
            }
            break;
        case 3:
            cout << "Waiting customers:" << endl;
            bankQueue.display();
            break;
        case 4:
            cout << "Total customers waiting: " << bankQueue.size() << endl;
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
