#include <iostream>
#include <cstring>
using namespace std;

template <typename T>
void selectionSort(T arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            T temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

template <typename T>
int linearSearch(T arr[], int n, const char key[])
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i].matches(key))
        {
            return i;
        }
    }
    return -1;
}

class LibraryItem
{
protected:
    char title[100];

public:
    LibraryItem(const char t[] = "")
    {
        strcpy(title, t);
    }

    bool matches(const char key[]) const
    {
        return strcmp(title, key) == 0;
    }

    virtual void display() const = 0;
    virtual ~LibraryItem() {}
};

class Book : public LibraryItem
{
private:
    char author[100];
    int pages;

public:
    Book(const char t[] = "", const char a[] = "", int p = 0) : LibraryItem(t)
    {
        strcpy(author, a);
        pages = p;
    }

    bool operator<(const Book& other) const
    {
        return pages < other.pages;
    }

    void display() const override
    {
        cout << "Book: " << title << " | Author: " << author << " | Pages: " << pages << endl;
    }
};

class Newspaper : public LibraryItem
{
private:
    char date[20];
    char edition[50];

public:
    Newspaper(const char n[] = "", const char d[] = "", const char e[] = "") : LibraryItem(n)
    {
        strcpy(date, d);
        strcpy(edition, e);
    }

    bool operator<(const Newspaper& other) const
    {
        return strcmp(edition, other.edition) < 0;
    }

    void display() const override
    {
        cout << "Newspaper: " << title << " | Date: " << date << " | Edition: " << edition << endl;
    }
};

class Library
{
private:
    static const int MAX = 20;
    Book books[MAX];
    Newspaper newspapers[MAX];
    int bookCount;
    int newspaperCount;

public:
    Library()
    {
        bookCount = 0;
        newspaperCount = 0;
    }

    void addBook(const Book& b)
    {
        if (bookCount < MAX)
        {
            books[bookCount] = b;
            bookCount++;
        }
        else
        {
            cout << "Library is full of books" << endl;
        }
    }

    void addNewspaper(const Newspaper& n)
    {
        if (newspaperCount < MAX)
        {
            newspapers[newspaperCount] = n;
            newspaperCount++;
        }
        else
        {
            cout << "Library is full of newspapers" << endl;
        }
    }

    void displayCollection() const
    {
        for (int i = 0; i < bookCount; i++)
        {
            books[i].display();
        }
        for (int i = 0; i < newspaperCount; i++)
        {
            newspapers[i].display();
        }
    }

    void sortBooksByPages()
    {
        selectionSort(books, bookCount);
    }

    void sortNewspapersByEdition()
    {
        selectionSort(newspapers, newspaperCount);
    }

    Book* searchBookByTitle(const char title[])
    {
        int index = linearSearch(books, bookCount, title);
        if (index == -1)
        {
            return nullptr;
        }
        return &books[index];
    }

    Newspaper* searchNewspaperByName(const char name[])
    {
        int index = linearSearch(newspapers, newspaperCount, name);
        if (index == -1)
        {
            return nullptr;
        }
        return &newspapers[index];
    }
};

int main() {
    Book book1("The Catcher in the Rye", "J.D. Salinger", 277);
    Book book2("To Kill a Mockingbird", "Harper Lee", 324);

    Newspaper newspaper1("Washington Post", "2024-10-13", "Morning Edition");
    Newspaper newspaper2("The Times", "2024-10-12", "Weekend Edition");

    Library library;

    library.addBook(book1);
    library.addBook(book2);
    library.addNewspaper(newspaper1);
    library.addNewspaper(newspaper2);

    cout << "Before Sorting:\n";
    library.displayCollection();

    library.sortBooksByPages();
    library.sortNewspapersByEdition();

    cout << "\nAfter Sorting:\n";
    library.displayCollection();

    Book* foundBook = library.searchBookByTitle("The Catcher in the Rye");
    if (foundBook) {
        cout << "\nFound Book:\n";
        foundBook->display();
    } else {
        cout << "\nBook not found.\n";
    }

    Newspaper* foundNewspaper = library.searchNewspaperByName("The Times");
    if (foundNewspaper) {
        cout << "\nFound Newspaper:\n";
        foundNewspaper->display();
    } else {
        cout << "\nNewspaper not found.\n";
    }

    return 0;
}
