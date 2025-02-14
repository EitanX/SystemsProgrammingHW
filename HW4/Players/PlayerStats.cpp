#include "PlayerStats.h"
#include <string>
#include <stdexcept>

using std::string;

//simple getters
string PlayerStats::getName() const {
    return this->name;
}
int PlayerStats::getLevel() const {
    return this->level;
}
int PlayerStats::getForce() const {
    return this->force;
}
unsigned int PlayerStats::getMaxHP() const {
    return this->maxHP;
}
int PlayerStats::getCurrentHP() const {
    return this->currentHP;
}
int PlayerStats::getCoins() const {
    return this->coins;
}
bool PlayerStats::isFainted() const {
    return this->flagFainted;
}

//simple setters
void PlayerStats::levelUp() {
    this->level = this->level + 1;
}
void PlayerStats::setForcePointsBy(int amount) {
    if (amount < 0) {
        if (this->force + amount <= 0) {
            this->force = 0;
            return;
        }
    }
    this->force = this->force + amount;
}
void PlayerStats::setMaxHP(unsigned int value) {
    this->maxHP = value;
}
void PlayerStats::setCurrentHP(unsigned int value) {
    this->currentHP = value;
}
void PlayerStats::setCurrentHPBy(int amount) {
    if (amount < 0) {
        if (this->currentHP + amount <= 0) {
            this->currentHP = 0;
            this->flagFainted = true;
            return;
        }
    }
    int maxHP = this->maxHP;
    if (this->currentHP + amount > maxHP) {
        this->currentHP = this->maxHP;
        return;
    }
    this->currentHP = this->currentHP + amount;
}
void PlayerStats::setCoinsBy(int amount) {
    if (this->coins + amount < 0) {
        throw std::runtime_error("illegal financial move somehow...???");
    }
    this->coins = this->coins + amount;
}
void PlayerStats::setIsFainted() {
    this->flagFainted = true;
}

PlayerStats::PlayerStats(std::string name) : name(name) {}