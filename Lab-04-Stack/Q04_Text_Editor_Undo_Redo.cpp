#include <iostream>
#include <cstring>
using namespace std;

const int TYPE_ACTION = 1;
const int DELETE_ACTION = 2;
const int MAX_TEXT = 500;
const int MAX_PIECE = 100;

struct Action
{
    int type;
    char piece[MAX_PIECE];
};

class ActionStack
{
private:
    Action* arr;
    int maxSize;
    int topIndex;

public:
    ActionStack(int size = 100)
    {
        maxSize = size;
        topIndex = -1;
        arr = new Action[maxSize];
    }

    ~ActionStack()
    {
        delete[] arr;
    }

    bool isEmpty() const
    {
        return topIndex == -1;
    }

    bool isFull() const
    {
        return topIndex == maxSize - 1;
    }

    void push(Action a)
    {
        if (isFull())
        {
            for (int i = 0; i < topIndex; i++)
            {
                arr[i] = arr[i + 1];
            }
            topIndex--;
        }
        topIndex++;
        arr[topIndex] = a;
    }

    Action pop()
    {
        Action a = arr[topIndex];
        topIndex--;
        return a;
    }

    void clear()
    {
        topIndex = -1;
    }

    int size() const
    {
        return topIndex + 1;
    }
};

class TextEditor
{
private:
    char text[MAX_TEXT];
    ActionStack undoStack;
    ActionStack redoStack;

    bool appendText(const char piece[])
    {
        if (strlen(text) + strlen(piece) >= MAX_TEXT)
        {
            return false;
        }
        strcat(text, piece);
        return true;
    }

    void removeFromEnd(int count, char removed[])
    {
        int length = strlen(text);
        strcpy(removed, text + length - count);
        text[length - count] = '\0';
    }

public:
    TextEditor()
    {
        text[0] = '\0';
    }

    void typeText(const char piece[])
    {
        if (strlen(piece) == 0)
        {
            cout << "Nothing to type" << endl;
            return;
        }
        if (!appendText(piece))
        {
            cout << "Text is too long" << endl;
            return;
        }
        Action a;
        a.type = TYPE_ACTION;
        strcpy(a.piece, piece);
        undoStack.push(a);
        redoStack.clear();
        cout << "Typed: \"" << piece << "\"" << endl;
    }

    void deleteText(int count)
    {
        int length = strlen(text);
        if (length == 0)
        {
            cout << "Nothing to delete" << endl;
            return;
        }
        if (count <= 0)
        {
            cout << "Invalid number of characters" << endl;
            return;
        }
        if (count > length)
        {
            count = length;
        }
        if (count >= MAX_PIECE)
        {
            count = MAX_PIECE - 1;
        }
        Action a;
        a.type = DELETE_ACTION;
        removeFromEnd(count, a.piece);
        undoStack.push(a);
        redoStack.clear();
        cout << "Deleted: \"" << a.piece << "\"" << endl;
    }

    void undo()
    {
        if (undoStack.isEmpty())
        {
            cout << "Nothing to undo" << endl;
            return;
        }
        Action a = undoStack.pop();
        if (a.type == TYPE_ACTION)
        {
            char removed[MAX_PIECE];
            removeFromEnd(strlen(a.piece), removed);
            cout << "Undo typing of \"" << a.piece << "\"" << endl;
        }
        else
        {
            appendText(a.piece);
            cout << "Undo deletion of \"" << a.piece << "\"" << endl;
        }
        redoStack.push(a);
    }

    void redo()
    {
        if (redoStack.isEmpty())
        {
            cout << "Nothing to redo" << endl;
            return;
        }
        Action a = redoStack.pop();
        if (a.type == TYPE_ACTION)
        {
            appendText(a.piece);
            cout << "Redo typing of \"" << a.piece << "\"" << endl;
        }
        else
        {
            char removed[MAX_PIECE];
            removeFromEnd(strlen(a.piece), removed);
            cout << "Redo deletion of \"" << a.piece << "\"" << endl;
        }
        undoStack.push(a);
    }

    void showText() const
    {
        cout << "Current text: \"" << text << "\"" << endl;
    }

    void showHistory() const
    {
        cout << "Undo steps available: " << undoStack.size() << endl;
        cout << "Redo steps available: " << redoStack.size() << endl;
    }
};

int main()
{
    TextEditor editor;
    int choice, count;
    char piece[MAX_PIECE];

    do
    {
        cout << endl << "===== Text Editor Menu =====" << endl;
        cout << "1. Type text" << endl;
        cout << "2. Delete characters" << endl;
        cout << "3. Undo" << endl;
        cout << "4. Redo" << endl;
        cout << "5. Show current text" << endl;
        cout << "6. Show history size" << endl;
        cout << "7. Exit" << endl;
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
        cin.ignore(1000, '\n');

        switch (choice)
        {
        case 1:
            cout << "Enter text to type: ";
            cin.getline(piece, MAX_PIECE);
            editor.typeText(piece);
            editor.showText();
            break;
        case 2:
            cout << "How many characters to delete? ";
            cin >> count;
            editor.deleteText(count);
            editor.showText();
            break;
        case 3:
            editor.undo();
            editor.showText();
            break;
        case 4:
            editor.redo();
            editor.showText();
            break;
        case 5:
            editor.showText();
            break;
        case 6:
            editor.showHistory();
            break;
        case 7:
            cout << "Exiting" << endl;
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice != 7);

    return 0;
}
