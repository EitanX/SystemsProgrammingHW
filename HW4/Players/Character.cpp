#include "Character.h"

//Character
//Responsible
string Responsible::getDescription() const {
    return this->description;
}
int Responsible::howManyPotions(unsigned int hp, unsigned int coins, unsigned int maxHP) const {
    unsigned int calcByCoins = 0;
    unsigned int calcByHp = 0;
    calcByCoins = coins / 5;
    calcByHp = (maxHP - hp) / 10;
    if ((maxHP - hp) % 10) {
        calcByHp++;
    }

    unsigned int finalAmount = 0;
    if (calcByCoins <= calcByHp) {
        finalAmount = calcByCoins;
    } else {
        finalAmount = calcByHp;
    }

    return finalAmount;
}

//RiskTaking
string RiskTaking::getDescription() const {
    return this->description;
}
int RiskTaking::howManyPotions(unsigned int hp, unsigned int coins, unsigned int maxHP) const {
    int amount = 0;
    if (hp < 50 && coins >= 5) {
        amount = 1;
    }
    return amount;
}