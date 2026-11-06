#include <iostream>
#include <cstring>
using namespace std;

struct Package
{
    int packageID;
    char address[100];
    int startTime;
    int endTime;
};

void printTime(int time)
{
    int hours = time / 100;
    int minutes = time % 100;
    if (hours < 10)
    {
        cout << "0";
    }
    cout << hours << ":";
    if (minutes < 10)
    {
        cout << "0";
    }
    cout << minutes;
}

bool validTime(int time)
{
    return time >= 0 && time <= 2359 && time % 100 < 60;
}

class PackageQueue
{
private:
    Package* packages;
    int maxSize;
    int frontIndex;
    int rearIndex;
    int count;

    void printPackage(const Package& p) const
    {
        cout << "ID " << p.packageID << " | " << p.address << " | Window ";
        printTime(p.startTime);
        cout << " - ";
        printTime(p.endTime);
        cout << endl;
    }

public:
    PackageQueue(int size = 20)
    {
        maxSize = size;
        packages = new Package[maxSize];
        frontIndex = 0;
        rearIndex = -1;
        count = 0;
    }

    ~PackageQueue()
    {
        delete[] packages;
    }

    bool isEmpty() const
    {
        return count == 0;
    }

    bool isFull() const
    {
        return count == maxSize;
    }

    void enqueue(const Package& p)
    {
        if (isFull())
        {
            cout << "Delivery queue is full" << endl;
            return;
        }
        rearIndex = (rearIndex + 1) % maxSize;
        packages[rearIndex] = p;
        count++;
        cout << "Package " << p.packageID << " added to the delivery queue" << endl;
    }

    Package dequeue()
    {
        Package p = packages[frontIndex];
        frontIndex = (frontIndex + 1) % maxSize;
        count--;
        return p;
    }

    void front() const
    {
        if (isEmpty())
        {
            cout << "No packages in the queue" << endl;
            return;
        }
        cout << "Front package: ";
        printPackage(packages[frontIndex]);
    }

    void display() const
    {
        if (isEmpty())
        {
            cout << "No packages in the queue" << endl;
            return;
        }
        cout << "Packages in queue (" << count << "):" << endl;
        for (int i = 0; i < count; i++)
        {
            cout << "   " << i + 1 << ". ";
            printPackage(packages[(frontIndex + i) % maxSize]);
        }
    }

    void timeToDeliver(int currentTime)
    {
        while (!isEmpty())
        {
            Package& p = packages[frontIndex];
            if (currentTime > p.endTime)
            {
                cout << "EXPIRED: Package " << p.packageID << " missed its window (ended at ";
                printTime(p.endTime);
                cout << "). Skipping to next package" << endl;
                dequeue();
            }
            else if (currentTime < p.startTime)
            {
                cout << "Package " << p.packageID << " cannot be delivered yet. Window opens at ";
                printTime(p.startTime);
                cout << endl;
                return;
            }
            else
            {
                Package delivered = dequeue();
                cout << "DELIVERED: Package " << delivered.packageID << " to " << delivered.address << " at ";
                printTime(currentTime);
                cout << endl;
                return;
            }
        }
        cout << "No packages left to deliver" << endl;
    }
};

int readTime(const char prompt[])
{
    int time;
    do
    {
        cout << prompt;
        cin >> time;
        if (!cin)
        {
            return 0;
        }
        if (!validTime(time))
        {
            cout << "Invalid time. Use 24-hour HHMM format, e.g. 930 or 1745" << endl;
        }
    } while (!validTime(time));
    return time;
}

int main()
{
    PackageQueue queue(20);
    int choice;
    int currentTime = 900;

    Package p1 = {501, "House 12, Gulberg", 900, 1100};
    Package p2 = {502, "Plot 7, DHA Phase 5", 800, 930};
    Package p3 = {503, "Shop 3, Liberty Market", 1300, 1500};
    queue.enqueue(p1);
    queue.enqueue(p2);
    queue.enqueue(p3);

    do
    {
        cout << endl << "===== Package Delivery System =====" << endl;
        cout << "Current time: ";
        printTime(currentTime);
        cout << endl;
        cout << "1. Add a new package" << endl;
        cout << "2. Deliver front package (timeToDeliver)" << endl;
        cout << "3. Show front package" << endl;
        cout << "4. Display all packages" << endl;
        cout << "5. Set current time" << endl;
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
        {
            Package p;
            cout << "Enter package ID: ";
            cin >> p.packageID;
            cin.ignore(1000, '\n');
            cout << "Enter delivery address: ";
            cin.getline(p.address, 100);
            p.startTime = readTime("Enter window start (HHMM): ");
            p.endTime = readTime("Enter window end (HHMM): ");
            if (p.endTime < p.startTime)
            {
                cout << "End time cannot be before start time. Package not added" << endl;
            }
            else
            {
                queue.enqueue(p);
            }
            break;
        }
        case 2:
            queue.timeToDeliver(currentTime);
            break;
        case 3:
            queue.front();
            break;
        case 4:
            queue.display();
            break;
        case 5:
            currentTime = readTime("Enter current time (HHMM): ");
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
