#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <chrono>
#include <thread>

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
    int startXPos, startYPos, endXPos = startXPos, endYPos = startYPos, health;
};

struct Bullet
{
    int xPos, yPos;
};

void runGame();
void clearScreen();
void hideCursor();
void mainMenu();
void readSavedGames(string, vector<Spaceship> &spaceships, vector<Bullet> &bullets, int &size, int &goalScore, int &currentScore, int &level);
void autoSave(vector<Spaceship>, vector<Bullet>, int, int, int, int);
void deleteSavedInfo(string);
void mkHistory(string, int, int, int, Spaceship);
void statusBar(int, int, int, int);
void pauseMenu(string);
string selectMode();
void generateGame(string);
void generateMap(int, vector<Spaceship>, vector<Bullet>, int, int);
void move(vector<Spaceship> &spaceships, int &score, int, int &goalScore, char, vector<Bullet> &bullets, int &level);
void shot(vector<Bullet> &bullets, Spaceship);
void gameLog(vector<Spaceship>);
void checkPositions(vector<Spaceship> &spaceships, vector<Bullet> &bullets, int &score, int &goalScore, int, int &level);
void refreshPositions(vector<Spaceship> &spaceships, vector<Bullet> &bullets, int &score, int &goalScore, int, bool, int &level);
void createEnemy(vector<Spaceship> &spaceships, int);
void increaseScore(int &score, string, int &level);
void damage(Spaceship &spaceship);
void gameOver(bool, int &goalScore, int, vector<Spaceship>, int, string);

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
    string start = "Start Game", loadgame = "Load Game", exitOption = "Exit";
    start = colorYellow + start + resetColor;
    int j = 2, GameCount;

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
                cout << "  |            " << start << "           |" << endl;
            }
            else if (i == 4)
            {
                cout << "  |             " << loadgame << "           |" << endl;
            }
            else if (i == 6)
            {
                cout << "  |               " << exitOption << "              |" << endl;
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
            loadgame = "Load Game";
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
                    // addGame() -> GameCout++
                }
                else if (mode == "advanced")
                {
                    generateGame("advanced");
                }
            }
            break;
        case 1:
            start = "Start Game";
            loadgame = colorYellow + loadgame + resetColor;
            exitOption = "Exit";
            if (ch == 13)
            {
                clearScreen();
                string loadMode = selectMode();
                if (loadMode == "back")
                {
                    mainMenu();
                }
                else if (loadMode == "basic")
                {
                    generateGame("basic_load");
                }
                else if (loadMode == "advanced")
                {
                    generateGame("advanced_load");
                }
            }
            break;
        case 0:
            start = "Start Game";
            loadgame = "Load Game";
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

void statusBar(int health, int score, int size, int level)
{
    if (level == -1)
    {
        cout << resetColor << colorRed << "-----------------------------------------------------------------------" << endl;
        cout << "|  p => Pause , e => Exit  |  Health : " << health << " , Score : " << score << " , Map Size : " << size << "  |" << endl;
        cout << "-----------------------------------------------------------------------" << resetColor << endl;
    }
    else
    {
        cout << resetColor << colorRed << "-----------------------------------------------------------------------------------" << endl;
        cout << "|  p => Pause , e => Exit  |  Health : " << health << " , Level : " << level << " , Score : " << score << " , Map Size : " << size << "  |" << endl;
        cout << "-----------------------------------------------------------------------------------" << resetColor << endl;
    }
}

void pauseMenu(string gameType)
{
    char ch;
    string Resume = "Resume", Exit = "Exit";
    Resume = colorYellow + Resume + resetColor;
    int selected = 1;

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
                cout << "  |              " << Resume << "             |" << endl;
            }
            else if (i == 4)
            {
                cout << "  |               " << Exit << "              |" << endl;
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
            selected++;
            if (selected > 1)
                selected = 0;
        }
        else if (ch == 80)
        {
            selected--;
            if (selected < 0)
                selected = 1;
        }

        switch (selected)
        {
        case 1:
            Resume = colorYellow + Resume + resetColor;
            Exit = "Exit";
            if (ch == 13)
            {
                clearScreen();
                generateGame(gameType + "_load");
                return;
            }
            break;
        case 0:
            Resume = "Resume";
            Exit = colorYellow + Exit + resetColor;
            if (ch == 13)
            {
                clearScreen();
                mainMenu();
                return;
            }
        }
    } while (ch != 27);
}

