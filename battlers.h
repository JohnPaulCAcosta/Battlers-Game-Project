#ifndef BATTLERS_h
#define BATTLERS_h
using namespace std;

class Type {
    private:
        string name;
        string strength1;
        string weakness1;
    public:
        Type();
        Type(string name, string s = "", string w = "");
        void SetTypeName(string name);
        void SetStrengths(string s);
        void SetWeaknesses(string w);
        string GetTypeName();
        string GetStrength();
        string GetWeakness();
};

class Move {
    private:
        string name;
        string attackType;
        char damageType; //'p' or 's' or 'X'
        double damageMultiplier;
    public:
        Move();
        Move(string name, string type, char dType, double multiplier);
        void SetMoveName(string name);
        void SetMoveType(string type);
        void SetDamageType(char dType);
        void SetMultiplier(double multiplier);
        string GetMoveName();
        string GetMoveTypeName();
        char GetDamageType();
        double GetDamageMultiplier();
};

class Battler {
    private:
        string name;
        Type type;
        double health;
        int physicalAttack;
        int physicalDefense;
        int specialAttack;
        int specialDefense;
        Move move1;
        Move move2;
        Move move3;
        bool playerStatus = false;

    public:
        char** image;
        Battler(string name);
        ~Battler();
        Battler(const Battler& otherBattler);
        void SetImage(char new_image[15][10]);
        void SetImage(char** new_image);
        void SetType(string type, string strength = "", string weakness = "");
        void SetHealth(double health);
        void SetStats(int pA, int pD, int sA, int sD);
        void SetPlayingStatus(bool status);
        string GetName();
        double GetHealth();
        string GetMoves();
        bool GetPlayerStatus();
        void AddMove(string name, string type, char dType, double multiplier);
        double Attack(Battler& opponent, int t = 0);
        double CalculateDamage(Move move, char attackType);
        double SpecialMoveIdentifier(string move);
        Battler& operator=(const Battler& otherBattler);

};

void GlobalSpecialMoves(Battler battler, Battler opponentBattler, double negative);

#endif
