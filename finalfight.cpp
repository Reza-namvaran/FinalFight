#include <iostream>
using namespace std;

struct postion
{
    int x_Posiotion;
    int y_Posiotion;
};

void runGame();
void clearScreen();
void generatMap(int size);

int main(){
    runGame();
    return 0;
}

void runGame(){
    clearScreen();
    int size;
    cout << "Enter the size of the map: ";
    cin >> size;
    generatMap(size);
}

void generatMap(int size){
    clearScreen();
    for(int i = 0; i <= size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            cout << " ---";
        }

        cout << endl;

        if(i == size)
            continue;

        for(int k = 0; k < size; k++)
        {
            cout << "|   ";

            if (k == size - 1)
            {
                cout << "|";
            }
        }

        cout << endl;
    }
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