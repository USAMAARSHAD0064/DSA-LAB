#include <iostream>
using namespace std;

template <typename Type>
class List
{
protected:
    Type* arr;
    int maxSize;
    int currentSize;

public:
    List(int size = 10)
    {
        if (size <= 0)
        {
            size = 10;
        }
        maxSize = size;
        currentSize = 0;
        arr = new Type[maxSize];
    }

    List(const List<Type>& other)
    {
        maxSize = other.maxSize;
        currentSize = other.currentSize;
        arr = new Type[maxSize];
        for (int i = 0; i < currentSize; i++)
        {
            arr[i] = other.arr[i];
        }
    }

    virtual ~List()
    {
        delete[] arr;
    }

    virtual void addElementAtFirstIndex(Type) = 0;
    virtual void addElementAtLastIndex(Type) = 0;
    virtual Type removeElementFromEnd() = 0;
    virtual void removeElementFromStart() = 0;
};

template <typename Type>
class MyList : public List<Type>
{
public:
    MyList(int size = 10) : List<Type>(size)
    {
    }

    MyList(const MyList<Type>& other) : List<Type>(other)
    {
    }

    ~MyList()
    {
    }

    bool empty() const
    {
        return this->currentSize == 0;
    }

    bool full() const
    {
        return this->currentSize == this->maxSize;
    }

    int size() const
    {
        return this->currentSize;
    }

    void addElementAtFirstIndex(Type value) override
    {
        if (full())
        {
            cout << "List is full" << endl;
            return;
        }
        for (int i = this->currentSize; i > 0; i--)
        {
            this->arr[i] = this->arr[i - 1];
        }
        this->arr[0] = value;
        this->currentSize++;
    }

    void addElementAtLastIndex(Type value) override
    {
        if (full())
        {
            cout << "List is full" << endl;
            return;
        }
        this->arr[this->currentSize] = value;
        this->currentSize++;
    }

    Type removeElementFromEnd() override
    {
        if (empty())
        {
            cout << "List is empty" << endl;
            return Type();
        }
        this->currentSize--;
        return this->arr[this->currentSize];
    }

    void removeElementFromStart() override
    {
        if (empty())
        {
            cout << "List is empty" << endl;
            return;
        }
        for (int i = 0; i < this->currentSize - 1; i++)
        {
            this->arr[i] = this->arr[i + 1];
        }
        this->currentSize--;
    }

    bool insertAt(int index, Type value)
    {
        if (full() || index < 0 || index > this->currentSize)
        {
            return false;
        }
        for (int i = this->currentSize; i > index; i--)
        {
            this->arr[i] = this->arr[i - 1];
        }
        this->arr[index] = value;
        this->currentSize++;
        return true;
    }

    Type last() const
    {
        if (empty())
        {
            return Type();
        }
        return this->arr[this->currentSize - 1];
    }

    bool search(Type value) const
    {
        for (int i = 0; i < this->currentSize; i++)
        {
            if (this->arr[i] == value)
            {
                return true;
            }
        }
        return false;
    }

    void display() const
    {
        if (empty())
        {
            cout << "List is empty" << endl;
            return;
        }
        cout << "List: ";
        for (int i = 0; i < this->currentSize; i++)
        {
            cout << this->arr[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    int capacity;
    cout << "Enter maximum size of the list: ";
    cin >> capacity;

    MyList<int> list(capacity);
    int choice, value, index;

    do
    {
        cout << endl << "===== MyList Menu =====" << endl;
        cout << "1. Add element at first index" << endl;
        cout << "2. Add element at last index" << endl;
        cout << "3. Remove element from end" << endl;
        cout << "4. Remove element from start" << endl;
        cout << "5. Insert at index" << endl;
        cout << "6. Check if empty" << endl;
        cout << "7. Check if full" << endl;
        cout << "8. Show size" << endl;
        cout << "9. Show last element" << endl;
        cout << "10. Search element" << endl;
        cout << "11. Display list" << endl;
        cout << "12. Make a copy and display it" << endl;
        cout << "0. Exit" << endl;
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
            list.addElementAtFirstIndex(value);
            list.display();
            break;
        case 2:
            cout << "Enter value: ";
            cin >> value;
            list.addElementAtLastIndex(value);
            list.display();
            break;
        case 3:
            if (list.empty())
            {
                cout << "List is empty" << endl;
            }
            else
            {
                cout << "Removed: " << list.removeElementFromEnd() << endl;
            }
            list.display();
            break;
        case 4:
            list.removeElementFromStart();
            list.display();
            break;
        case 5:
            cout << "Enter index: ";
            cin >> index;
            cout << "Enter value: ";
            cin >> value;
            if (list.insertAt(index, value))
            {
                cout << "Value inserted" << endl;
            }
            else
            {
                cout << "Invalid index or list is full" << endl;
            }
            list.display();
            break;
        case 6:
            cout << (list.empty() ? "List is empty" : "List is not empty") << endl;
            break;
        case 7:
            cout << (list.full() ? "List is full" : "List is not full") << endl;
            break;
        case 8:
            cout << "Size: " << list.size() << endl;
            break;
        case 9:
            if (list.empty())
            {
                cout << "List is empty" << endl;
            }
            else
            {
                cout << "Last element: " << list.last() << endl;
            }
            break;
        case 10:
            cout << "Enter value to search: ";
            cin >> value;
            cout << (list.search(value) ? "Found" : "Not found") << endl;
            break;
        case 11:
            list.display();
            break;
        case 12:
        {
            MyList<int> copyList(list);
            cout << "Copy -> ";
            copyList.display();
            break;
        }
        case 0:
            cout << "Exiting" << endl;
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice != 0);

    return 0;
}
