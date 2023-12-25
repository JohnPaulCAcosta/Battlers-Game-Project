#ifndef INTERFACE_h
#define INTERFACE_h
#include "battlers.h"
using namespace std;

vector<Battler> loadHelperData(string fileName);

vector<Battler> selectBattlers(vector<Battler>& allBattlers);

void battleDisplay(vector<Battler>& battlers);

void printGreetings();

#endif