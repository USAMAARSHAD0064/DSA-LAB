#include <iostream>
using namespace std;

class TicketQueue
{
private:
    int* tickets;
    int maxSize;
    int frontIndex;
    int rearIndex;
    int count;

public:
    TicketQueue(int size = 20)
    {
        maxSize = size;
        tickets = new int[maxSize];
        frontIndex = 0;
        rearIndex = -1;
        count = 0;
    }

    ~TicketQueue()
    {
        delete[] tickets;
    }

    bool isEmpty() const
    {
        return count == 0;
    }

    bool isFull() const
    {
        return count == maxSize;
    }

    bool exists(int ticket_id) const
    {
        for (int i = 0; i < count; i++)
        {
            if (tickets[(frontIndex + i) % maxSize] == ticket_id)
            {
                return true;
            }
        }
        return false;
    }

    void enqueue(int ticket_id)
    {
        if (ticket_id < 1000 || ticket_id > 9999)
        {
            cout << "Ticket ID must be exactly 4 digits (1000 - 9999)" << endl;
            return;
        }
        if (exists(ticket_id))
        {
            cout << "Ticket #" << ticket_id << " already exists. IDs must be unique" << endl;
            return;
        }
        if (isFull())
        {
            cout << "Ticket queue is full" << endl;
            return;
        }
        rearIndex = (rearIndex + 1) % maxSize;
        tickets[rearIndex] = ticket_id;
        count++;
        cout << "Ticket #" << ticket_id << " added to the queue" << endl;
    }

    void dequeue()
    {
        if (isEmpty())
        {
            cout << "No pending tickets to resolve" << endl;
            return;
        }
        int ticket_id = tickets[frontIndex];
        frontIndex = (frontIndex + 1) % maxSize;
        count--;
        cout << "Ticket #" << ticket_id << " resolved and removed" << endl;
    }

    void front() const
    {
        if (isEmpty())
        {
            cout << "No pending tickets" << endl;
            return;
        }
        cout << "Next ticket to resolve: #" << tickets[frontIndex] << endl;
    }

    void display() const
    {
        if (isEmpty())
        {
            cout << "No pending tickets" << endl;
            return;
        }
        cout << "Pending tickets (" << count << "): ";
        for (int i = 0; i < count; i++)
        {
            cout << "#" << tickets[(frontIndex + i) % maxSize] << " ";
        }
        cout << endl;
    }
};

int main()
{
    TicketQueue queue(20);
    int choice, ticket_id;

    do
    {
        cout << endl << "===== Customer Support Tickets =====" << endl;
        cout << "1. Add a new ticket" << endl;
        cout << "2. Resolve next ticket" << endl;
        cout << "3. Check next ticket" << endl;
        cout << "4. Display all pending tickets" << endl;
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
            cout << "Enter 4-digit ticket ID: ";
            cin >> ticket_id;
            queue.enqueue(ticket_id);
            break;
        case 2:
            queue.dequeue();
            break;
        case 3:
            queue.front();
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
