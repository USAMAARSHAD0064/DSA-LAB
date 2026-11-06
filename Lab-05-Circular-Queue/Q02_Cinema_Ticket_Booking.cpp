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

struct Booking
{
    int customerID;
    char customerName[50];
    int numberOfTickets;

    void print() const
    {
        cout << "ID " << customerID << " | " << customerName << " | Tickets: " << numberOfTickets << endl;
    }
};

int main()
{
    int size;
    cout << "Enter maximum number of bookings: ";
    cin >> size;

    MyQueue<Booking> bookings(size);
    int choice;

    do
    {
        cout << endl << "===== Cinema Booking Menu =====" << endl;
        cout << "1. Book tickets" << endl;
        cout << "2. Cancel the first booking" << endl;
        cout << "3. Display the next booking" << endl;
        cout << "4. Display all bookings" << endl;
        cout << "5. Show the total number of bookings" << endl;
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
            if (bookings.isFull())
            {
                cout << "Queue Overflow! No more bookings can be taken right now" << endl;
                break;
            }
            {
                Booking b;
                cout << "Enter customer ID: ";
                cin >> b.customerID;
                cin.ignore(1000, '\n');
                cout << "Enter customer name: ";
                cin.getline(b.customerName, 50);
                cout << "Enter number of tickets: ";
                cin >> b.numberOfTickets;
                if (b.numberOfTickets <= 0)
                {
                    cout << "Number of tickets must be at least 1" << endl;
                    break;
                }
                bookings.enqueue(b);
                cout << "Booking added for " << b.customerName << endl;
            }
            break;
        case 2:
            if (bookings.isEmpty())
            {
                cout << "Queue Underflow! No bookings to cancel" << endl;
            }
            else
            {
                Booking b = bookings.dequeue();
                cout << "Cancelled booking: ";
                b.print();
            }
            break;
        case 3:
            if (bookings.isEmpty())
            {
                cout << "No bookings" << endl;
            }
            else
            {
                cout << "Next booking: ";
                bookings.peek().print();
            }
            break;
        case 4:
            cout << "All bookings:" << endl;
            bookings.display();
            break;
        case 5:
            cout << "Total bookings: " << bookings.size() << endl;
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
