#include <iostream>
using namespace std;

template <typename T>
class AbstractQueue
{
public:
    virtual void enQueue(T value) = 0;
    virtual T deQueue() = 0;
    virtual T front() const = 0;
    virtual bool isEmpty() const = 0;
    virtual bool isFull() const = 0;
    virtual ~AbstractQueue() {}
};

template <typename T>
class myQueue : public AbstractQueue<T>
{
private:
    T* arr;
    int maxSize;
    int frontIndex;
    int rearIndex;
    int count;

public:
    myQueue(int size = 10)
    {
        if (size <= 0)
        {
            size = 10;
        }
        maxSize = size;
        arr = new T[maxSize];
        frontIndex = 0;
        rearIndex = -1;
        count = 0;
    }

    ~myQueue()
    {
        delete[] arr;
    }

    void enQueue(T value) override
    {
        if (isFull())
        {
            cout << "Queue Overflow! Cannot add " << value << endl;
            return;
        }
        rearIndex = (rearIndex + 1) % maxSize;
        arr[rearIndex] = value;
        count++;
    }

    T deQueue() override
    {
        if (isEmpty())
        {
            cout << "Queue Underflow! Nothing to remove" << endl;
            return T();
        }
        T value = arr[frontIndex];
        frontIndex = (frontIndex + 1) % maxSize;
        count--;
        return value;
    }

    T front() const override
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return T();
        }
        return arr[frontIndex];
    }

    bool isEmpty() const override
    {
        return count == 0;
    }

    bool isFull() const override
    {
        return count == maxSize;
    }

    void display() const
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return;
        }
        cout << "Queue (front to rear): ";
        for (int i = 0; i < count; i++)
        {
            cout << arr[(frontIndex + i) % maxSize] << " ";
        }
        cout << endl;
    }
};

int main()
{
    int size;
    cout << "Enter maximum size of the queue: ";
    cin >> size;

    myQueue<int> queue(size);
    int choice, value;

    do
    {
        cout << endl << "===== Queue Menu =====" << endl;
        cout << "1. Enqueue element" << endl;
        cout << "2. Dequeue element" << endl;
        cout << "3. Show front element" << endl;
        cout << "4. Check if queue is empty" << endl;
        cout << "5. Check if queue is full" << endl;
        cout << "6. Display queue elements" << endl;
        cout << "7. Exit" << endl;
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
            cout << "Enter value: ";
            cin >> value;
            queue.enQueue(value);
            break;
        case 2:
            if (!queue.isEmpty())
            {
                cout << "Dequeued: " << queue.deQueue() << endl;
            }
            else
            {
                queue.deQueue();
            }
            break;
        case 3:
            if (!queue.isEmpty())
            {
                cout << "Front element: " << queue.front() << endl;
            }
            else
            {
                queue.front();
            }
            break;
        case 4:
            cout << (queue.isEmpty() ? "Queue is empty" : "Queue is not empty") << endl;
            break;
        case 5:
            cout << (queue.isFull() ? "Queue is full" : "Queue is not full") << endl;
            break;
        case 6:
            queue.display();
            break;
        case 7:
            cout << "Exiting" << endl;
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice != 7);

    return 0;
}
