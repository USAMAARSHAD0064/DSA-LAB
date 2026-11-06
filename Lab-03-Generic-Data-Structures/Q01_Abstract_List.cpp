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
class DemoList : public List<Type>
{
public:
    DemoList(int size = 10) : List<Type>(size)
    {
    }

    DemoList(const DemoList<Type>& other) : List<Type>(other)
    {
    }

    void addElementAtFirstIndex(Type value) override
    {
        if (this->currentSize == this->maxSize)
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
        if (this->currentSize == this->maxSize)
        {
            cout << "List is full" << endl;
            return;
        }
        this->arr[this->currentSize] = value;
        this->currentSize++;
    }

    Type removeElementFromEnd() override
    {
        if (this->currentSize == 0)
        {
            cout << "List is empty" << endl;
            return Type();
        }
        this->currentSize--;
        return this->arr[this->currentSize];
    }

    void removeElementFromStart() override
    {
        if (this->currentSize == 0)
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

    void display() const
    {
        cout << "[ ";
        for (int i = 0; i < this->currentSize; i++)
        {
            cout << this->arr[i] << " ";
        }
        cout << "]  size = " << this->currentSize << "/" << this->maxSize << endl;
    }
};

int main()
{
    DemoList<int> list(5);

    list.addElementAtLastIndex(20);
    list.addElementAtLastIndex(30);
    list.addElementAtFirstIndex(10);
    cout << "After adding 20, 30 at end and 10 at start: ";
    list.display();

    DemoList<int> copyList(list);
    cout << "Copied list: ";
    copyList.display();

    cout << "Removed from end: " << list.removeElementFromEnd() << endl;
    list.removeElementFromStart();
    cout << "After removing from start: ";
    list.display();

    cout << "Copied list is unchanged: ";
    copyList.display();

    list.addElementAtLastIndex(1);
    list.addElementAtLastIndex(2);
    list.addElementAtLastIndex(3);
    list.addElementAtLastIndex(4);
    cout << "Trying to add to a full list: ";
    list.addElementAtLastIndex(5);
    list.display();

    DemoList<double> doubleList(3);
    doubleList.addElementAtLastIndex(2.5);
    doubleList.addElementAtFirstIndex(1.5);
    cout << "Double list: ";
    doubleList.display();

    return 0;
}
