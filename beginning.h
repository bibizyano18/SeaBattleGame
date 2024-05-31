#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <vector>
#include "catchbutton.h"
#include "generatefield.h"


using namespace std;

char PrintWordByCoordinate(int n) {
    switch (n) {
        case 6:
            return 'G';
            break;
        case 5:
            return 'F';
            break;
        case 4:
            return 'E';
            break;
        case 3:
            return 'D';
            break;
        case 2:
            return 'C';
            break;
        case 1:
            return 'B';
            break;
        case 0:
            return 'A';
            break;
    }
    return ' ';
}

void RemainFleet(int One, int Two) {
    switch (One) {
        case 4:
            cout << "1. One dotted: # # # #" << endl;
            break;
        case 3:
            cout << "1. One dotted: # # #" << endl;
            break;
        case 2:
            cout << "1. One dotted: # #" << endl;
            break;
        case 1:
            cout << "1. One dotted: #" << endl;
            break;
    }
    switch (Two) {
        case 3:
            cout << "2. Two dotted: ## ## ##" << endl;
            break;
        case 2:
            cout << "2. Two dotted: ## ##" << endl;
            break;
        case 1:
            cout << "2. Two dotted: ##" << endl;
            break;
    }

}
void PrintField(string FieldName[]) {
    cout << "Your field: " << endl;
    string Y = "ABCDEFGHIJ";
    string X = "  1 2 3 4 5 6 7";
    cout << X; 
    for (int i = 0; i < 7; i++){
        cout << endl << Y[i] << " ";
        for (int j = 0; j < 7; j++){
            cout << FieldName[i][j] << " ";
        }
    }
}
void MakeShip(string FieldName[], int DotShip, int**& Coordinates) {
    int** Coor = new int* [DotShip];
        for (int i = 0; i < DotShip; i++)
            Coor[i] = new int[2];
    if (DotShip == 1) {
        FieldName[0][0] = '#';
        // (0,0)
        Coor[0][1] = 0; // x 
        Coor[0][0] = 0; // y
        
    }
    if (DotShip == 2) {
        FieldName[0][0] = '#';
        FieldName[1][0] = '#';
        // (0,0)
        Coor[0][1] = 0; // x1
        Coor[0][0] = 0; // y1
        // (0,1)
        Coor[1][1] = 0; // x2
        Coor[1][0] = 1; // y2
    }
    Coordinates = Coor;
}
void ChangeFieldWithActionOneDotted(string FieldName[], int Action, int**& Coordinates) {   
    int** Coor = new int*[1];
    for (int i = 0; i < 1; i++)
            Coor[i] = new int[2];
    int X = Coordinates[0][1];
    int Y = Coordinates[0][0];
    int flag = 0;
    if (Action == 5) {
        Coor[0][0] = Y;
        Coor[0][1] = X;
        cout << "Don't test me. YOU CHOSE ONE-DOTTED SHIP YOU *******" << endl;
    }
    if (Action == 3) { // right
        if (FieldName[Y][X+2] != '#') { // если на две клетки вправо нет корабля
            if (X < 6) { // не пересекаем границу
                if (FieldName[Y-1][X+2] != '#') { // заход на диагональную клетку корабля справа вверху
                    if (FieldName[Y+1][X+2] != '#') { // заход на диагональную клетку корабля справа снизу
                        FieldName[Y][X] = '~';
                        FieldName[Y][X+1] = '#';
                        Coor[0][0] = Y;
                        Coor[0][1] = X+1;
                        flag = 1;
                    }
                }
            }
        }
        if (flag == 0) {
            FieldName[Y][X] = '#';
            Coor[0][0] = Y;
            Coor[0][1] = X;
            cout << "There is an another ship or you're trying to cross the border!!" << endl;
        }
    }
    if (Action == 1) { // down
        if (FieldName[Y+2][X] != '#') {
            if (Y < 6) {
                if (FieldName[Y+2][X+1] != '#') {
                    if (FieldName[Y+2][X-1] != '#') {
                        FieldName[Y][X] = '~';
                        FieldName[Y+1][X] = '#';
                        Coor[0][0] = Y+1;
                        Coor[0][1] = X;
                        flag = 1;
                    }
                }
            }
        }
        if (flag == 0) {
            FieldName[Y][X] = '#';
            Coor[0][0] = Y;
            Coor[0][1] = X;
            cout << "There is an another ship or you're trying to cross the border!!" << endl;
        }
    }
    if (Action == 0) { // up
        if (FieldName[Y-2][X] != '#') {
            if (Y > 0) {
                if (FieldName[Y-2][X+1] != '#') {
                    if (FieldName[Y-2][X-1] != '#') {
                        FieldName[Y][X] = '~';
                        FieldName[Y-1][X] = '#';
                        Coor[0][0] = Y-1;
                        Coor[0][1] = X;
                        flag = 1;
                    }
                }
            }
        }
        if (flag == 0) {
            FieldName[Y][X] = '#';
            Coor[0][0] = Y;
            Coor[0][1] = X;
            cout << "There is an another ship or you're trying to cross the border!!" << endl;
        }
    }
    if (Action == 2) { // left
        if (FieldName[Y][X-2] != '#') {
            if (X > 0) {
                if (FieldName[Y+1][X-2] != '#') {
                    if (FieldName[Y-1][X-2] != '#'){ 
                        FieldName[Y][X] = '~';
                        FieldName[Y][X-1] = '#';
                        Coor[0][0] = Y;
                        Coor[0][1] = X-1;
                        flag = 1;
                    }
                }
            } 
        }
        if (flag == 0) {
            FieldName[Y][X] = '#';
            Coor[0][0] = Y;
            Coor[0][1] = X;
            cout << "There is an another ship or you're trying to cross the border!!" << endl;
        }
    }
    Coordinates = Coor;

}
void ChangeFieldWithActionTwoDotted(string FieldName[], int Action, int**& Coordinates, int& position) {   
    int** Coor = new int*[2];
    for (int i = 0; i < 2; i++)
            Coor[i] = new int[2];
    int X1 = Coordinates[0][1]; // х координата начала корабля
    int Y1 = Coordinates[0][0]; // у координата начала корабля
    int X2 = Coordinates[1][1]; // х координата конца корабля
    int Y2 = Coordinates[1][0]; // у координата конца корабля
    int flag = 0;
    // положение корабля 1 = vertical, 0 = horizontal
    if (Action == 5) {
        if (position == 1) { // vertical
            if (FieldName[Y2+1][X2+2] != '#'){
                if (FieldName[Y2][X2+2] != '#') {
                    if (FieldName[Y1-1][X2+2] != '#') {
                        if (X1 < 6 and X2 < 6) {
                            FieldName[Y2][X2] = '~';
                            FieldName[Y2-1][X2+1] = '#';
                            Y2 = Y2 - 1;
                            X2 = X2 + 1;
                            Coor[0][1] = X1;
                            Coor[0][0] = Y1;
                            Coor[1][1] = X2;
                            Coor[1][0] = Y2;
                            position = 0;
                            flag = 1;
                        }
                    }
                }
            }
            if (flag == 0) {
                FieldName[Y1][X1] = '#';
                FieldName[Y2][X2] = '#';
                Coor[0][1] = X1;
                Coor[0][0] = Y1;
                Coor[1][1] = X2;
                Coor[1][0] = Y2;
                cout << "There is an another ship or you're trying to cross the border!!" << endl;
            }

        }  
        // СДЕЛАТЬ ПРОВЕРКУ НА РАЗВОРОТ ИЗ ПОЛОЖЕНИЯ ГОРИЗОНТАЛЬНОГО
        else { // horizontal
            FieldName[Y2][X2] = '~';
            FieldName[Y2+1][X2-1] = '#';
            Y2 = Y2 + 1;
            X2 = X2 - 1;
            Coor[0][1] = X1;
            Coor[0][0] = Y1;
            Coor[1][1] = X2;
            Coor[1][0] = Y2;
            position = 1;
        }
    }
    if (position == 1) {
        if (Action == 3) { // right
            if (FieldName[Y1][X1+2] != '#') { // если на две клетки вправо нет корабля
                if (FieldName[Y2][X2+2] != '#') { // если на две клетки вправо нет корабля
                    if (X1 < 6) { // не пересекаем границу
                        if (X2 < 6) { // не пересекаем границу
                            if (FieldName[Y2+1][X2+2] != '#') { // заход на диагональную клетку корабля справа вверху
                                if (FieldName[Y1-1][X1+2] != '#') { // заход на диагональную клетку корабля справа снизу
                                    FieldName[Y1][X1] = '~';
                                    FieldName[Y2][X2] = '~';
                                    FieldName[Y1][X1+1] = '#';
                                    FieldName[Y2][X2+1] = '#';
                                    Coor[0][1] = X1+1;
                                    Coor[0][0] = Y1;
                                    Coor[1][1] = X2+1;
                                    Coor[1][0] = Y2;                                    
                                    flag = 1;
                                }
                            }
                        }
                    }
                }
            }
            if (flag == 0) {
                FieldName[Y1][X1] = '#';
                FieldName[Y2][X2] = '#';
                Coor[0][1] = X1;
                Coor[0][0] = Y1;
                Coor[1][1] = X2;
                Coor[1][0] = Y2;
                cout << "There is an another ship or you're trying to cross the border!!" << endl;
            }
        }
        if (Action == 1) { // down
            if (FieldName[Y2+2][X2] != '#') {
                if (Y2 < 6) {
                    if (FieldName[Y2+2][X2+1] != '#') {
                        if (FieldName[Y2+2][X2-1] != '#') {
                            FieldName[Y1][X1] = '~';
                            FieldName[Y2+1][X2] = '#';
                            Coor[0][1] = X2;
                            Coor[0][0] = Y2;
                            Coor[1][1] = X2;
                            Coor[1][0] = Y2+1;
                            flag = 1;
                        }
                    }
                }
            }
            if (flag == 0) {
                FieldName[Y1][X1] = '#';
                FieldName[Y2][X2] = '#';
                Coor[0][1] = X1;
                Coor[0][0] = Y1;
                Coor[1][1] = X2;
                Coor[1][0] = Y2;
                cout << "There is an another ship or you're trying to cross the border!!" << endl;
            }
        }
        if (Action == 0) { // up
            if (FieldName[Y1-2][X1] != '#') {
                if (Y1 > 0) {
                    if (FieldName[Y1-2][X1+1] != '#') {
                        if (FieldName[Y1-2][X1-1] != '#') {
                            FieldName[Y2][X2] = '~';
                            FieldName[Y1-1][X1] = '#';
                            Coor[0][1] = X1;
                            Coor[0][0] = Y1-1;
                            Coor[1][1] = X2;
                            Coor[1][0] = Y2-1;
                            flag = 1;
                        }
                    }
                }
            }
            if (flag == 0) {
                FieldName[Y1][X1] = '#';
                FieldName[Y2][X2] = '#';
                Coor[0][1] = X1;
                Coor[0][0] = Y1;
                Coor[1][1] = X2;
                Coor[1][0] = Y2;
                cout << "There is an another ship or you're trying to cross the border!!" << endl;
            }
        }
        if (Action == 2) { // left
            if (FieldName[Y1][X1-2] != '#') { // если на две клетки влево нет корабля
                if (FieldName[Y2][X2-2] != '#') { // если на две клетки влево нет корабля
                    if (X1 > 0) { // не пересекаем границу
                        if (X2 > 0) { // не пересекаем границу
                            if (FieldName[Y2+1][X2-2] != '#') { // заход на диагональную клетку корабля справа вверху
                                if (FieldName[Y1-1][X1-2] != '#') { // заход на диагональную клетку корабля справа снизу
                                    FieldName[Y1][X1] = '~';
                                    FieldName[Y2][X2] = '~';
                                    FieldName[Y1][X1-1] = '#';
                                    FieldName[Y2][X2-1] = '#';
                                    Coor[0][1] = X1-1;
                                    Coor[0][0] = Y1;
                                    Coor[1][1] = X2-1;
                                    Coor[1][0] = Y2;                                    
                                    flag = 1;
                                }
                            }
                        }
                    }
                }
            }
            if (flag == 0) {
                FieldName[Y1][X1] = '#';
                FieldName[Y2][X2] = '#';
                Coor[0][1] = X1;
                Coor[0][0] = Y1;
                Coor[1][1] = X2;
                Coor[1][0] = Y2;
                cout << "There is an another ship or you're trying to cross the border!!" << endl;
            }
        }
    }
    else {
        if (Action == 3) { // right
            if (FieldName[Y2][X2+2] != '#') { // если на две клетки вправо нет корабля
                if (X2 < 6) { // не пересекаем границу
                    if (FieldName[Y2+1][X2+2] != '#') { // заход на диагональную клетку корабля справа вверху
                        if (FieldName[Y2-1][X2+2] != '#') { // заход на диагональную клетку корабля справа снизу
                            FieldName[Y1][X1] = '~';
                            FieldName[Y2][X2] = '~';
                            FieldName[Y1][X1+1] = '#';
                            FieldName[Y2][X2+1] = '#';
                            Coor[0][1] = X1+1;
                            Coor[0][0] = Y1;
                            Coor[1][1] = X2+1;
                            Coor[1][0] = Y2;                                    
                            flag = 1;
                        }
                    }
                }
            }
            
            if (flag == 0) {
                FieldName[Y1][X1] = '#';
                FieldName[Y2][X2] = '#';
                Coor[0][1] = X1;
                Coor[0][0] = Y1;
                Coor[1][1] = X2;
                Coor[1][0] = Y2;
                cout << "There is an another ship or you're trying to cross the border!!" << endl;
            }
        }
        if (Action == 1) { // down
            if (FieldName[Y2+2][X2] != '#') {
                if ((FieldName[Y1+2][X1] != '#')) {
                    if (Y2 < 6) {
                        if (Y1 < 6) {
                            if (FieldName[Y2+2][X2+1] != '#') {
                                if (FieldName[Y1+2][X1-1] != '#') {
                                    FieldName[Y2+1][X2] = '#';
                                    FieldName[Y1+1][X1] = '#';
                                    FieldName[Y1][X1] = '~';
                                    FieldName[Y2][X2] = '~';                                   
                                    Coor[0][1] = X1;
                                    Coor[0][0] = Y1+1;
                                    Coor[1][1] = X2;
                                    Coor[1][0] = Y2+1;
                                    flag = 1;
                                }
                            }
                        }
                    }
                }
            }
            if (flag == 0) {
                FieldName[Y1][X1] = '#';
                FieldName[Y2][X2] = '#';
                Coor[0][1] = X1;
                Coor[0][0] = Y1;
                Coor[1][1] = X2;
                Coor[1][0] = Y2;
                cout << "There is an another ship or you're trying to cross the border!!" << endl;
            }
        }
        if (Action == 2) { // left
            if (FieldName[Y1][X1-2] != '#') { // если на две клетки влево нет корабля
                if (X1 > 0) { // не пересекаем границу
                    if (FieldName[Y1+1][X1-2] != '#') { // заход на диагональную клетку корабля свлева вверху
                        if (FieldName[Y1-1][X1-2] != '#') { // заход на диагональную клетку корабля свлева снизу
                            FieldName[Y1][X1] = '~';
                            FieldName[Y2][X2] = '~';
                            FieldName[Y1][X1-1] = '#';
                            FieldName[Y2][X2-1] = '#';
                            Coor[0][1] = X1-1;
                            Coor[0][0] = Y1;
                            Coor[1][1] = X2-1;
                            Coor[1][0] = Y2;                                    
                            flag = 1;
                        }
                    }
                }
            }
            if (flag == 0) {
                FieldName[Y1][X1] = '#';
                FieldName[Y2][X2] = '#';
                Coor[0][1] = X1;
                Coor[0][0] = Y1;
                Coor[1][1] = X2;
                Coor[1][0] = Y2;
                cout << "There is an another ship or you're trying to cross the border!!" << endl;
            }
        }
        if (Action == 0) { // up
            if (FieldName[Y2-2][X2] != '#') {
                if ((FieldName[Y1-2][X1] != '#')) {
                    if (Y1 > 0) {
                        if (Y2 > 0) {
                            if (FieldName[Y2-2][X2+1] != '#') {
                                if (FieldName[Y1-2][X1-1] != '#') {
                                    FieldName[Y1][X1] = '~';
                                    FieldName[Y2][X2] = '~';
                                    FieldName[Y2-1][X2] = '#';
                                    FieldName[Y1-1][X1] = '#';
                                    Coor[0][1] = X1;
                                    Coor[0][0] = Y1-1;
                                    Coor[1][1] = X2;
                                    Coor[1][0] = Y2-1;
                                    flag = 1;
                                }
                            }
                        }
                    }
                }
            }
            if (flag == 0) {
                FieldName[Y1][X1] = '#';
                FieldName[Y2][X2] = '#';
                Coor[0][1] = X1;
                Coor[0][0] = Y1;
                Coor[1][1] = X2;
                Coor[1][0] = Y2;
                cout << "There is an another ship or you're trying to cross the border!!" << endl;
            }
        }
    }
    Coordinates = Coor;
    
}
void Beginning(vector<string>& OutputField) {
    cout << "Welcome to the SEA BATTLE!" << endl;
    cout << "Choose an option: " << endl;
    cout << "1. New game" << endl;
    cout << "2. Quit" << endl;

    int number = ButtonPressedNum();


    if (number == 1) {

        cout << "Do you want to generate a field or do you want to make your own one?: " << endl;
        cout << "1. Generate a field" << endl;
        cout << "2. Make my own" << endl;
        cout << "3. Quit" << endl;

        int newnum = ButtonPressedNum();

        if (newnum == 1) 
            OutputField = GenerateField();
        
        if (newnum == 2) {
            string PlayerField[9] = 
            {
                "~~~~~~~", "~~~~~~~", "~~~~~~~",
                "~~~~~~~", "~~~~~~~", "~~~~~~~",
                "~~~~~~~", "~~~~~~~",
            };
            int FlagReadyToBattle = 0;
            PrintField(PlayerField);
            int TwoDotShip = 3;
            int OneDotShip = 3;

            while (true) {
                if (TwoDotShip == 0 and OneDotShip == 0) {
                    cout << "\033[2J\033[1;1H"; // очистка консоли
                    cout << endl <<  "Your fleet is ready to fight!" << endl;
                    FlagReadyToBattle = 1;
                    break;
                }
                cout << endl << "Choose which ship do you want to put on the field: " << endl;
                RemainFleet(OneDotShip, TwoDotShip);
                cout << "Press '0' to quit" << endl;
                int ChooseWhichShip = ButtonPressedNum();
                if (ChooseWhichShip == 0) {
                    cout << "See you later!" << endl;
                    break;
                }

                if (ChooseWhichShip == 1 and OneDotShip > 0) {
                    int** Coordinates = new int* [ChooseWhichShip];
                    for (int i = 0; i < ChooseWhichShip; i++)
                        Coordinates[i] = new int[2];
                    MakeShip(PlayerField, ChooseWhichShip, Coordinates);
                    cout << "\033[2J\033[1;1H"; // очистка консоли
                    PrintField(PlayerField);
                    while (true) {
                        cout << endl << "Use arrows to move the ship, 'R' to rotate, 'Enter' to confirm" << endl;
                        int Action = ButtonPressed();
                        cout << "\033[2J\033[1;1H"; // очистка консоли
                        ChangeFieldWithActionOneDotted(PlayerField, Action, Coordinates);
                        cout << PrintWordByCoordinate(Coordinates[0][0]) << " " << Coordinates[0][1] + 1 << endl;
                        PrintField(PlayerField);
                        if (Action == 4) {
                            OneDotShip = OneDotShip - 1;
                            break;
                        }
                    }
                    delete[] Coordinates; 
                }

                if (ChooseWhichShip == 1 and OneDotShip == 0 and TwoDotShip > 0) {   
                    cout << endl << "You ain't got any one-dotted ships left!" << endl; 
                }

                if (ChooseWhichShip == 2 and TwoDotShip > 0) {
                    int** Coordinates = new int* [ChooseWhichShip];
                    for (int i = 0; i < ChooseWhichShip; i++)
                        Coordinates[i] = new int[2];
                    MakeShip(PlayerField, ChooseWhichShip, Coordinates);
                    int position = 1; // vertical
                    cout << "\033[2J\033[1;1H"; // очистка консоли
                    PrintField(PlayerField);
                    while (true) {
                        cout << endl << "Use arrows to move the ship, 'R' to rotate, 'Enter' to confirm" << endl;
                        int Action = ButtonPressed(); 
                        cout << "\033[2J\033[1;1H"; // очистка консоли 
                        ChangeFieldWithActionTwoDotted(PlayerField, Action, Coordinates, position);
                        cout << PrintWordByCoordinate(Coordinates[0][0]) << " " << Coordinates[0][1] + 1 << endl;
                        cout << PrintWordByCoordinate(Coordinates[1][0]) << " " << Coordinates[1][1] + 1 << endl;
                        PrintField(PlayerField);
                        if (Action == 4) {
                            TwoDotShip = TwoDotShip - 1;
                            break;
                        }
                    }
                    delete[] Coordinates;  
                }

                if (ChooseWhichShip == 2 and TwoDotShip == 0 and OneDotShip > 0) {   
                    cout << endl << "You ain't got any two-dotted ships left!" << endl; 
                }        
            }
            if (FlagReadyToBattle == 1) {
                for (auto n : PlayerField) {
                    OutputField.push_back(n);
                }
            }
        }
        if (newnum == 3) 
            cout << "See you later!" << endl;
    }
    
    if (number == 2){
        cout << "See you later!" << endl;
    }
}

