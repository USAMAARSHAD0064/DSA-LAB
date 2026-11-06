#include <iostream>
#include <cstring>
using namespace std;

class Patient
{
public:
    int id;
    char name[50];
    Patient* next;

    Patient(int patientId, const char patientName[])
    {
        id = patientId;
        strcpy(name, patientName);
        next = nullptr;
    }
};

class PatientQueue
{
private:
    Patient* head;

public:
    PatientQueue()
    {
        head = nullptr;
    }

    void addPatient(int id, const char name[])
    {
        Patient* newPatient = new Patient(id, name);
        if (head == nullptr)
        {
            head = newPatient;
        }
        else
        {
            Patient* temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newPatient;
        }
        cout << "Patient " << name << " (ID " << id << ") added to the queue" << endl;
    }

    void cancelAppointment(int id)
    {
        if (head == nullptr)
        {
            cout << "Queue is empty" << endl;
            return;
        }
        Patient* toDelete;
        if (head->id == id)
        {
            toDelete = head;
            head = head->next;
            cout << "Patient " << toDelete->name << " (ID " << id << ") cancelled and removed" << endl;
            delete toDelete;
            return;
        }
        Patient* temp = head;
        while (temp->next != nullptr && temp->next->id != id)
        {
            temp = temp->next;
        }
        if (temp->next == nullptr)
        {
            cout << "Patient with ID " << id << " not found" << endl;
            return;
        }
        toDelete = temp->next;
        temp->next = toDelete->next;
        cout << "Patient " << toDelete->name << " (ID " << id << ") cancelled and removed" << endl;
        delete toDelete;
    }

    void displayQueue()
    {
        if (head == nullptr)
        {
            cout << "No patients in the queue" << endl;
            return;
        }
        cout << "Current patient queue:" << endl;
        int number = 1;
        Patient* temp = head;
        while (temp != nullptr)
        {
            cout << number << ". " << temp->name << " (ID " << temp->id << ")" << endl;
            temp = temp->next;
            number++;
        }
    }

    int countPatients()
    {
        int count = 0;
        Patient* temp = head;
        while (temp != nullptr)
        {
            count++;
            temp = temp->next;
        }
        return count;
    }

    ~PatientQueue()
    {
        Patient* temp = head;
        while (temp != nullptr)
        {
            Patient* nextPatient = temp->next;
            delete temp;
            temp = nextPatient;
        }
    }
};

int main()
{
    PatientQueue queue;

    cout << "--- Adding patients ---" << endl;
    queue.addPatient(101, "Ahmed");
    queue.addPatient(102, "Sara");
    queue.addPatient(103, "Bilal");
    queue.addPatient(104, "Fatima");
    queue.addPatient(105, "Hamza");

    cout << endl;
    queue.displayQueue();
    cout << "Total patients: " << queue.countPatients() << endl;

    cout << endl << "--- Cancelling appointments ---" << endl;
    queue.cancelAppointment(103);
    queue.cancelAppointment(101);
    queue.cancelAppointment(110);

    cout << endl;
    queue.displayQueue();
    cout << "Total patients: " << queue.countPatients() << endl;

    cout << endl << "--- New patient arrives ---" << endl;
    queue.addPatient(106, "Zainab");

    cout << endl;
    queue.displayQueue();
    cout << "Total patients: " << queue.countPatients() << endl;

    return 0;
}