void readSavedGames(string filename, vector<Spaceship> &spaceships, vector<Bullet> &bullets, int &size, int &goalScore, int &currentScore, int &level)
{
    ifstream load;
    load.open(filename);
    string line;
    Bullet bullet;
    Spaceship character;

    if (!load.is_open())
    {
        cout << "There are no games, Please Start a new game" << endl;
        cout << "Enter any key to go back" << endl;
        _getch();
        mainMenu();
    }
    else
    {
        load >> size >> goalScore >> currentScore;
        if (filename == "advanced-savegames.txt")
        {
            load >> level;
        }

        for (int i = 0; i < 2; i++)
        {
            load >> character.type >> character.startXPos >> character.endXPos >> character.startYPos >> character.endYPos >> character.health;
            spaceships.push_back(character);
        }
        while (!load.eof())
        {
            load >> bullet.xPos >> bullet.yPos;
            bullets.push_back(bullet);
        }

        load.close();
    }
}

void autoSave(vector<Spaceship> spaceships, vector<Bullet> bullets, int size, int currentScore, int goalScore, int level)
{
    ofstream output;
    if (level != -1)
    {
        output.open("advanced-savegames.txt");
    }
    else
    {
        output.open("basic-savegames.txt");
    }

    if (!output.is_open())
    {
        cerr << "Can't open file" << endl;
    }
    else
    {
        output << size << " " << goalScore << " " << currentScore;
        if (level != -1)
        {
            output << " " << level;
        }
        output << endl;

        output << spaceships[0].type << " " << spaceships[0].startXPos << " " << spaceships[0].endXPos << " " << spaceships[0].startYPos << " " << spaceships[0].endYPos << " " << spaceships[0].health << endl;
        output << spaceships[spaceships.size() - 1].type << " " << spaceships[spaceships.size() - 1].startXPos << " " << spaceships[spaceships.size() - 1].endXPos << " " << spaceships[spaceships.size() - 1].startYPos << " " << spaceships[spaceships.size() - 1].endYPos << " " << spaceships[spaceships.size() - 1].health << endl;

        for (int i = 0; i < bullets.size(); i++)
        {
            if (i == bullets.size() - 1)
                output << bullets[i].xPos << " " << bullets[i].yPos;
            else
            {
                output << bullets[i].xPos << " " << bullets[i].yPos << " ";
            }
        }

        output.close();
    }
}

void deleteSavedInfo(string gameMode)
{
    if (gameMode == "basic")
    {
        remove("basic-savegames.txt");
    }
    else
    {
        remove("advanced-savegames.txt");
    }
}

