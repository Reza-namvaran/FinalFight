#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <ctime>

#define colorBlue "\033[0;34m"
#define colorRed "\033[0;31m"
#define colorWhite "\u001b[37m"
#define colorYellow "\033[33m"
#define colorGreen "\u001b[32m"
#define colorMagenta "\u001b[35m"
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
void runningMenu(int, int, int);
string selectMode();
void generateGame(string);
void generateMap(int, vector<vector<string>> &map, vector<Spaceship>, vector<Bullet>, int);
void move(vector<Spaceship> &spaceships, int &score, int, int, char, vector<Bullet> &bullets);
void checkPositions(vector<Spaceship> &spaceships, vector<Bullet> &bullets, int &score, int, int);
void createEnemy(vector<Spaceship> &spaceships, int);
void increaseScore(int &score, string);
void damage(Spaceship &spaceship);
void gameOver(bool);

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

void runningMenu(int health, int score, int size)
{
    cout << resetColor << colorRed << "-----------------------------------------------------------------------" << endl;
    cout << "|  p => Pause , e => Exit  |  Health : " << health << " , Score : " << score << " , Map Size : " << size << "  |" << endl;
    cout << "-----------------------------------------------------------------------" << resetColor << endl;
}

void generateGame(string gameType)
{
    if (gameType == "basic")
    {
        int size, goalScore;
        do
        {
            cout << "Please Enter the size of the map (minimum 15) : ";
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

        do
        {
            cout << "Please Enter your goal score (minimum 20) : ";
            cin >> goalScore;
            if (size < 15)
            {
                cout << "Notice: The minimum score is 20, try greater score!" << endl;
            }
        } while (goalScore < 20);

        int score = 0;
        vector<vector<string>> map(size, vector<string>(size));
        vector<Spaceship> spaceships;
        vector<Bullet> bullets;
        Spaceship spaceship;
        spaceship.type = "user";
        spaceship.startYPos = size - 1;
        spaceship.startXPos = size / 2;
        spaceship.health = 3;
        spaceships.push_back(spaceship);
        createEnemy(spaceships, size);
        generateMap(size, map, spaceships, bullets, score);

        while (true)
        {
            if (_kbhit())
            {
                char ch = _getch();
                if (ch == 'a' || ch == 'd')
                {
                    move(spaceships, score, size, goalScore, ch, bullets);
                    generateMap(size, map, spaceships, bullets, score);
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

void generateMap(int size, vector<vector<string>> &map, vector<Spaceship> spaceships, vector<Bullet> bullets, int score)
{
    clearScreen();
    runningMenu(spaceships[0].health, score, size);
    string userSpaceship = "#", enemy = "*", bullet = "^";

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
            bool isBullet = false;
            for (int h = 0; h < bullets.size(); h++)
            {
                if (i == bullets[h].yPos && k == bullets[h].xPos)
                {
                    isBullet = true;
                    cout << colorBlue << "| " << resetColor << colorRed << bullet << resetColor << " ";
                }
            }
            if (i == spaceships[0].startYPos && k == spaceships[0].startXPos)
            {
                cout << colorBlue << "| " << resetColor << colorRed << userSpaceship << resetColor << " ";
            }
            else if (i >= spaceships[spaceships.size() - 1].startYPos && i <= spaceships[spaceships.size() - 1].endYPos && k >= spaceships[spaceships.size() - 1].startXPos && k <= spaceships[spaceships.size() - 1].endXPos)
            {
                cout << colorBlue << "| " << resetColor;
                if (spaceships[spaceships.size() - 1].type == "Dart")
                {
                    cout << colorWhite;
                }
                else if (spaceships[spaceships.size() - 1].type == "Striker")
                {
                    cout << colorGreen;
                }
                else if (spaceships[spaceships.size() - 1].type == "Wraith")
                {
                    cout << colorYellow;
                }
                else
                {
                    cout << colorMagenta;
                }
                cout << userSpaceship << resetColor << " ";
            }
            else
            {
                if (!isBullet)
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

void move(vector<Spaceship> &spaceships, int &score, int size, int goalScore, char direction, vector<Bullet> &bullets)
{
    checkPositions(spaceships, bullets, score, goalScore, size);
    switch (direction)
    {
    case 'a':
        if (spaceships[0].startXPos > 0)
        {
            spaceships[0].startXPos--;
        }
        break;
    case 'd':
        if (spaceships[0].startXPos < size - 1)
        {
            spaceships[0].startXPos++;
        }
        break;
    }
    checkPositions(spaceships, bullets, score, goalScore, size);

    spaceships[spaceships.size() - 1].startYPos++;
    spaceships[spaceships.size() - 1].endYPos++;
    checkPositions(spaceships, bullets, score, goalScore, size);

    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i].yPos--;
    }
    checkPositions(spaceships, bullets, score, goalScore, size);

    Bullet newBullet;
    newBullet.xPos = spaceships[0].startXPos;
    newBullet.yPos = spaceships[0].startYPos - 1;
    bullets.push_back(newBullet);
    checkPositions(spaceships, bullets, score, goalScore, size);
}

void checkPositions(vector<Spaceship> &spaceships, vector<Bullet> &bullets, int &score, int goalScore, int size)
{
    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets[i].xPos >= spaceships[spaceships.size() - 1].startXPos && bullets[i].xPos <= spaceships[spaceships.size() - 1].endXPos && bullets[i].yPos >= spaceships[spaceships.size() - 1].startYPos && bullets[i].yPos <= spaceships[spaceships.size() - 1].endYPos)
        {
            bullets.erase(bullets.begin() + i);
            damage(spaceships[spaceships.size() - 1]);
            if (spaceships[spaceships.size() - 1].health == 0)
            {
                increaseScore(score, spaceships[spaceships.size() - 1].type);
                createEnemy(spaceships, size);
            }
        }
    }
    if (spaceships[spaceships.size() - 1].endYPos == size - 1)
    {
        spaceships[spaceships.size() - 1].health = 0;
        damage(spaceships[0]);
        createEnemy(spaceships, size);
    }
    if (spaceships[0].health == 0)
    {
        gameOver(false);
    }
    if (score >= goalScore)
    {
        gameOver(true);
    }
}

void createEnemy(vector<Spaceship> &spaceships, int size)
{
    string enemyTypes[4] = {"Dart", "Striker", "Wraith", "Banshee"};
    Spaceship enemy;
    srand(time(0));
    enemy.type = enemyTypes[rand() % 4];
    if (enemy.type == enemyTypes[0])
    {
        int startXPos = rand() % size;
        enemy.startXPos = startXPos;
        enemy.endXPos = enemy.startXPos;
        enemy.startYPos = 0;
        enemy.endYPos = 0;
        enemy.health = 1;
    }
    else if (enemy.type == enemyTypes[1])
    {
        int startXPos = rand() % (size - 1);
        enemy.startXPos = startXPos;
        enemy.endXPos = startXPos + 1;
        enemy.startYPos = -1;
        enemy.endYPos = 0;
        enemy.health = 2;
    }
    else if (enemy.type == enemyTypes[2])
    {
        int startXPos = rand() % (size - 2);
        enemy.startXPos = startXPos;
        enemy.endXPos = startXPos + 2;
        enemy.startYPos = -2;
        enemy.endYPos = 0;
        enemy.health = 4;
    }
    else
    {
        int startXPos = rand() % (size - 3);
        enemy.startXPos = startXPos;
        enemy.endXPos = startXPos + 3;
        enemy.startYPos = -3;
        enemy.endYPos = 0;
        enemy.health = 6;
    }
    spaceships.push_back(enemy);
}

void increaseScore(int &score, string type)
{
    if (type == "Dart")
    {
        score += 2;
    }
    else if (type == "Striker")
    {
        score += 8;
    }
    else if (type == "Wraith")
    {
        score += 18;
    }
    else
    {
        score += 32;
    }
}

void damage(Spaceship &spaceship)
{
    if (spaceship.health != 0)
    {
        spaceship.health--;
        return;
    }
}

void gameOver(bool win)
{
    clearScreen();
    if (win)
    {
        cout << "You win!" << endl;
    }
    else
    {
        cout << "You lose!" << endl;
    }
    cout << "press any key to back to main menu" << endl;
    _getch();
    mainMenu();
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