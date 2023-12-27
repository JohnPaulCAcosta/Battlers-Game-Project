#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "battlers.h"
using namespace std;

//Non-Generic Functions (for my level of knowledge in coding currently)

double Battler::CalculateDamage(Battler& opponent, Move move, char attackType) {

    double output;

    /*the attack's output depends on the battler's stats and type
    in relation to the move's stats and types*/

    /* output = pA * mM - (pD * mM) / 2 */

    /*output = battler's relevant attack stat times a move's damage
    multiplier, minus the opponent's all of which is multiplied by a multiplier if the types match*/

    //relevant attack stat times damage multiplier

    if (attackType == 'p') {
        output = this->physicalAttack * move.GetDamageMultiplier();
    }
    if (attackType == 's') {
        output = this->specialAttack * move.GetDamageMultiplier();
    }
    //identify if special move used, uses the average of the pA and sA
    if (attackType == 'X') {
        output = (this->physicalAttack + this->specialAttack) / 2.0 * move.GetDamageMultiplier();
    }
    
    //relevant defense stat times damage multiplier

    if (attackType == 'p') {
        output -= ( opponent.physicalDefense * move.GetDamageMultiplier() ) / 2.0;
    }
    if (attackType == 's') {
        output -= ( opponent.specialDefense * move.GetDamageMultiplier() ) / 2.0;
    }
    //identify if special move used, uses the average (4 to account for both defense and the ratio of the special move)
    if (attackType == 'X') {
        output -= (this->physicalAttack + this->specialAttack) * move.GetDamageMultiplier() / 4.0;
    }

    //if defense overwhelms the attack, then we shouldn't have a negative output!

    if (output <= 1) {
        output = 1;
        cout << "Insignificant hit... maybe try another move..." << endl;
    }

    //type matching multiplier

    if (this->type.GetTypeName() == move.GetMoveTypeName()) {
        output *= 1.10; //battler's moves are amped if types match
    }

    return output;

}

double Battler::Attack(Battler& opponent, int t, int ignore) {
    /*if this runs with t = 0, then the battler is not
     controlled by a player!*/
    /*variable 't' is to be overriden by user's choice in Player
    class' Attack function*/

    double damage_output;
    Move currMove;

    if (t == 1) {
        currMove = this->move1;
    }
    else if (t == 2) {
        currMove = this->move2;
    }
    else if (t == 3) {
        currMove = this->move3;
    }
    else {

        srand(time(NULL));
        int random_number = rand();
        /*using an random number generator function let's the computer
        have a way to choose moves*/

        if (random_number % 3 == 0) {
            currMove = this->move1;
        }
        if (random_number % 3 == 1) {
            currMove = this->move2;
        }
        if (random_number % 3 == 2) {
            currMove = this->move3;
        }
    }

    if (currMove.GetDamageType() == 'X' && ignore != 1) {
        //gives a special negative number which determines special attack function
        double special_output = this->SpecialMoveIdentifier(currMove.GetMoveName());

        return special_output; /*will check for a negative number outside the class*/

    }
    else {

        damage_output = CalculateDamage(opponent, currMove, currMove.GetDamageType());

        if (currMove.GetMoveTypeName() == opponent.type.GetWeakness()) {
            damage_output *= 1.15;
            cout << "Critical hit! ";
        }
        else if (currMove.GetMoveTypeName() == opponent.type.GetStrength()) {
            damage_output *= 0.85;
            cout << "Weak hit... ";
        }

        opponent.SetHealth(opponent.GetHealth() - damage_output);

        if (opponent.GetHealth() < 0) {
            opponent.SetHealth(0);
        }

        cout << this->name << " used " << currMove.GetMoveName() << " for ";
        cout << damage_output << " points of damage!" << endl;

        if (opponent.GetHealth() == 0) {
            cout << opponent.GetName() << " has been defeated!" << endl;
            return -99.9; /*will check for specifcially -99.9 for defeated battlers*/
        }

        return damage_output;

    }

}

