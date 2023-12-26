#ifndef INTERFACE_h
#define INTERFACE_h
#include "battlers.h"
using namespace std;

vector<Battler> loadHelperData(string fileName);

vector<Battler> selectBattlers(vector<Battler>& allBattlers);

void battleDisplay(vector<Battler>& battlers);

void printGreetings();

//helper function for battle display, determines numbers for certain scenarios 

void InitiateAttackFunctions(Battler& attacker, Battler& opponent, int selected_move = 0);

#endif
