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

template <typename Type>
class CustomList : public MyList<Type>
{
private:
    bool isPrime(int n) const
    {
        if (n < 2)
        {
            return false;
        }
        for (int i = 2; i * i <= n; i++)
        {
            if (n % i == 0)
            {
                return false;
            }
        }
        return true;
    }

    void rotateRight(int start, int end, int times)
    {
        int length = end - start;
        if (length <= 1)
        {
            return;
        }
        times = times % length;
        for (int t = 0; t < times; t++)
        {
            Type lastValue = this->arr[end - 1];
            for (int i = end - 1; i > start; i--)
            {
                this->arr[i] = this->arr[i - 1];
            }
            this->arr[start] = lastValue;
        }
    }

    void rotateLeft(int start, int end, int times)
    {
        int length = end - start;
        if (length <= 1)
        {
            return;
        }
        times = times % length;
        for (int t = 0; t < times; t++)
        {
            Type firstValue = this->arr[start];
            for (int i = start; i < end - 1; i++)
            {
                this->arr[i] = this->arr[i + 1];
            }
            this->arr[end - 1] = firstValue;
        }
    }

public:
    bool found;

    CustomList(int size = 10) : MyList<Type>(size)
    {
        found = false;
    }

    CustomList(const CustomList<Type>& other) : MyList<Type>(other)
    {
        found = other.found;
    }

    ~CustomList()
    {
    }

    Type sum_ofPrime()
    {
        Type sum = 0;
        for (int i = 0; i < this->currentSize; i++)
        {
            if (isPrime((int)this->arr[i]))
            {
                sum = sum + this->arr[i];
            }
        }
        return sum;
    }

    Type secondMaxEven()
    {
        bool hasMax = false;
        bool hasSecond = false;
        Type maxValue = 0;
        Type secondMax = 0;
        for (int i = 0; i < this->currentSize; i++)
        {
            Type value = this->arr[i];
            if ((int)value % 2 != 0)
            {
                continue;
            }
            if (!hasMax || value > maxValue)
            {
                if (hasMax)
                {
                    secondMax = maxValue;
                    hasSecond = true;
                }
                maxValue = value;
                hasMax = true;
            }
            else if (value < maxValue && (!hasSecond || value > secondMax))
            {
                secondMax = value;
                hasSecond = true;
            }
        }
        found = hasSecond;
        return secondMax;
    }

    Type secondMinOdd()
    {
        bool hasMin = false;
        bool hasSecond = false;
        Type minValue = 0;
        Type secondMin = 0;
        for (int i = 0; i < this->currentSize; i++)
        {
            Type value = this->arr[i];
            if ((int)value % 2 == 0)
            {
                continue;
            }
            if (!hasMin || value < minValue)
            {
                if (hasMin)
                {
                    secondMin = minValue;
                    hasSecond = true;
                }
                minValue = value;
                hasMin = true;
            }
            else if (value > minValue && (!hasSecond || value < secondMin))
            {
                secondMin = value;
                hasSecond = true;
            }
        }
        found = hasSecond;
        return secondMin;
    }

    void printDuplicates()
    {
        bool anyDuplicate = false;
        cout << "Duplicates: ";
        for (int i = 0; i < this->currentSize; i++)
        {
            bool printedBefore = false;
            for (int k = 0; k < i; k++)
            {
                if (this->arr[k] == this->arr[i])
                {
                    printedBefore = true;
                    break;
                }
            }
            if (printedBefore)
            {
                continue;
            }
            int count = 0;
            for (int j = 0; j < this->currentSize; j++)
            {
                if (this->arr[j] == this->arr[i])
                {
                    count++;
                }
            }
            if (count > 1)
            {
                cout << this->arr[i] << " (" << count << " times)  ";
                anyDuplicate = true;
            }
        }
        if (!anyDuplicate)
        {
            cout << "none";
        }
        cout << endl;
    }

    void rotateClockwaise(int r)
    {
        int half = this->currentSize / 2;
        rotateRight(0, half, r);
        rotateRight(half, this->currentSize, r);
    }

    void rotateanitclockwaise(int rt)
    {
        int half = this->currentSize / 2;
        rotateLeft(0, half, rt);
        rotateLeft(half, this->currentSize, rt);
    }
};

int main()
{
    int capacity;
    cout << "Enter maximum size of the list: ";
    cin >> capacity;

    CustomList<int> list(capacity);
    int choice, value, count;

    do
    {
        cout << endl << "===== CustomList Menu =====" << endl;
        cout << "1. Add element at last index" << endl;
        cout << "2. Add element at first index" << endl;
        cout << "3. Display list" << endl;
        cout << "4. Sum of prime numbers" << endl;
        cout << "5. Second maximum even number" << endl;
        cout << "6. Second minimum odd number" << endl;
        cout << "7. Print duplicates" << endl;
        cout << "8. Rotate clockwise" << endl;
        cout << "9. Rotate anti-clockwise" << endl;
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
            cout << "How many values? ";
            cin >> count;
            cout << "Enter values: ";
            for (int i = 0; i < count; i++)
            {
                cin >> value;
                list.addElementAtLastIndex(value);
            }
            list.display();
            break;
        case 2:
            cout << "Enter value: ";
            cin >> value;
            list.addElementAtFirstIndex(value);
            list.display();
            break;
        case 3:
            list.display();
            break;
        case 4:
            cout << "Sum of primes: " << list.sum_ofPrime() << endl;
            break;
        case 5:
            value = list.secondMaxEven();
            if (list.found)
            {
                cout << "Second maximum even: " << value << endl;
            }
            else
            {
                cout << "Second maximum even does not exist" << endl;
            }
            break;
        case 6:
            value = list.secondMinOdd();
            if (list.found)
            {
                cout << "Second minimum odd: " << value << endl;
            }
            else
            {
                cout << "Second minimum odd does not exist" << endl;
            }
            break;
        case 7:
            list.printDuplicates();
            break;
        case 8:
            cout << "Enter number of rotations: ";
            cin >> value;
            list.rotateClockwaise(value);
            list.display();
            break;
        case 9:
            cout << "Enter number of rotations: ";
            cin >> value;
            list.rotateanitclockwaise(value);
            list.display();
            break;
        case 0:
            cout << "Exiting" << endl;
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice != 0);

    return 0;
}