void generateGame(string gameType)
{
    int size, goalScore, score, level = -1;
    vector<Spaceship> spaceships;
    vector<Bullet> bullets;
    Spaceship spaceship;

    if (gameType == "basic" || gameType == "advanced")
    {
        score = 0;
        if (gameType == "advanced")
        {
            level = 0;
        }
        do
        {
            cout << "Please Enter the size of the map (minimum 15) : ";
            cin >> size;
            if (size < 15)
            {
                cout << "Notice: The minimum size of map is 15, try a greater size!" << endl;
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
            if (size < 20)
            {
                cout << "Notice: The minimum score is 20, try a greater score!" << endl;
            }
        } while (goalScore < 20);

        spaceship.type = "user";
        spaceship.startYPos = size - 1;
        spaceship.startXPos = size / 2;
        spaceship.health = 3;
        spaceships.push_back(spaceship);
        createEnemy(spaceships, size);
        generateMap(size, spaceships, bullets, score, level);
        autoSave(spaceships, bullets, size, score, goalScore, level);
    }
    else if (gameType == "basic_load" || gameType == "advanced_load")
    {
        clearScreen();
        spaceships.clear();
        bullets.clear();
        if (gameType == "advanced_load")
        {
            readSavedGames("advanced-savegames.txt", spaceships, bullets, size, goalScore, score, level);
        }
        else
        {
            readSavedGames("basic-savegames.txt", spaceships, bullets, size, goalScore, score, level);
        }
        generateMap(size, spaceships, bullets, score, level);
    }

    if (gameType == "advanced" || gameType == "advanced_load")
    {
        while (true)
        {
            this_thread::sleep_for(chrono::milliseconds(500));
            if (_kbhit())
            {
                char ch = _getch();
                if (ch == 'a' || ch == 'd')
                {
                    move(spaceships, score, size, goalScore, ch, bullets, level);
                    generateMap(size, spaceships, bullets, score, level);
                }
                else if (ch == 's')
                {
                    refreshPositions(spaceships, bullets, score, goalScore, size, false, level);
                    shot(bullets, spaceships[0]);
                    checkPositions(spaceships, bullets, score, goalScore, size, level);
                    generateMap(size, spaceships, bullets, score, level);
                }
                else if (ch == 'e')
                {
                    break;
                }
                else if (ch == 'p')
                {
                    pauseMenu("advanced");
                    break;
                }
                autoSave(spaceships, bullets, size, score, goalScore, level);
            }
            else
            {
                refreshPositions(spaceships, bullets, score, goalScore, size, true, level);
                shot(bullets, spaceships[0]);
                checkPositions(spaceships, bullets, score, goalScore, size, level);
                generateMap(size, spaceships, bullets, score, level);
                autoSave(spaceships, bullets, size, score, goalScore, level);
            }
        }
    }
    else
    {
        while (true)
        {
            if (_kbhit())
            {
                char ch = _getch();
                if (ch == 'a' || ch == 'd')
                {
                    move(spaceships, score, size, goalScore, ch, bullets, level);
                    generateMap(size, spaceships, bullets, score, level);
                }
                else if (ch == 's')
                {
                    refreshPositions(spaceships, bullets, score, goalScore, size, false, level);
                    shot(bullets, spaceships[0]);
                    checkPositions(spaceships, bullets, score, goalScore, size, level);
                    generateMap(size, spaceships, bullets, score, level);
                }
                else if (ch == 'e')
                {
                    break;
                }
                else if (ch == 'p')
                {
                    pauseMenu("basic");
                    break;
                }
                autoSave(spaceships, bullets, size, score, goalScore, level);
            }
        }
    }
}

void generateMap(int size, vector<Spaceship> spaceships, vector<Bullet> bullets, int score, int level)
{
    clearScreen();
    statusBar(spaceships[0].health, score, size, level);
    string userSpaceship = "@", enemy = "#", bullet = "^";

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
                cout << enemy << resetColor << " ";
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

void move(vector<Spaceship> &spaceships, int &score, int size, int &goalScore, char direction, vector<Bullet> &bullets, int &level)
{
    checkPositions(spaceships, bullets, score, goalScore, size, level);
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
    spaceships[0].endXPos = spaceships[0].startXPos;
    spaceships[0].endYPos = spaceships[0].startYPos;
    checkPositions(spaceships, bullets, score, goalScore, size, level);
    refreshPositions(spaceships, bullets, score, goalScore, size, false, level);
    shot(bullets, spaceships[0]);
    checkPositions(spaceships, bullets, score, goalScore, size, level);
}

void shot(vector<Bullet> &bullets, Spaceship spaceship)
{
    Bullet newBullet;
    newBullet.xPos = spaceship.startXPos;
    newBullet.yPos = spaceship.startYPos - 1;
    bullets.push_back(newBullet);
}

void checkPositions(vector<Spaceship> &spaceships, vector<Bullet> &bullets, int &score, int &goalScore, int size, int &level)
{
    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets[i].xPos >= spaceships[spaceships.size() - 1].startXPos && bullets[i].xPos <= spaceships[spaceships.size() - 1].endXPos && bullets[i].yPos >= spaceships[spaceships.size() - 1].startYPos && bullets[i].yPos <= spaceships[spaceships.size() - 1].endYPos)
        {
            bullets.erase(bullets.begin() + i);
            damage(spaceships[spaceships.size() - 1]);
            if (spaceships[spaceships.size() - 1].health == 0)
            {
                increaseScore(score, spaceships[spaceships.size() - 1].type, level);
                createEnemy(spaceships, size);
            }
        }
        else if (bullets[i].yPos < 0)
        {
            bullets.erase(bullets.begin() + i);
        }
    }
    if (spaceships[spaceships.size() - 1].endYPos == size - 1)
    {
        damage(spaceships[0]);
        createEnemy(spaceships, size);
    }
    string gameType;
    if (level != -1)
    {
        gameType = "advanced";
    }
    else
    {
        gameType = "basic";
    }

    if (spaceships[0].health == 0)
    {
        gameOver(false, goalScore, score, spaceships, level, gameType);
    }
    if (score >= goalScore && goalScore != -1)
    {
        gameOver(true, goalScore, score, spaceships, level, gameType);
    }
}

void refreshPositions(vector<Spaceship> &spaceships, vector<Bullet> &bullets, int &score, int &goalScore, int size, bool justShot, int &level)
{
    if (!justShot)
    {
        spaceships[spaceships.size() - 1].startYPos++;
        spaceships[spaceships.size() - 1].endYPos++;
    }
    checkPositions(spaceships, bullets, score, goalScore, size, level);

    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i].yPos--;
    }
    checkPositions(spaceships, bullets, score, goalScore, size, level);
}

