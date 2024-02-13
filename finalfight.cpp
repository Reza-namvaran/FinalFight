#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <fstream>


#define colorBlue "\033[0;34m"
#define colorRed "\033[0;31m" 
#define colorYellow "\033[33m"
#define resetColor "\033[0m"

struct postion
{
    int x_Posiotion;
    int y_Posiotion;
};


void runGame();
void clearScreen();
void hideCursor();
void mainMenu();
void generateMap(int size, int state, std::vector<std::vector<std::string>> & map);
void move(std::vector<std::vector<std::string>> &map, int size, char direction);

int main(){
    runGame();
    return 0;
}

void runGame(){
    clearScreen();
    hideCursor();
    mainMenu();
    int size;
    std::cout << "Please Enter the size of the map: ";
    std::cin >> size;
    if(size % 2 == 0)
    {
        std::cout << "Notice: You've entered an Even number for the size while it should be an odd number!" << std::endl;
        std::cout << "The size has incremented by one automatically. Press any key to continue" << std::endl;
        _getch();
        size++; 
    }   
    std::vector<std::vector<std::string>> map(size, std::vector<std::string>(size));
    generateMap(size, 0, map);

    while (true) {
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 'a' || ch == 'd') {
                move(map, size, ch);
                generateMap(size, 1, map);
            } else if (ch == 'p') {
                break;
            }
        }
    }
}

void mainMenu(){
    char ch;
    std::string start = "Start Game", change = "Change Spaceship", exit = "Exit";
    int j = 2;
    

    do
    {
        clearScreen();
        std::cout << "__|";
        for(int i = 0; i < 33; i++){
            std::cout << "_";
        }
        std::cout << "|__" << std::endl;

        

        for(int i = 0; i < 10; i++){
            if(i == 2)
            {
                std::cout << "  |           " << start << "            |" <<  std::endl;
            }
            else if(i == 4)
            {
                std::cout << "  |        " << change << "         |" << std::endl;
            }
            else if(i == 6)
            {
                std::cout << "  |              " << exit << "               |" << std::endl;
            }
            else
            {
                std::cout << "  |";
                for(int j = 0; j < 33; j++){
                    std::cout << " ";
                }
                std::cout << "|" << std::endl;
            }
        }
        
        std::cout << "__|";
        for (int i = 0; i < 33; i++){
            std::cout << "_";
        }
        std::cout << "|__" << std::endl;
        for(int i = 0; i < 37; i++){
            if(i == 2 || i == 36){
                std::cout << "|";
            }
            else{
                std::cout << " ";
            }
        }
        ch = _getch();

        if (ch == 72)
        {
            j++;
            if(j > 2)
                j = 0;
        }
        else if (ch == 80)
        {
            j--;
            if(j < 0)
                j = 2;
        }

        switch (j)
        {
        case 2:
            start = colorYellow + start + resetColor;
            change = "Change Spaceship"; 
            exit = "Exit";
            if(ch == 13){
                clearScreen();
                return;
            }
            break;
        
        case 1:
            start = "Start Game";
            change = colorYellow + change + resetColor;
            exit = "Exit";
            break;
        case 0:
            start = "Start Game";
            change = "Change Spaceship";
            exit = colorYellow + exit + resetColor;
            if(ch == 13){
                clearScreen();
                std::exit(0);
            }
        }
    } while (ch != 27);
    std::exit(0);
    
}

void generateMap(int size, int state, std::vector<std::vector<std::string>> & map){
    clearScreen();
    std::string space = "#";

    
    if (state == 0)
    { 
        map[size - 1][size / 2] = space;
    }
    for(int i = 0; i <= size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            std::cout << colorBlue << " ---" << resetColor;
        }

        std::cout << std::endl;

        if(i == size)
            continue;

        for(int k = 0; k < size; k++)
        {   
            if (map[i][k] == "#")
            {
            std::cout << colorBlue << "| " << resetColor << colorRed << space << resetColor << " ";
            }
            else{
                std::cout << colorBlue << "|   " << resetColor;
            }
            if (k == size - 1)
            {
                std::cout << colorBlue << "|" << resetColor;
            }
        }

        std::cout << std::endl;
    }
}

void move(std::vector<std::vector<std::string>> &map, int size, char direction) {
        for (int j = 0; j < size; ++j) {
            if (map[size - 1][j] == "#") {
                map[size - 1][j] = " ";
                if (direction == 'a' && j > 0) {
                    map[size - 1][j - 1] = "#";
                } else if (direction == 'd' && j < size - 1) {
                    map[size - 1][j + 1] = "#";
                }
                else if(j == 0 || j == size - 1) 
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

// this function is used when we want to clear the termial screen
void clearScreen(){
    #ifdef _WIN32
        // for windows
        system("CLS");
    #else
        // for other oprating systems
        system("clear");
    #endif
}
