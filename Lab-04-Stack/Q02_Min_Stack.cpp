#include <iostream>
using namespace std;

template <typename T>
class AbstractStack
{
public:
    virtual void push(T value) = 0;
    virtual T pop() = 0;
    virtual T top() const = 0;
    virtual bool isEmpty() const = 0;
    virtual bool isFull() const = 0;
    virtual ~AbstractStack() {}
};

template <typename T>
class myStack : public AbstractStack<T>
{
private:
    T* arr;
    int maxSize;
    int topIndex;

    T* minArr;
    int minTop;

public:
    myStack(int size = 10)
    {
        if (size <= 0)
        {
            size = 10;
        }
        maxSize = size;
        topIndex = -1;
        arr = new T[maxSize];
        minTop = -1;
        minArr = new T[maxSize];
    }

    ~myStack()
    {
        delete[] arr;
        delete[] minArr;
    }

    void push(T value) override
    {
        if (isFull())
        {
            cout << "Stack Overflow! Cannot push " << value << endl;
            return;
        }
        topIndex++;
        arr[topIndex] = value;

        if (minTop == -1 || value <= minArr[minTop])
        {
            minTop++;
            minArr[minTop] = value;
        }
    }

    T pop() override
    {
        if (isEmpty())
        {
            cout << "Stack Underflow! Nothing to pop" << endl;
            return T();
        }
        T value = arr[topIndex];
        topIndex--;

        if (value == minArr[minTop])
        {
            minTop--;
        }
        return value;
    }

    T top() const override
    {
        if (isEmpty())
        {
            cout << "Stack is empty" << endl;
            return T();
        }
        return arr[topIndex];
    }

    bool isEmpty() const override
    {
        return topIndex == -1;
    }

    bool isFull() const override
    {
        return topIndex == maxSize - 1;
    }

    T getMin() const
    {
        if (isEmpty())
        {
            cout << "Stack is empty" << endl;
            return T();
        }
        return minArr[minTop];
    }

    void display() const
    {
        if (isEmpty())
        {
            cout << "Stack is empty" << endl;
            return;
        }
        cout << "Stack (top to bottom): ";
        for (int i = topIndex; i >= 0; i--)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    int size;
    cout << "Enter maximum size of the stack: ";
    cin >> size;

    myStack<int> stack(size);
    int choice, value;

    do
    {
        cout << endl << "===== Stack Menu =====" << endl;
        cout << "1. Push element" << endl;
        cout << "2. Pop element" << endl;
        cout << "3. Show top element" << endl;
        cout << "4. Check if stack is empty" << endl;
        cout << "5. Check if stack is full" << endl;
        cout << "6. Display stack elements" << endl;
        cout << "7. Show minimum element" << endl;
        cout << "8. Exit" << endl;
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
            stack.push(value);
            break;
        case 2:
            if (!stack.isEmpty())
            {
                cout << "Popped: " << stack.pop() << endl;
            }
            else
            {
                stack.pop();
            }
            break;
        case 3:
            if (!stack.isEmpty())
            {
                cout << "Top element: " << stack.top() << endl;
            }
            else
            {
                stack.top();
            }
            break;
        case 4:
            cout << (stack.isEmpty() ? "Stack is empty" : "Stack is not empty") << endl;
            break;
        case 5:
            cout << (stack.isFull() ? "Stack is full" : "Stack is not full") << endl;
            break;
        case 6:
            stack.display();
            break;
        case 7:
            if (!stack.isEmpty())
            {
                cout << "Minimum element: " << stack.getMin() << endl;
            }
            else
            {
                stack.getMin();
            }
            break;
        case 8:
            cout << "Exiting" << endl;
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice != 8);

    return 0;
}
