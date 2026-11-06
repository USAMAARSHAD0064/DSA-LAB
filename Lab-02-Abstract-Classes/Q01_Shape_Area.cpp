#include <iostream>
using namespace std;

class Shape
{
public:
    virtual double area() const = 0;
    virtual void display() const = 0;
    virtual ~Shape() {}
};

class Circle : public Shape
{
private:
    double radius;

public:
    Circle(double r)
    {
        radius = r;
    }

    double area() const override
    {
        return 3.14159 * radius * radius;
    }

    void display() const override
    {
        cout << "Circle (radius = " << radius << ") Area: " << area() << endl;
    }
};

class Rectangle : public Shape
{
private:
    double length;
    double width;

public:
    Rectangle(double l, double w)
    {
        length = l;
        width = w;
    }

    double area() const override
    {
        return length * width;
    }

    void display() const override
    {
        cout << "Rectangle (length = " << length << ", width = " << width << ") Area: " << area() << endl;
    }
};

int main()
{
    Circle circle(5.0);
    Rectangle rectangle(4.0, 6.0);

    Shape* shapes[2];
    shapes[0] = &circle;
    shapes[1] = &rectangle;

    for (int i = 0; i < 2; i++)
    {
        shapes[i]->display();
    }

    return 0;
}
