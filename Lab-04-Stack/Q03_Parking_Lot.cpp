#include <iostream>
using namespace std;

class myCarStack
{
private:
    int* cars;
    int maxSize;
    int topIndex;

public:
    myCarStack(int size = 8)
    {
        maxSize = size;
        topIndex = -1;
        cars = new int[maxSize];
    }

    ~myCarStack()
    {
        delete[] cars;
    }

    bool isEmpty() const
    {
        return topIndex == -1;
    }

    bool isFull() const
    {
        return topIndex == maxSize - 1;
    }

    void push(int carNumber)
    {
        if (isFull())
        {
            return;
        }
        topIndex++;
        cars[topIndex] = carNumber;
    }

    int pop()
    {
        if (isEmpty())
        {
            return -1;
        }
        int carNumber = cars[topIndex];
        topIndex--;
        return carNumber;
    }

    int top() const
    {
        if (isEmpty())
        {
            return -1;
        }
        return cars[topIndex];
    }

    int size() const
    {
        return topIndex + 1;
    }

    bool search(int carNumber) const
    {
        for (int i = 0; i <= topIndex; i++)
        {
            if (cars[i] == carNumber)
            {
                return true;
            }
        }
        return false;
    }

    void display() const
    {
        if (isEmpty())
        {
            cout << "Parking lot is empty" << endl;
            return;
        }
        cout << "Cars parked (exit side first): ";
        for (int i = topIndex; i >= 0; i--)
        {
            cout << cars[i] << " ";
        }
        cout << endl;
    }
};

class ParkingLot
{
private:
    myCarStack lot;

public:
    ParkingLot() : lot(8)
    {
    }

    void parkCar(int carNumber)
    {
        if (lot.isFull())
        {
            cout << "Parking lot is full (8 cars). Car " << carNumber << " cannot park" << endl;
            return;
        }
        if (lot.search(carNumber))
        {
            cout << "Car " << carNumber << " is already parked" << endl;
            return;
        }
        lot.push(carNumber);
        cout << "Car " << carNumber << " parked" << endl;
    }

    void removeCar(int carNumber)
    {
        if (lot.isEmpty())
        {
            cout << "Parking lot is empty" << endl;
            return;
        }
        if (!lot.search(carNumber))
        {
            cout << "Car " << carNumber << " is not in the parking lot" << endl;
            return;
        }

        myCarStack temp(8);
        while (lot.top() != carNumber)
        {
            int moved = lot.pop();
            cout << "Car " << moved << " moved out temporarily" << endl;
            temp.push(moved);
        }

        lot.pop();
        cout << "Car " << carNumber << " has left the parking lot" << endl;

        while (!temp.isEmpty())
        {
            int moved = temp.pop();
            lot.push(moved);
            cout << "Car " << moved << " parked back" << endl;
        }
    }

    void searchCar(int carNumber) const
    {
        if (lot.search(carNumber))
        {
            cout << "Car " << carNumber << " is parked in the lot" << endl;
        }
        else
        {
            cout << "Car " << carNumber << " is not in the lot" << endl;
        }
    }

    void showCars() const
    {
        lot.display();
    }

    void showTotal() const
    {
        cout << "Total cars parked: " << lot.size() << " / 8" << endl;
    }
};

int main()
{
    ParkingLot parking;
    int choice, carNumber;

    do
    {
        cout << endl << "===== Parking Lot Menu =====" << endl;
        cout << "1. Park a new car" << endl;
        cout << "2. Remove a car by car number" << endl;
        cout << "3. View cars currently parked" << endl;
        cout << "4. Total cars parked" << endl;
        cout << "5. Search for a car" << endl;
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
            cout << "Enter car number: ";
            cin >> carNumber;
            parking.parkCar(carNumber);
            break;
        case 2:
            cout << "Enter car number to remove: ";
            cin >> carNumber;
            parking.removeCar(carNumber);
            break;
        case 3:
            parking.showCars();
            break;
        case 4:
            parking.showTotal();
            break;
        case 5:
            cout << "Enter car number to search: ";
            cin >> carNumber;
            parking.searchCar(carNumber);
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