void createEnemy(vector<Spaceship> &spaceships, int size)
{
    string enemyTypes[4] = {"Dart", "Striker", "Wraith", "Banshee"};
    Spaceship enemy;
    srand(time(0));
    enemy.type = enemyTypes[rand() % 4];
    int startXPos;
    if (enemy.type == enemyTypes[0])
    {
        startXPos = rand() % size;
        enemy.endXPos = startXPos;
        enemy.startYPos = 0;
        enemy.health = 1;
    }
    else if (enemy.type == enemyTypes[1])
    {
        startXPos = rand() % (size - 1);
        enemy.endXPos = startXPos + 1;
        enemy.startYPos = -1;
        enemy.health = 2;
    }
    else if (enemy.type == enemyTypes[2])
    {
        startXPos = rand() % (size - 2);
        enemy.endXPos = startXPos + 2;
        enemy.startYPos = -2;
        enemy.health = 4;
    }
    else
    {
        startXPos = rand() % (size - 3);
        enemy.endXPos = startXPos + 3;
        enemy.startYPos = -3;
        enemy.health = 6;
    }
    enemy.startXPos = startXPos;
    enemy.endYPos = 0;
    spaceships.push_back(enemy);
}

void increaseScore(int &score, string type, int &level)
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
    if (level != -1)
    {
        level = score / 200;
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

void mkHistory(string status, int score, int goalScore, int level, Spaceship spaceship)
{
    if (status == "Win")
    {
        score = goalScore;
    }
    vector<string> datas;
    string data;
    ifstream input("history.txt");
    int counter = 0;
    while (!input.eof() && input.is_open())
    {
        getline(input, data);
        datas.push_back(data);
        if (data != "")
        {
            counter++;
        }
    }
    ofstream output("history.txt");
    for (int i = 0; i < datas.size(); i++)
    {
        if (datas[i] != "")
        {
            output << datas[i] << endl;
        }
    }
    counter++;
    input.close();
    output << "Game " + to_string(counter);
    if (level != -1)
    {
        output << " - Level : " << level;
    }
    output << " - Point : " << score << " - Heal : " << spaceship.health << " - " << status;
    output.close();
}

void gameLog(vector<Spaceship> spaceships)
{
    int dartCount = 0, strikerCount = 0, wraithCount = 0, bansheeCount = 0;
    for (int i = 0; i < spaceships.size(); i++)
    {
        if (spaceships[i].health == 0)
        {
            if (spaceships[i].type == "Dart")
                dartCount++;
            else if (spaceships[i].type == "Striker")
                strikerCount++;
            else if (spaceships[i].type == "Wraith")
                wraithCount++;
            else if (spaceships[i].type == "Banshee")
                bansheeCount++;
        }
    }

    cout << "You've destroyed:" << endl;
    cout << dartCount << " Dart" << endl;
    cout << strikerCount << " Striker" << endl;
    cout << wraithCount << " Wraith" << endl;
    cout << bansheeCount << " Banshee" << endl;
}

void gameOver(bool win, int &goalScore, int score, vector<Spaceship> spaceships, int level, string gameMode)
{
    clearScreen();
    if (win)
    {
        mkHistory("Win", score, goalScore, level, spaceships[0]);
        
        cout << colorGreen
             << "\n"
             << "   \\\\      //\\\\      //  ||    ||\\\\      || \n"
             << "    \\\\    //  \\\\    //   ||    ||  \\\\    || \n"
             << "     \\\\  //    \\\\  //    ||    ||    \\\\  || \n"
             << "      \\\\//      \\\\//     ||    ||      \\\\|| \n"
             << "\n"
             << resetColor;
    
        cout << "\n"
             << "Game Log: "
             << "\n";
        gameLog(spaceships);

        cout << "\n"
             << "Press c for entering the infinite mode or b for going back to the menu";
        char ch;
        do
        {
            ch = _getch();
            switch (ch)
            {
            case 'c':
                goalScore = -1;
                return;
                break;
            case 'b':
                deleteSavedInfo(gameMode);
                mainMenu();
                break;
            }
        } while (ch != 'c' && ch != 'b');
    }
    else
    {
        if (goalScore != -1)
        {
            mkHistory("Lose", score, goalScore, level, spaceships[0]);
        }
        deleteSavedInfo(gameMode);
        cout << colorRed
             << "\n"
             << "   ||             //||||||\\\\       ///|||||\\\\\\    ||\\\\\\\\\\\\\\\\\\\\\n"
             << "   ||            ||        ||      \\\\       //    ||\n"
             << "   ||            ||        ||         \\\\          ||\\\\\\\\\\\\\\\\\\\\\n"
             << "   ||            ||        ||    //       \\\\      ||\n"
             << "   ||\\\\\\\\\\\\\\\\\\    \\\\||||||//     \\\\\\|||||///      ||\\\\\\\\\\\\\\\\\\\\\n"
             << "\n"
             << resetColor;

        cout << "\n"
             << "You've gained " << score << " Points!"
             << "\n";
        cout << "\n"
             << "Game Log: "
             << "\n";
        gameLog(spaceships);
        cout << "\n"
             << "Press any key to back to the main menu"
             << "\n";
        _getch();
        mainMenu();
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
    system("CLS || CLEAR");
    // cls for windows and clear for other operating systems
}