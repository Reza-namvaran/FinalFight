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

struct Spaceship
{
    string type;
    int startXPos, startYPos, endXPos, endYPos, health;
};

struct Bullet
{
    int xPos, yPos;
};

void runGame();
void clearScreen();
void hideCursor();
void mainMenu();
string selectMode();
void generateGame(string);
void generateMap(int, vector<vector<string>> &map, Spaceship spaceship);
void move(Spaceship &spaceship, int, char);

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
                string mode = selectMode();
                if (mode == "back")
                {
                    mainMenu();
                }
                else if (mode == "basic")
                {
                    generateGame("basic");
                }
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

string selectMode()
{
    char ch;
    string basic = "Basic", advanced = "Advanced", back = "<- Back";
    basic = colorYellow + basic + resetColor;
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
                cout << "  |              " << basic << "              |" << endl;
            }
            else if (i == 4)
            {
                cout << "  |             " << advanced << "            |" << endl;
            }
            else if (i == 6)
            {
                cout << "  |             " << back << "             |" << endl;
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
            basic = colorYellow + basic + resetColor;
            advanced = "Advanced";
            back = "<- Back";
            if (ch == 13)
            {
                clearScreen();
                return "basic";
            }
            break;
        case 1:
            basic = "Basic";
            advanced = colorYellow + advanced + resetColor;
            back = "<- Back";
            if (ch == 13)
            {
                clearScreen();
                return "advanced";
            }
            break;
        case 0:
            basic = "Basic";
            advanced = "Advanced";
            back = colorYellow + back + resetColor;
            if (ch == 13)
            {
                clearScreen();
                return "back";
            }
        }
    } while (ch != 27);
    return "back";
}

void runningMenu()
{
    cout << resetColor << colorRed << "----------------------------" << endl;
    cout << "|  p => Pause , e => Exit  |" << endl;
    cout << "----------------------------" << resetColor << endl;
}

void generateGame(string gameType)
{
    if (gameType == "basic")
    {
        int size;
        do
        {
            cout << "Please Enter the size of the map: ";
            cin >> size;
            if (size < 15)
            {
                cout << "Notice: The minimum size of map is 15, try greater size!" << endl;
            }
        } while (size < 15);
        if (size % 2 == 0)
        {
            cout << "Notice: You've entered an Even number for the size while it should be an odd number!" << endl;
            cout << "The size has incremented by one automatically. Press any key to continue" << endl;
            _getch();
            size++;
        }
        vector<vector<string>> map(size, vector<string>(size));
        vector<Spaceship> spaceships;
        vector<Bullet> bullets;
        Spaceship spaceship;
        spaceship.type = "user";
        spaceship.startYPos = size - 1;
        spaceship.startXPos = size / 2;
        spaceship.health = 3;
        spaceships.push_back(spaceship);
        generateMap(size, map, spaceships[0]);

        while (true)
        {
            if (_kbhit())
            {
                char ch = _getch();
                if (ch == 'a' || ch == 'd')
                {
                    move(spaceships[0], size, ch);
                    generateMap(size, map, spaceships[0]);
                }
                else if (ch == 'e')
                {
                    break;
                }
                else if (ch == 'p')
                {
                    // save game
                    break;
                }
            }
        }
    }
    else
    {
        /* code */
    }
}

void generateMap(int size, vector<vector<string>> &map, Spaceship spaceship)
{
    clearScreen();
    runningMenu();
    string space = "#";

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
            if (i == spaceship.startYPos && k == spaceship.startXPos)
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

void move(Spaceship &spaceship, int size, char direction)
{
    switch (direction)
    {
    case 'a':
        if (spaceship.startXPos > 0)
        {
            spaceship.startXPos--;
        }
        break;
    case 'd':
        if (spaceship.startXPos < size - 1)
        {
            spaceship.startXPos++;
        }
        break;
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