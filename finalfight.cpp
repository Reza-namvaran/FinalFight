#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <fstream>

#define colorBlue "\033[0;34m"
#define colorRed "\033[0;31m"
#define colorYellow "\033[33m"
#define resetColor "\033[0m"

using namespace std;

struct postion
{
    int x_Position;
    int y_Position;
};

void runGame();
void clearScreen();
void hideCursor();
void mainMenu();
void generateMap(int size, int state, vector<vector<string>> &map);
void move(vector<vector<string>> &map, int size, char direction);

int main()
{
    runGame();
    return 0;
}

void runGame()
{
    clearScreen();
    hideCursor();
    mainMenu();
    int size;
    cout << "Please Enter the size of the map: ";
    cin >> size;
    if (size % 2 == 0)
    {
        cout << "Notice: You've entered an Even number for the size while it should be an odd number!" << endl;
        cout << "The size has incremented by one automatically. Press any key to continue" << endl;
        _getch();
        size++;
    }
    vector<vector<string>> map(size, vector<string>(size));
    generateMap(size, 0, map);

    while (true)
    {
        if (_kbhit())
        {
            char ch = _getch();
            if (ch == 'a' || ch == 'd')
            {
                move(map, size, ch);
                generateMap(size, 1, map);
            }
            else if (ch == 'p')
            {
                break;
            }
        }
    }
}

void mainMenu()
{
    char ch;
    string start = "Start Game", change = "Change Spaceship", exitOption = "Exit";
    start = colorYellow + start + resetColor;
    int j = 2;

    do
    {
        clearScreen();
        cout << "__|";
        for (int i = 0; i < 33; i++)
        {
            cout << "_";
        }
        cout << "|__" << endl;

        for (int i = 0; i < 10; i++)
        {
            if (i == 2)
            {
                cout << "  |           " << start << "            |" << endl;
            }
            else if (i == 4)
            {
                cout << "  |        " << change << "         |" << endl;
            }
            else if (i == 6)
            {
                cout << "  |              " << exitOption << "               |" << endl;
            }
            else
            {
                cout << "  |";
                for (int j = 0; j < 33; j++)
                {
                    cout << " ";
                }
                cout << "|" << endl;
            }
        }

        cout << "__|";
        for (int i = 0; i < 33; i++)
        {
            cout << "_";
        }
        cout << "|__" << endl;
        for (int i = 0; i < 37; i++)
        {
            if (i == 2 || i == 36)
            {
                cout << "|";
            }
            else
            {
                cout << " ";
            }
        }
        ch = _getch();

        if (ch == 72)
        {
            j++;
            if (j > 2)
                j = 0;
        }
        else if (ch == 80)
        {
            j--;
            if (j < 0)
                j = 2;
        }

        switch (j)
        {
        case 2:
            start = colorYellow + start + resetColor;
            change = "Change Spaceship";
            exitOption = "Exit";
            if (ch == 13)
            {
                clearScreen();
                return;
            }
            break;
        case 1:
            start = "Start Game";
            change = colorYellow + change + resetColor;
            exitOption = "Exit";
            break;
        case 0:
            start = "Start Game";
            change = "Change Spaceship";
            exitOption = colorYellow + exitOption + resetColor;
            if (ch == 13)
            {
                clearScreen();
                exit(0);
            }
        }
    } while (ch != 27);
    exit(0);
}

void generateMap(int size, int state, vector<vector<string>> &map)
{
    clearScreen();
    string space = "#";

    if (state == 0)
    {
        map[size - 1][size / 2] = space;
    }
    for (int i = 0; i <= size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << colorBlue << " ---" << resetColor;
        }

        cout << endl;

        if (i == size)
            continue;

        for (int k = 0; k < size; k++)
        {
            if (map[i][k] == "#")
            {
                cout << colorBlue << "| " << resetColor << colorRed << space << resetColor << " ";
            }
            else
            {
                cout << colorBlue << "|   " << resetColor;
            }
            if (k == size - 1)
            {
                cout << colorBlue << "|" << resetColor;
            }
        }

        cout << endl;
    }
}

void move(vector<vector<string>> &map, int size, char direction)
{
    for (int j = 0; j < size; ++j)
    {
        if (map[size - 1][j] == "#")
        {
            map[size - 1][j] = " ";
            if (direction == 'a' && j > 0)
            {
                map[size - 1][j - 1] = "#";
            }
            else if (direction == 'd' && j < size - 1)
            {
                map[size - 1][j + 1] = "#";
            }
            else if (j == 0 || j == size - 1)
                map[size - 1][j] = "#";
            return;
        }
    }
}

void hideCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

// this function is used when we want to clear the terminal screen
void clearScreen()
{
#ifdef _WIN32
    // for windows
    system("CLS");
#else
    // for other operating systems
    system("clear");
#endif
}