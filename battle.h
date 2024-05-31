#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include "beginning.h"

using namespace std;
 

int isDotExist(vector<pair<int,int>> FieldName, int Y, int X) {
    for (int i = 0; i < FieldName.size(); i++) {
        if (FieldName[i].first == Y and FieldName[i].second == X) {
            return i;
            break;
        }
    }
    return -1;
    
}
bool MoreShip(vector<string> FieldName, pair<int,int> Coords) {
    int Y = Coords.first;
    int X = Coords.second;
    if (Y + 1 < FieldName.size() and FieldName[Y+1][X] == '#') return true;
    if (Y - 1 >= 0 and FieldName[Y-1][X] == '#') return true;
    if (X + 1 < FieldName[0].size() and FieldName[Y][X+1] == '#') return true;
    if (X - 1 >= 0 and FieldName[Y][X-1] == '#') return true;
    return false;
}

int MoreShipV(vector<string> FieldName, int Y, int X) {
    if (Y + 1 < FieldName.size() and FieldName[Y+1][X] == 'V') return 0;
    if (Y - 1 >= 0 and FieldName[Y-1][X] == 'V') return 1;
    if (X + 1 < FieldName[0].size() and FieldName[Y][X+1] == 'V') return 2;
    if (X - 1 >= 0 and FieldName[Y][X-1] == 'V') return 3;
    return -1;
}

void MoveWithAction(vector<string>& AttackField, pair<int,int>& Coords, int Action, char& prevChar) {
    pair<int,int> changedCoords;
    int Y = Coords.first;
    int X = Coords.second;
    char NewChar = prevChar;
    if (Action == 0) { // up
        if (Y - 1 > -1) {
            AttackField[Y][X] = prevChar;
            NewChar = AttackField[Y-1][X];
            AttackField[Y-1][X] = '!';
            changedCoords.first = Y - 1;
            changedCoords.second = X;
        }
        else {
            AttackField[Y][X] = '!';
            changedCoords.first = Y;
            changedCoords.second = X;
        }
    }
    if (Action == 1) { // down
        if (Y + 1 < 7) {
            AttackField[Y][X] = prevChar;
            NewChar = AttackField[Y+1][X];
            AttackField[Y+1][X] = '!';
            changedCoords.first = Y + 1;
            changedCoords.second = X;
        }
        else {
            AttackField[Y][X] = '!';
            changedCoords.first = Y;
            changedCoords.second = X;
        }
    }
    if (Action == 2) { // left
        if (X - 1 > -1) {
            AttackField[Y][X] = prevChar;
            NewChar = AttackField[Y][X-1];
            AttackField[Y][X-1] = '!';
            changedCoords.first = Y;
            changedCoords.second = X - 1;
        }
        else {
            AttackField[Y][X] = '!';
            changedCoords.first = Y;
            changedCoords.second = X;
        }
    }
    if (Action == 3) { // right
        if (X + 1 < 7) {
            AttackField[Y][X] = prevChar;
            NewChar = AttackField[Y][X+1];
            AttackField[Y][X+1] = '!';
            changedCoords.first = Y;
            changedCoords.second = X + 1;
        }
        else {
            AttackField[Y][X] = '!';
            changedCoords.first = Y;
            changedCoords.second = X;
        }
    }
    if (Action == 4) { 
        changedCoords.first = Y;
        changedCoords.second = X;
    }
    prevChar = NewChar;
    Coords = changedCoords;
}

int PickRandomIndex(vector<pair<int,int>> Arr) {
    int sizeArray = Arr.size() - 1;
    // rand() % ((b - a) + 1) + a; // a - левая граница, b - правая граница
    int result = rand() % ((sizeArray - 0) + 1) + 0;
    return result;
}

