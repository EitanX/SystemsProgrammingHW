#include "Job.h"
#include "PlayerStats.h"

//Job
//Warrior
void Warrior::initPerks(PlayerStats& playerStats) {
    playerStats.setMaxHP(150);
    playerStats.setCurrentHP(150);
}
string Warrior::getDescription() const {
    return this->description;
}
int Warrior::calcCombatPower(int force, int level) {
    return force * 2 + level;
}
void Warrior::applyPostFightConsequences(PlayerStats& playerStats, bool flagWin) {
    if (flagWin) {
        playerStats.setCurrentHPBy(-10);
    }
};


//Archer
void Archer::initPerks(PlayerStats& playerStats) {
    playerStats.setCoinsBy(10);
}
string Archer::getDescription() const {
    return this->description;
}
int Archer::calcCombatPower(int force, int level) {
    return force + level;
}
void Archer::applyPostFightConsequences(PlayerStats& playerStats, bool flagWin) {};

//Magician
void Magician::initPerks(PlayerStats& playerStats) {};
string Magician::getDescription() const {
    return this->description;
}
int Magician::calcCombatPower(int force, int level) {
    return force + level;
}
void Magician::applyPostFightConsequences(PlayerStats& playerStats, bool flagWin) {};