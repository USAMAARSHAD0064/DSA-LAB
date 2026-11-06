#include <iostream>
#include <cstring>
using namespace std;

class Student
{
public:
    int id;
    char name[50];
    int priority;
    Student* next;

    Student(int studentId, const char studentName[], int studentPriority)
    {
        id = studentId;
        strcpy(name, studentName);
        priority = studentPriority;
        next = nullptr;
    }
};

const char* priorityName(int priority)
{
    if (priority == 1)
    {
        return "Research";
    }
    else if (priority == 2)
    {
        return "Assignment";
    }
    return "Casual Reading";
}

class ReservationList
{
private:
    Student* head;
    char bookTitle[100];

    void insertByPriority(Student* newStudent)
    {
        if (head == nullptr || newStudent->priority < head->priority)
        {
            newStudent->next = head;
            head = newStudent;
            return;
        }
        Student* temp = head;
        while (temp->next != nullptr && temp->next->priority <= newStudent->priority)
        {
            temp = temp->next;
        }
        newStudent->next = temp->next;
        temp->next = newStudent;
    }

    Student* detachStudent(int id)
    {
        if (head == nullptr)
        {
            return nullptr;
        }
        Student* found;
        if (head->id == id)
        {
            found = head;
            head = head->next;
            found->next = nullptr;
            return found;
        }
        Student* temp = head;
        while (temp->next != nullptr && temp->next->id != id)
        {
            temp = temp->next;
        }
        if (temp->next == nullptr)
        {
            return nullptr;
        }
        found = temp->next;
        temp->next = found->next;
        found->next = nullptr;
        return found;
    }

public:
    ReservationList()
    {
        head = nullptr;
        strcpy(bookTitle, "Untitled");
    }

    void setTitle(const char title[])
    {
        strcpy(bookTitle, title);
    }

    void addStudent(int id, const char name[], int priority = 3)
    {
        if (priority < 1 || priority > 3)
        {
            priority = 3;
        }
        Student* newStudent = new Student(id, name, priority);
        insertByPriority(newStudent);
        cout << name << " (ID " << id << ") reserved \"" << bookTitle << "\" with priority: " << priorityName(priority) << endl;
    }

    void cancelReservation(int id)
    {
        Student* removed = detachStudent(id);
        if (removed == nullptr)
        {
            cout << "Student with ID " << id << " not found in \"" << bookTitle << "\" list" << endl;
            return;
        }
        cout << removed->name << " (ID " << id << ") cancelled reservation for \"" << bookTitle << "\"" << endl;
        delete removed;
    }

    void updatePriority(int id, int newPriority)
    {
        if (newPriority < 1 || newPriority > 3)
        {
            cout << "Invalid priority" << endl;
            return;
        }
        Student* student = detachStudent(id);
        if (student == nullptr)
        {
            cout << "Student with ID " << id << " not found in \"" << bookTitle << "\" list" << endl;
            return;
        }
        student->priority = newPriority;
        insertByPriority(student);
        cout << student->name << " (ID " << id << ") priority updated to " << priorityName(newPriority) << " for \"" << bookTitle << "\"" << endl;
    }

    void displayList()
    {
        cout << "Reservation list for \"" << bookTitle << "\":" << endl;
        if (head == nullptr)
        {
            cout << "   No reservations" << endl;
            return;
        }
        int number = 1;
        Student* temp = head;
        while (temp != nullptr)
        {
            cout << "   " << number << ". " << temp->name << " (ID " << temp->id << ") - " << priorityName(temp->priority) << endl;
            temp = temp->next;
            number++;
        }
    }

    int countStudents()
    {
        int count = 0;
        Student* temp = head;
        while (temp != nullptr)
        {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void bookReturned()
    {
        cout << "\"" << bookTitle << "\" has been returned" << endl;
        if (head == nullptr)
        {
            cout << "No students waiting. Book is now available on the shelf" << endl;
            return;
        }
        Student* served = head;
        head = head->next;
        cout << "Book issued to " << served->name << " (ID " << served->id << ") and removed from the list" << endl;
        delete served;
    }

    ~ReservationList()
    {
        Student* temp = head;
        while (temp != nullptr)
        {
            Student* nextStudent = temp->next;
            delete temp;
            temp = nextStudent;
        }
    }
};

int main()
{
    ReservationList books[2];
    books[0].setTitle("Introduction to Algorithms");
    books[1].setTitle("Database System Concepts");

    cout << "===== Adding Reservations =====" << endl;
    books[0].addStudent(1, "Ali", 3);
    books[0].addStudent(2, "Ayesha", 2);
    books[0].addStudent(3, "Usman", 1);
    books[0].addStudent(4, "Hira");
    books[0].addStudent(5, "Danish", 2);

    cout << endl;
    books[1].addStudent(6, "Maryam", 2);
    books[1].addStudent(7, "Hassan", 3);
    books[1].addStudent(8, "Noor", 1);
    books[1].addStudent(2, "Ayesha", 3);

    cout << endl;
    books[0].displayList();
    cout << "Total students: " << books[0].countStudents() << endl;
    cout << endl;
    books[1].displayList();
    cout << "Total students: " << books[1].countStudents() << endl;

    cout << endl << "===== Cancelling Reservations =====" << endl;
    books[0].cancelReservation(5);
    books[1].cancelReservation(7);
    books[1].cancelReservation(20);

    cout << endl;
    books[0].displayList();
    cout << "Total students: " << books[0].countStudents() << endl;
    cout << endl;
    books[1].displayList();
    cout << "Total students: " << books[1].countStudents() << endl;

    cout << endl << "===== Updating Priority =====" << endl;
    books[0].updatePriority(1, 1);
    books[1].updatePriority(2, 1);

    cout << endl;
    books[0].displayList();
    cout << endl;
    books[1].displayList();

    cout << endl << "===== Books Returned =====" << endl;
    books[0].bookReturned();
    books[0].displayList();
    cout << "Total students: " << books[0].countStudents() << endl;
    cout << endl;
    books[1].bookReturned();
    books[1].displayList();
    cout << "Total students: " << books[1].countStudents() << endl;

    return 0;
}
