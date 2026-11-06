#include <iostream>
#include <cstring>
using namespace std;

class Employee
{
protected:
    char name[50];

public:
    Employee(const char n[])
    {
        strcpy(name, n);
    }

    virtual double calculateSalary() const = 0;

    void printSalary() const
    {
        cout << name << " Salary: Rs. " << calculateSalary() << endl;
    }

    virtual ~Employee() {}
};

class FullTimeEmployee : public Employee
{
private:
    double fixedSalary;

public:
    FullTimeEmployee(const char n[], double salary) : Employee(n)
    {
        fixedSalary = salary;
    }

    void setSalary(double salary)
    {
        fixedSalary = salary;
    }

    double calculateSalary() const override
    {
        return fixedSalary;
    }
};

class PartTimeEmployee : public Employee
{
private:
    double hoursWorked;
    double hourlyRate;

public:
    PartTimeEmployee(const char n[], double hours, double rate) : Employee(n)
    {
        hoursWorked = hours;
        hourlyRate = rate;
    }

    void setDetails(double hours, double rate)
    {
        hoursWorked = hours;
        hourlyRate = rate;
    }

    double calculateSalary() const override
    {
        return hoursWorked * hourlyRate;
    }
};

int main()
{
    FullTimeEmployee fullTime("Ahmed", 0);
    PartTimeEmployee partTime("Sara", 0, 0);

    fullTime.setSalary(85000);
    partTime.setDetails(60, 750);

    cout << "Full-Time Employee" << endl;
    fullTime.printSalary();

    cout << endl << "Part-Time Employee (60 hours x Rs. 750)" << endl;
    partTime.printSalary();

    return 0;
}
