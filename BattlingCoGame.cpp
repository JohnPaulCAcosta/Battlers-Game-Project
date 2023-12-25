#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "interface.h"
#include "battlers.h"
using namespace std;

int main() {

    char decision = 'b'; //holds if player wants to create, battle, or quit
    string helperFileName; //helper file holds the battlers' info

    printGreetings();
    cin >> helperFileName;
    cout << endl;

    while (decision == 'b') {

        vector<Battler> allBattlers = loadHelperData(helperFileName);

        vector<Battler> currentBattlers = selectBattlers(allBattlers);

        battleDisplay(currentBattlers);

        cout << endl;
        cout << " Want to battle again?" << endl;
        cout << " (Enter 'b', or 'q' to quit): ";
        cin >> decision;
        cout << endl;

    }

    cout << "Thanks for checking this out, see you later!";

}