void Battle(vector<string> PlayerField, vector<string> AiField) {
    vector<pair<int,int>> fieldCoord;
    vector<pair<int,int>> firedDotsCoord;
    vector<string> AttackField;
    for (int i = 0; i < 7; i++)
        AttackField.push_back("~~~~~~~");
    for (int i = 0; i < PlayerField.size(); i++) {
        for (int j = 0; j < PlayerField[i].size(); j++) {
            fieldCoord.push_back(make_pair(i,j));
        }
    }

    int PlayerOneDotted = 3;
    int PlayerTwoDotted = 3;
    int AiOneDotted = 3;
    int AiTwoDotted = 3;

    int Turn = 0; // 0 - Player's turn, 1 - Ai's turn
    cout << endl << "Your fields: ";
    PrintFieldVector(AttackField);
    PrintFieldVector(PlayerField);
    cout << endl << "Press 1 to start the battle! (0 to quit)";
    int button = ButtonPressedNum();
        if (button == 1) {
            cout << "\033[2J\033[1;1H"; // очистка консоли
            bool flagV = false;
            int hittedY = 0;
            int hittedX = 0;
            while (true) {
                if (PlayerOneDotted == 0 and PlayerTwoDotted == 0) {
                    cout << "\033[2J\033[1;1H"; // очистка консоли
                    PrintFieldVector(AttackField);
                    PrintFieldVector(PlayerField);
                    cout << endl << "You lose!";
                    cout << endl << "GAME OVER!!";
                    break;
                }
                if (AiOneDotted == 0 and AiTwoDotted == 0) {
                    cout << "\033[2J\033[1;1H"; // очистка консоли
                    PrintFieldVector(AttackField);
                    PrintFieldVector(PlayerField);
                    cout << endl << "You won!";
                    cout << endl << "GAME OVER!!";
                    break;
                }
                if (Turn == 0) {
                    pair <int,int> Coords = make_pair(0,0);
                    char ch = AttackField[0][0];
                    AttackField[0][0] = '!';
                    cout << endl << PrintWordByCoordinate(Coords.first) << " " << Coords.second + 1;
                    PrintFieldVector(AttackField);
                    PrintFieldVector(PlayerField);
                    while(true) {
                        int Action = ButtonPressed();
                        MoveWithAction(AttackField,Coords,Action,ch);
                        cout << "\033[2J\033[1;1H"; // очистка консоли
                        cout << endl << PrintWordByCoordinate(Coords.first) << " " << Coords.second + 1;
                        PrintFieldVector(AttackField);
                        PrintFieldVector(PlayerField);
                        if (Action == 4) { 
                            break;
                        }
                    }
                    int dY = Coords.first;
                    int dX = Coords.second;
                    cout << "\033[2J\033[1;1H"; // очистка консоли
                    if (AiField[dY][dX] == '#') {
                        if (MoreShip(AiField, Coords)) {
                            AttackField[dY][dX] = 'V';
                            cout << endl << "You hitted him!" << endl;
                        }
                        else {
                            AttackField[dY][dX] = 'X';
                            AiOneDotted -= 1;
                            cout << endl << "We murdered one of them!" << endl;
                            
                        } 
                    }
                    else {
                        AttackField[dY][dX] = '*';
                        cout << endl << "You missed, captain! Now it's his turn!";
                        cout << endl << " ";
                        Turn = 1;
                    }
                    bool flag = true;
                    for (int i = 0; i < AttackField.size(); i++) {
                        if (!flag) break;
                        for (int j = 0; j < AttackField[i].size(); j++) {
                            if ((MoreShipV(AttackField,i,j) == 0) and (AttackField[i][j] == 'V')) {
                                AttackField[i+1][j] = 'X';
                                AttackField[i][j] = 'X';
                                AiTwoDotted -= 1;
                                cout << endl << "We murdered one of them!" << endl;
                                flag = false;
                                break;
                            }
                            if ((MoreShipV(AttackField,i,j) == 1) and (AttackField[i][j] == 'V')) {
                                AttackField[i-1][j] = 'X';
                                AttackField[i][j] = 'X';
                                AiTwoDotted -= 1;
                                cout << endl << "We murdered one of them!" << endl;
                                flag = false;
                                break;
                            }
                            if ((MoreShipV(AttackField,i,j) == 2) and (AttackField[i][j] == 'V')) {
                                AttackField[i][j+1] = 'X';
                                AttackField[i][j] = 'X';
                                AiTwoDotted -= 1;
                                cout << endl << "We murdered one of them!" << endl;
                                flag = false;
                                break;
                            }
                            if ((MoreShipV(AttackField,i,j) == 3) and (AttackField[i][j] == 'V')) {
                                AttackField[i][j-1] = 'X';
                                AttackField[i][j] = 'X';
                                AiTwoDotted -= 1;
                                cout << endl << "We murdered one of them!" << endl;
                                flag = false;
                                break;
                            }
                        }
                    }
                }
                if (Turn == 1) {
                    while (true) {          
                        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                        if (flagV == false) {
                            int index = PickRandomIndex(fieldCoord);
                            firedDotsCoord.push_back(fieldCoord[index]);
                            fieldCoord.erase(fieldCoord.begin() + index);
                            int nY = firedDotsCoord[firedDotsCoord.size()-1].first;
                            int nX = firedDotsCoord[firedDotsCoord.size()-1].second;
                            pair <int,int> AiCoords = make_pair(nY,nX);
                            
                                        
                            if ((PlayerField[nY][nX] == '#') and (MoreShip(PlayerField,AiCoords) == false)) {
                                PlayerField[nY][nX] = 'X';
                                PlayerOneDotted -= 1;
                                cout << endl << "He murdered our ship!";
                                cout << endl << "He will make another shot!" << endl;
                                PrintFieldVector(PlayerField);
                                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                            }
                            if ((PlayerField[nY][nX] == '~') and (flagV == false)) {
                                PlayerField[nY][nX] = '*';
                                Turn = 0;
                                cout << endl << "He missed!";
                                cout << endl << "Now it's our turn!" << endl;
                                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                                break;

                            }
                            if ((PlayerField[nY][nX] == '#') and (MoreShip(PlayerField,AiCoords) == true)) {
                                PlayerField[nY][nX] = 'V';
                                cout << endl << "He hitted our ship!";
                                cout << endl << "He will make another shot!" << endl;
                                PrintFieldVector(PlayerField);
                                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                                hittedY = nY;
                                hittedX = nX;
                                flagV = true;
                            }
                        }
                        if (flagV == true) {

                            if (isDotExist(fieldCoord,hittedY+1,hittedX) != -1 and Turn == 1) {                            
                                if (PlayerField[hittedY+1][hittedX] == '#') {
                                    int ind = isDotExist(fieldCoord,hittedY+1,hittedX);
                                    PlayerField[hittedY][hittedX] = 'X';
                                    PlayerField[hittedY+1][hittedX] = 'X';
                                    cout << endl << "He murdered our ship!";
                                    cout << endl << "He will make another shot!" << endl;
                                    PrintFieldVector(PlayerField);
                                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                                    PlayerTwoDotted -= 1;
                                    firedDotsCoord.push_back(fieldCoord[ind]);
                                    fieldCoord.erase(fieldCoord.begin() + ind);
                                    flagV = false;
                                }
                                if (PlayerField[hittedY+1][hittedX] == '~') {
                                    int ind = isDotExist(fieldCoord,hittedY+1,hittedX);
                                    PlayerField[hittedY+1][hittedX] = '*';
                                    cout << endl << "He missed!";
                                    cout << endl << "Now it's our turn!" << endl;
                                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                                    firedDotsCoord.push_back(fieldCoord[ind]);
                                    fieldCoord.erase(fieldCoord.begin() + ind);
                                    Turn = 0;
                                    break;
                                }
                            }
                            if (isDotExist(fieldCoord,hittedY-1,hittedX) != -1 and Turn == 1) {
                                if (PlayerField[hittedY-1][hittedX] == '#') {
                                    int ind = isDotExist(fieldCoord,hittedY-1,hittedX);
                                    PlayerField[hittedY][hittedX] = 'X';
                                    PlayerField[hittedY-1][hittedX] = 'X';
                                    cout << endl << "He murdered our ship!";
                                    cout << endl << "He will make another shot!" << endl;
                                    PrintFieldVector(PlayerField);
                                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                                    PlayerTwoDotted -= 1;
                                    firedDotsCoord.push_back(fieldCoord[ind]);
                                    fieldCoord.erase(fieldCoord.begin() + ind);
                                    flagV = false;
                                }
                                if (PlayerField[hittedY-1][hittedX] == '~') {
                                    int ind = isDotExist(fieldCoord,hittedY-1,hittedX);
                                    PlayerField[hittedY-1][hittedX] = '*';
                                    cout << endl << "He missed!";
                                    cout << endl << "Now it's our turn!" << endl;
                                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                                    firedDotsCoord.push_back(fieldCoord[ind]);
                                    fieldCoord.erase(fieldCoord.begin() + ind);
                                    Turn = 0;
                                    break;
                                }
                            }
                            if (isDotExist(fieldCoord,hittedY,hittedX+1) != -1 and Turn == 1) {
                                if (PlayerField[hittedY][hittedX+1] == '#') {
                                    int ind = isDotExist(fieldCoord,hittedY,hittedX+1);
                                    PlayerField[hittedY][hittedX] = 'X';
                                    PlayerField[hittedY][hittedX+1] = 'X';
                                    cout << endl << "He murdered our ship!";
                                    cout << endl << "He will make another shot!" << endl;
                                    PrintFieldVector(PlayerField);
                                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                                    PlayerTwoDotted -= 1;
                                    firedDotsCoord.push_back(fieldCoord[ind]);
                                    fieldCoord.erase(fieldCoord.begin() + ind);
                                    flagV = false;
                                }
                                if (PlayerField[hittedY][hittedX+1] == '~') {
                                    int ind = isDotExist(fieldCoord,hittedY,hittedX+1);
                                    PlayerField[hittedY][hittedX+1] = '*';
                                    cout << endl << "He missed!";
                                    cout << endl << "Now it's our turn!" << endl;
                                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                                    firedDotsCoord.push_back(fieldCoord[ind]);
                                    fieldCoord.erase(fieldCoord.begin() + ind);
                                    Turn = 0;
                                    break;
                                }
                            }
                            if (isDotExist(fieldCoord,hittedY,hittedX-1) != -1 and Turn == 1) {
                                if (PlayerField[hittedY][hittedX-1] == '#') {
                                    int ind = isDotExist(fieldCoord,hittedY,hittedX-1);
                                    PlayerField[hittedY][hittedX] = 'X';
                                    PlayerField[hittedY][hittedX-1] = 'X';
                                    cout << endl << "He murdered our ship!";
                                    cout << endl << "He will make another shot!" << endl;
                                    PrintFieldVector(PlayerField);
                                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                                    PlayerTwoDotted -= 1;
                                    firedDotsCoord.push_back(fieldCoord[ind]);
                                    fieldCoord.erase(fieldCoord.begin() + ind);
                                    flagV = false;
                                }
                                if (PlayerField[hittedY][hittedX-1] == '~') {
                                    int ind = isDotExist(fieldCoord,hittedY,hittedX-1);
                                    PlayerField[hittedY][hittedX-1] = '*';
                                    cout << endl << "He missed!";
                                    cout << endl << "Now it's our turn!" << endl;
                                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                                    firedDotsCoord.push_back(fieldCoord[ind]);
                                    fieldCoord.erase(fieldCoord.begin() + ind);
                                    Turn = 0;
                                    break;
                                }
                            }
                        }   
                    }
                }
            }
        }
        else cout << endl << "See you later!";  
}
