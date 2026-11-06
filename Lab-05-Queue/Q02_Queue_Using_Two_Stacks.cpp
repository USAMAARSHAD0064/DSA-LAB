#include <iostream>
using namespace std;

template <typename T>
class Stack
{
private:
    T* arr;
    int maxSize;
    int topIndex;

public:
    Stack(int size = 10)
    {
        maxSize = size;
        topIndex = -1;
        arr = new T[maxSize];
    }

    ~Stack()
    {
        delete[] arr;
    }

    bool isEmpty() const
    {
        return topIndex == -1;
    }

    bool isFull() const
    {
        return topIndex == maxSize - 1;
    }

    void push(T value)
    {
        topIndex++;
        arr[topIndex] = value;
    }

    T pop()
    {
        T value = arr[topIndex];
        topIndex--;
        return value;
    }

    T top() const
    {
        return arr[topIndex];
    }

    int size() const
    {
        return topIndex + 1;
    }

    T at(int index) const
    {
        return arr[index];
    }
};

template <typename T>
class QueueUsingStacks
{
private:
    Stack<T> inStack;
    Stack<T> outStack;
    int maxSize;

    void transfer()
    {
        if (outStack.isEmpty())
        {
            while (!inStack.isEmpty())
            {
                outStack.push(inStack.pop());
            }
        }
    }

public:
    QueueUsingStacks(int size = 10) : inStack(size), outStack(size)
    {
        maxSize = size;
    }

    bool isEmpty() const
    {
        return inStack.isEmpty() && outStack.isEmpty();
    }

    bool isFull() const
    {
        return inStack.size() + outStack.size() == maxSize;
    }

    void enqueue(T value)
    {
        if (isFull())
        {
            cout << "Queue is full! Cannot add " << value << endl;
            return;
        }
        inStack.push(value);
        cout << value << " added to the queue" << endl;
    }

    T dequeue()
    {
        if (isEmpty())
        {
            cout << "Queue is empty! Nothing to remove" << endl;
            return T();
        }
        transfer();
        return outStack.pop();
    }

    T front()
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return T();
        }
        transfer();
        return outStack.top();
    }

    void display() const
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return;
        }
        cout << "Queue (front to rear): ";
        for (int i = outStack.size() - 1; i >= 0; i--)
        {
            cout << outStack.at(i) << " ";
        }
        for (int i = 0; i < inStack.size(); i++)
        {
            cout << inStack.at(i) << " ";
        }
        cout << endl;
    }
};

int main()
{
    int size;
    cout << "Enter maximum size of the queue: ";
    cin >> size;

    QueueUsingStacks<int> queue(size);
    int choice, value;

    do
    {
        cout << endl << "===== Queue Using Two Stacks =====" << endl;
        cout << "1. Enqueue" << endl;
        cout << "2. Dequeue" << endl;
        cout << "3. Front element" << endl;
        cout << "4. Display elements" << endl;
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

        switch (choice)
        {
        case 1:
            cout << "Enter value: ";
            cin >> value;
            queue.enqueue(value);
            break;
        case 2:
            if (!queue.isEmpty())
            {
                cout << "Dequeued: " << queue.dequeue() << endl;
            }
            else
            {
                queue.dequeue();
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
            queue.display();
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