Battler& Battler::operator=(const Battler& otherBattler) { //copy assignment for rule of 3
    this->name = otherBattler.name;
    this->SetImage(otherBattler.image);
    this->type = otherBattler.type;
    this->health = otherBattler.health;
    this->physicalAttack = otherBattler.physicalAttack;
    this->physicalDefense = otherBattler.physicalDefense;
    this->specialAttack = otherBattler.specialAttack;
    this->specialDefense = otherBattler.specialDefense;
    this->move1 = otherBattler.move1;
    this->move2 = otherBattler.move2;
    this->move3 = otherBattler.move3;
    this->playerStatus = otherBattler.playerStatus;

    return *this;
}

void GlobalSpecialMoves(Battler currBattler, Battler opponentBattler, double negative) {
    if (negative == -1.001) { //Shapesitto's Transform
        currBattler = opponentBattler;
    }
}

//Battler Class Generic Functions

Battler::Battler(string name) : name(name), type(Type()), health(0.0), physicalAttack(0),
physicalDefense(0), specialAttack(0), specialDefense(0), move1(Move()), move2(Move()),
move3(Move()), playerStatus(false), image(nullptr) {}

Battler::Battler(const Battler& otherBattler) : name(otherBattler.name), type(otherBattler.type),
health(otherBattler.health), physicalAttack(otherBattler.physicalAttack), physicalDefense(otherBattler.physicalDefense), 
specialAttack(otherBattler.specialAttack), specialDefense(otherBattler.specialDefense),
move1(otherBattler.move1), move2(otherBattler.move2), move3(otherBattler.move3), 
playerStatus(otherBattler.playerStatus), image(nullptr) { //copy constructor for rule of 3

    this->SetImage(otherBattler.image);

}

Battler::~Battler() {

    /*Deallocate dynamic memory in image*/
    
    if (this->image != nullptr) {

        for (unsigned int i = 0; i < 15; i++) {
            delete[] this->image[i];
            this->image[i] = nullptr;
        }

        delete[] this->image;
        this->image = nullptr;
    }

}

void Battler::SetImage(char new_image[15][10]) {

    /*this SetImage function should be used when creating a new battler, since
    the an array as an input is created when reading the helper file*/

    /*dimensions of input images should always be 15 width x 10 height
    characters, using column major order so we can use [x][y] logic*/

    /*Deallocate memory for existing image if possible*/

    if (this->image != nullptr) {
        for (unsigned int i = 0; i < 15; i++) {
            delete[] this->image[i];
            this->image[i] = nullptr;
        }
    }

    /*Allocate new memory for new image*/

    this->image = new char*[15];

    for (unsigned int i = 0; i < 15; i++) {
        this->image[i] = new char[10];
    }

    /*Copy input image to current battler's image*/

    for (unsigned int i = 0; i < 15; i++) {
        for (unsigned int j = 0; j < 10; j++) {
            this->image[i][j] = new_image[i][j];
        }
    }

}

void Battler::SetImage(char** new_image) {

    /*this SetImage function should only be used in the copy assignment function*/

    /*dimensions of input images should always be 15 width x 10 height
    characters, using column major order so we can use [x][y] logic*/

    /*Deallocate memory for existing image if possible*/

    if (this->image != nullptr) {

        for (unsigned int i = 0; i < 15; i++) {
            delete[] this->image[i];
            this->image[i] = nullptr;
        }

        delete[] this->image;
        this->image = nullptr;
    }

    /*Allocate new memory for new image*/

    this->image = new char*[15];

    for (unsigned int i = 0; i < 15; i++) {
        this->image[i] = new char[10];
    }

    /*Copy input image to current battler's image*/

    for (unsigned int i = 0; i < 15; i++) {
        for (unsigned int j = 0; j < 10; j++) {
            this->image[i][j] = new_image[i][j];
        }
    }

    /*Deallocation of the new memory from this function as well as
    from the input image, which should be from another battler, will
    occur in the deconstructor*/

}

void Battler::SetType(string type, string strength, string weakness) {
    this->type = Type(type, strength, weakness);
}

void Battler::SetHealth(double health) {
    this->health = health;
}

