#include <iostream>
#include <cstring>
using namespace std;

class Course
{
protected:
    char courseName[50];

public:
    Course(const char name[])
    {
        strcpy(courseName, name);
    }

    virtual int duration() const = 0;
    virtual void display() const = 0;
    virtual ~Course() {}
};

class OnlineCourse : public Course
{
private:
    int weeks;
    int hoursPerWeek;

public:
    OnlineCourse(const char name[], int w, int h) : Course(name)
    {
        weeks = w;
        hoursPerWeek = h;
    }

    int duration() const override
    {
        return weeks * hoursPerWeek;
    }

    void display() const override
    {
        cout << "Online Course: " << courseName << endl;
        cout << "   " << weeks << " weeks x " << hoursPerWeek << " hours per week" << endl;
        cout << "   Total Duration: " << duration() << " hours" << endl;
    }
};

class OfflineCourse : public Course
{
private:
    int months;
    int hoursPerDay;

public:
    OfflineCourse(const char name[], int m, int h) : Course(name)
    {
        months = m;
        hoursPerDay = h;
    }

    int duration() const override
    {
        return months * 30 * hoursPerDay;
    }

    void display() const override
    {
        cout << "Offline Course: " << courseName << endl;
        cout << "   " << months << " months x 30 days x " << hoursPerDay << " hours per day" << endl;
        cout << "   Total Duration: " << duration() << " hours" << endl;
    }
};

int main()
{
    OnlineCourse online("Web Development", 12, 6);
    OfflineCourse offline("Data Structures", 4, 2);

    Course* courses[2];
    courses[0] = &online;
    courses[1] = &offline;

    for (int i = 0; i < 2; i++)
    {
        courses[i]->display();
        cout << endl;
    }

    return 0;
}
