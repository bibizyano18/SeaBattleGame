#include <iostream>
#include "battle.h"


using namespace std;

int main() {
    srand((unsigned int) time(NULL));
    vector<string> PlayerField;
    Beginning(PlayerField);
    vector<string> AiField = GenerateField();
    bool flag = false;
    for (int i = 0; i < PlayerField.size(); i++) {
        for (int j = 0; j < PlayerField[i].size(); j++) {
            if (PlayerField[i][j] == '#') flag = true;
        }
    }
    if (flag) {
        Battle(PlayerField, AiField);
    }
    return 0;
}