void Battler::SetStats(int pA, int pD, int sA, int sD) {
    this->physicalAttack = pA;
    this->physicalDefense = pD;
    this->specialAttack = sA;
    this->specialDefense = sD;
}

void Battler::SetPhysicalAttack(double pA) {
    this->physicalAttack = pA;
}

void Battler::SetSpecialAttack(double sA) {
    this->specialAttack = sA;
}

void Battler::SetPhysicalDefense(double pD) {
    this->physicalDefense = pD;
}

void Battler::SetSpecialDefense(double sD) {
    this->specialDefense = sD;
}

void Battler::SetPlayingStatus(bool status) {
    this->playerStatus = status;
}

string Battler::GetName() {
    return this->name;
}

double Battler::GetHealth() {
    return this->health;
}

string Battler::GetMoves() {
    string output;

    output.append("1.");
    output.append(this->move1.GetMoveName());
    output.append(" 2.");
    output.append(this->move2.GetMoveName());
    output.append(" 3.");
    output.append(this->move3.GetMoveName());
    output.append(" ");

    return output;
}

int Battler::GetPhysicalAttack() {
    return this->physicalAttack;
}

int Battler::GetSpecialAttack() {
    return this->specialAttack;
}

int Battler::GetPhysicalDefense() {
    return this->physicalDefense;
}

int Battler::GetSpecialDefense() {
    return this->specialDefense;
}

bool Battler::GetPlayerStatus() {
    return this->playerStatus;
}

void Battler::AddMove(string name, string type, char dType, double multiplier) {    
    if (this->move1.GetMoveName() == "") {
        this->move1 = Move(name, type, dType, multiplier);
    }
    else if (this->move2.GetMoveName() == "") {
        this->move2 = Move(name, type, dType, multiplier);
    }
    else if (this->move3.GetMoveName() == "") {
        this->move3 = Move(name, type, dType, multiplier);
    }
}

double Battler::SpecialMoveIdentifier(string move) {

    /*the purpose of this function is the streamline code inside of 
    the Attack function since this part can get long if many
    special moves exist*/

    if (move == "Transform") {

        /*an iconic move of Pokemon's Ditto, this move transforms the
        battler to the opponent's battler!*/

        return -1.001;

    }
    else if (move == "Flaming_Devastation") {

        /*a risk-based move, which trades a high damaging move for a
        20% debuff to the user's special attack stat*/

        return -1.002;

    }

    //else if...

    /*future possible updates can easily have more special attacks here,
    such as a move that amplifies the battler's power*/

    return 0; //signifies no special move was found, could ask user for another move but not the focus of project

}

//Type Class Generic Functions

Type::Type() : name(""), strength1(""), weakness1("") {}

Type::Type(string name, string s, string w) : name(name), strength1(s), weakness1(w) {}

void Type::SetTypeName(string name) {
    this->name = name;
}

void Type::SetStrengths(string s) {
    this->strength1 = s;
}

void Type::SetWeaknesses(string w) {
    this->weakness1 = w;
}

string Type::GetTypeName() {
    return this->name;
}

string Type::GetStrength() {
    return this->strength1;
}

string Type::GetWeakness() {
    return this->weakness1;
}

//Move Class Generic Functions

Move::Move() : name(""), attackType(""), damageType('\0'), damageMultiplier(0.0) {}

Move::Move(string name, string type, char dType, double multiplier) : name(name), attackType(type), damageType(dType), damageMultiplier(multiplier) {
}

void Move::SetMoveName(string name) {
    this->name = name;
}

void Move::SetMoveType(string type) {
    this->attackType = type;
}

void Move::SetDamageType(char dType) {
    this->damageType = dType;
}

void Move::SetMultiplier(double multiplier) {
    this->damageMultiplier = multiplier;
}

string Move::GetMoveName() {
    return this->name;
}

string Move::GetMoveTypeName() {
    return this->attackType;
}

char Move::GetDamageType() {
    return this->damageType;
}

double Move::GetDamageMultiplier() {
    return this->damageMultiplier;
}
