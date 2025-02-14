#pragma once

#include <string>

using std::string;

class PlayerStats {
    string name;
    unsigned int level = 1;
    unsigned int force = 5;
    unsigned int maxHP = 100;
    int currentHP = maxHP;
    int coins = 10;
    bool flagFainted = false;
public:
    string getName() const;
    void setName(string name);
    int getLevel() const;
    int getForce() const;
    unsigned int getMaxHP() const;
    int getCurrentHP() const;
    int getCoins() const;
    bool isFainted() const;
    void levelUp();
    void setForcePointsBy(int amount);
    void setMaxHP(unsigned int value);
    void setCurrentHP(unsigned int value);
    void setCurrentHPBy(int amount);
    void setCoinsBy(int amount);
    void setIsFainted();

    PlayerStats() = delete;
    PlayerStats(string name);
    ~PlayerStats() = default;
};