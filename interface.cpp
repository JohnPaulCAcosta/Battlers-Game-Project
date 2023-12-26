#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include "interface.h"
#include "battlers.h"
using namespace std;

//Non-Generic Functions

vector<Battler> loadHelperData(string fileName) {
    //see README file regarding helper file specifications
    
    vector<Battler> output;
    ifstream inFS;
    inFS.open(fileName);
    while (!inFS.is_open()) {
        cout << "Oops! No helper file was found, please enter the correct name: ";
        cin >> fileName;
        inFS.open(fileName);
    }

    while (!inFS.eof()) {

        string new_name;
        char new_image[15][10];
        string new_dummy_string; /*holds the line of characters that will get imported into image array*/
        string type_name;
        string strength;
        string weakness;
        double health;
        int pA;
        int pD;
        int sA;
        int sD;
        string move_name;
        string move_type;
        char move_Dtype;
        double move_multiplier;

        for (int y = 0; y < 10; y++) {
            getline(inFS, new_dummy_string);
            for (int x = 0; x < 15; x++) {
                new_image[x][y] = new_dummy_string.at(x);
            }
        }

        inFS >> new_name >> type_name >> strength >> weakness >> health >> pA >> pD >> sA >> sD;

        Battler new_battler(new_name);
        new_battler.SetImage(new_image);
        new_battler.SetType(type_name, strength, weakness);
        new_battler.SetHealth(health);
        new_battler.SetStats(pA, pD, sA, sD);

        for (int i = 0; i < 3; i++) {
            inFS >> move_name >> move_type >> move_Dtype >> move_multiplier;
            new_battler.AddMove(move_name, move_type, move_Dtype, move_multiplier);
        }

        output.push_back(new_battler);

        if (getline(inFS, new_dummy_string)) {
            /*the getline function will get the character associated with
            the 'enter' key or what makes a new line in the helper file, so
            this deals with the possible 'enter' character. this ensures
            it does not mess with our getline executions with other battler
            information segments, if it is there*/
        }

    }

    return output;

}


//Other Generic functions

vector<Battler> selectBattlers(vector<Battler>& allBattlers) {

    int numOfUsers;
    string battler1name;
    string battler2name;
    vector<Battler> battlingBattlers;
    Battler battler1("null");
    Battler battler2("null");

    cout << " Do you wish to battle the computer or a friend locally? (Enter 1 or 2) : ";
    cin >> numOfUsers;
    cout << endl;

    cout << " Time to choose your battler, Player One!" << endl;
    cout << " (Enter one of ";

    for (unsigned int i = 0; i < allBattlers.size(); i++) {
        cout << allBattlers.at(i).GetName();
        if (i != allBattlers.size() - 1) {
            cout << ", ";
        }
    }

    cout << ") : ";

    cin >> battler1name;
    cout << endl;

    if (numOfUsers == 2) {
        cout << " Time to choose your battler, Player Two! : ";
        cin >> battler2name;
        cout << endl;
    }
    else {
        cout << " Choose your opponent! : ";
        cin >> battler2name;
        cout << endl;
    }

    for (unsigned int i = 0; i < allBattlers.size(); i++) {
        /*example of unaccounted error: what if two battlers have the same name
        but different movesets?*/

        if (battler1name == allBattlers.at(i).GetName()) {
            battler1 = allBattlers.at(i);
            battler1.SetPlayingStatus(true);
        }

        if (battler2name == allBattlers.at(i).GetName()) {
            battler2 = allBattlers.at(i);

            if (numOfUsers == 2) {
                battler2.SetPlayingStatus(true);
            }
        }

    }

    battlingBattlers.push_back(battler1);
    battlingBattlers.push_back(battler2);

    return battlingBattlers;

}

void battleDisplay(vector<Battler>& battlers) {

    int selected_move;

    cout << "------------------------------------" << endl;
    cout << "                " << battlers.at(0).GetName() << endl;
    cout << "                 vs." << endl;
    cout << "                " << battlers.at(1).GetName() << "!" << endl;
    cout << "------------------------------------" << endl;

    while (battlers.at(0).GetHealth() != 0 && battlers.at(1).GetHealth() != 0) {
        cout << endl;
        cout << " HP: " << battlers.at(0).GetHealth() << "           ";
        cout << " HP: " << battlers.at(1).GetHealth() << "           " << endl;

        for (unsigned int y = 0; y < 10; y++) {
            for (unsigned int x = 0; x < 35; x++) { /* two images will have a width a 30, 5 whitespaces provides spacing*/
                
                if (x >= 2 && x <= 16) {
                    cout << battlers.at(0).image[x - 2][y];
                }
                else if (x >= 19 && x <= 33) {
                    cout << battlers.at(1).image[x - 19][y];
                }
                else {
                    cout << " ";
                }

            }
            cout << endl;
        }

        cout << endl;
        cout << battlers.at(0).GetName() << "\'s Moves: " << battlers.at(0).GetMoves() << endl;
        cout << battlers.at(1).GetName() << "\'s Moves: " << battlers.at(1).GetMoves() << endl;
        cout << endl;

        cout << "Player 1, what is your move? (select number): ";
        cin >> selected_move;
        cout << endl;

        //helper function using selected move: 
        InitiateAttackFunctions(battlers.at(0), battlers.at(1), selected_move);

        if (battlers.at(1).GetHealth() == 0) {
            break;
        }
        
        if (battlers.at(1).GetPlayerStatus()) {
            
            cout << endl;
            cout << "Player 2, what is your move? (select number): ";
            cin >> selected_move;
            cout << endl;

            InitiateAttackFunctions(battlers.at(1), battlers.at(0), selected_move);   //  InitiateAttackFunctions(battlers.at(0), battlers.at(1), selected_move);

        }
        else {
            InitiateAttackFunctions(battlers.at(1), battlers.at(0)); //  Initiateblahblahblah
        }

    }

    /*at this point, one of the battlers have been defeated*/

    if (battlers.at(0).GetHealth() == 0) {
        cout << battlers.at(1).GetName() << " has won the battle!" << endl;
    }
    else if (battlers.at(1).GetHealth() == 0) {
        cout << battlers.at(0).GetName() << " has won the battle!" << endl;
    }

}

void printGreetings() {

    cout << " Howdy! This is a Pokemon-type Battle Simulator," << endl;
    cout << " created to have fun experimenting with classes," << endl;
    cout << " dynamic memory, pointers, input management, and" << endl;
    cout << " batch processing-like functions                " << endl;
    cout << " (Try battling with Shapesitto!)                     " << endl;
    cout << " Created w/ Visual Studio Code, with Resolution " << endl;
    cout << " of 3840 x 2400                                 " << endl << endl;

    cout << "      ~~~~~     Battling Co. Game     ~~~~~     " << endl << endl;

    cout << " Please enter the name of the helper file: ";

}

void InitiateAttackFunctions(Battler& attacker, Battler& opponent, int selected_move) {

        double damage_dealt = attacker.Attack(opponent, selected_move);
 
        if (damage_dealt == -99.9) {
            /*if this runs, the second battler has been defeated!*/
        }
        else if (damage_dealt < 0) {
            /*checking for special moves*/
            if (damage_dealt == -1.001) { //'Transform'
                attacker = opponent;
                attacker.SetPlayingStatus(true); //accounts for multiple players, false for any non-user players
            }
            else if (damage_dealt == -1.002) { //'Flaming Devastation'
            
                attacker.SetSpecialAttack(attacker.GetSpecialAttack() * .80); //debuff for attack
                
                attacker.Attack(opponent, selected_move, 1); 

            }
        }
    
}
