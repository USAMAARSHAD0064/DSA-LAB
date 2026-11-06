#include <iostream>
using namespace std;

class Queue
{
private:
    int* arr;
    int maxSize;
    int frontIndex;
    int rearIndex;
    int count;

public:
    Queue(int size = 10)
    {
        if (size <= 0)
        {
            size = 1;
        }
        maxSize = size;
        arr = new int[maxSize];
        frontIndex = 0;
        rearIndex = -1;
        count = 0;
    }

    ~Queue()
    {
        delete[] arr;
    }

    bool isEmpty() const
    {
        return count == 0;
    }

    bool isFull() const
    {
        return count == maxSize;
    }

    int size() const
    {
        return count;
    }

    void enqueue(int value)
    {
        if (isFull())
        {
            cout << "Queue is full" << endl;
            return;
        }
        rearIndex = (rearIndex + 1) % maxSize;
        arr[rearIndex] = value;
        count++;
    }

    int dequeue()
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return -1;
        }
        int value = arr[frontIndex];
        frontIndex = (frontIndex + 1) % maxSize;
        count--;
        return value;
    }

    int front() const
    {
        if (isEmpty())
        {
            return -1;
        }
        return arr[frontIndex];
    }

    void display() const
    {
        for (int i = 0; i < count; i++)
        {
            cout << arr[(frontIndex + i) % maxSize] << " ";
        }
        cout << endl;
    }
};

class Stack
{
private:
    int* arr;
    int topIndex;

public:
    Stack(int size)
    {
        if (size <= 0)
        {
            size = 1;
        }
        arr = new int[size];
        topIndex = -1;
    }

    ~Stack()
    {
        delete[] arr;
    }

    bool isEmpty() const
    {
        return topIndex == -1;
    }

    void push(int value)
    {
        topIndex++;
        arr[topIndex] = value;
    }

    int pop()
    {
        int value = arr[topIndex];
        topIndex--;
        return value;
    }
};

void reverseFirstK(Queue& queue, int k)
{
    int n = queue.size();
    if (k > n)
    {
        cout << "K is greater than queue size, so the whole queue is reversed" << endl;
        k = n;
    }
    if (k <= 1)
    {
        cout << "No reversal needed" << endl;
        return;
    }

    Stack stack(k);
    for (int i = 0; i < k; i++)
    {
        stack.push(queue.dequeue());
    }
    while (!stack.isEmpty())
    {
        queue.enqueue(stack.pop());
    }
    for (int i = 0; i < n - k; i++)
    {
        queue.enqueue(queue.dequeue());
    }
}

int main()
{
    int n, k, value;

    cout << "Enter number of elements: ";
    cin >> n;
    if (n < 0)
    {
        n = 0;
    }

    Queue queue(n);
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++)
    {
        cin >> value;
        queue.enqueue(value);
    }

    cout << "Enter K: ";
    cin >> k;
    if (k < 0)
    {
        k = 0;
    }

    cout << "Queue: ";
    queue.display();
    cout << "K=" << k << endl;

    reverseFirstK(queue, k);

    cout << "Output: ";
    queue.display();

    return 0;
}
