#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> 
#include <ctime> 
#include <climits>

using namespace std;

pair<int,int> GenerateRandomDot(int N) {
    int Y = rand() % N;
    int X = rand() % N; 
    pair<int,int> result = make_pair(Y,X); 
    return result;
}
pair<int,int> GenerateRandomSecondDot(int Y, int X) {
    int side = rand() % 4;
    if (side == 0) Y = Y + 1;
    if (side == 1) Y = Y - 1;
    if (side == 2) X = X + 1;
    if (side == 3) X = X - 1;
    pair<int,int> result = make_pair(Y,X); 
    return result;
}

void PrintFieldVector(vector<string> FieldName) {
    cout << endl;
    string Y = "ABCDEFGHIJ";
    string X = "  1 2 3 4 5 6 7";
    cout << X; 
    for (int i = 0; i < 7; i++){
        cout << endl << Y[i] << " ";
        for (int j = 0; j < 7; j++){
            cout << FieldName[i][j] << " ";
        }
    }
    cout << endl;
}
vector<string> GenerateField() {
    vector<string> OutputField;
    for (int i = 0; i < 7; i++) {
        OutputField.push_back("~~~~~~~");
    }
    int TwoDotShip = 3;
    int OneDotShip = 3;
    while (TwoDotShip > 0) {
        bool flag = true;
        pair <int,int> CoorFirstDot = GenerateRandomDot(OutputField.size());
        for (int dx = -1; dx <= 1; dx++) {
            if (flag == false) break;
            for (int dy = -1; dy <= 1; dy++) {
                int ny = CoorFirstDot.first + dy;
                int nx = CoorFirstDot.second + dx;
                if (OutputField[ny][nx] == '#') {
                    flag = false;
                    break;
                }
            }
        }
        if (flag == true) {
            pair <int,int> CoorSecondDot = GenerateRandomSecondDot(CoorFirstDot.first, CoorFirstDot.second);
            for (int dx = -1; dx <= 1; dx++) {
                if (flag == false) break;
                for (int dy = -1; dy <= 1; dy++) {
                    int ny = CoorSecondDot.first + dy;
                    int nx = CoorSecondDot.second + dx;
                    if (ny == CoorFirstDot.first and nx == CoorFirstDot.second)
                        continue;
                    if ((ny > 6) or (ny < 0) or (nx > 6) or (nx < 0)) {
                        flag = false;
                        break;
                    }
                    if (OutputField[ny][nx] == '#') {
                        flag = false;
                        break;
                    }
                }
            }
            if (flag == true) {
                OutputField[CoorFirstDot.first][CoorFirstDot.second] = '#';
                OutputField[CoorSecondDot.first][CoorSecondDot.second] = '#';
                TwoDotShip--;
            }
        }    
    }
    while (OneDotShip > 0) {
        bool flag = true;
        pair <int,int> CoorOneDot = GenerateRandomDot(OutputField.size());
        for (int dx = -1; dx <= 1; dx++) {
            if (flag == false) break;
            for (int dy = -1; dy <= 1; dy++) {
                int ny = CoorOneDot.first + dy;
                int nx = CoorOneDot.second + dx;
                if (OutputField[ny][nx] == '#') {
                    flag = false;
                    break;
                }
            }
        }
        if (flag == true) {
            OutputField[CoorOneDot.first][CoorOneDot.second] = '#';
            OneDotShip--;
        }    
    }
    return OutputField;
}