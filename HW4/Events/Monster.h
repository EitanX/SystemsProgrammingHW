
#pragma once

#include "../Players/Player.h"
#include <vector>

class Monster {
public:
    virtual unsigned int getCombatPower() = 0;
    virtual unsigned int getLoot() = 0;
    virtual unsigned int getDamage() = 0;
    virtual unsigned int getSizeOfPack() = 0;
    virtual string getIdentity() = 0;
    virtual void postFightEffect() = 0;

    virtual ~Monster() = default;
};

class Snail : public Monster {
    unsigned int combatPower = 5;
    unsigned int loot = 2;
    unsigned int damage = 10;
    unsigned int sizeOfPack = 1;
public:
    unsigned int getCombatPower() override;
    unsigned int getLoot() override;
    unsigned int getDamage() override;
    unsigned int getSizeOfPack() override;
    void postFightEffect() override;
    string getIdentity() override;
};

class Slime : public Monster {
    unsigned int combatPower = 12;
    unsigned int loot = 5;
    unsigned int damage = 25;
    unsigned int sizeOfPack = 1;
public:
    unsigned int getCombatPower() override;
    unsigned int getLoot() override;
    unsigned int getDamage() override;
    unsigned int getSizeOfPack() override;
    void postFightEffect() override;
    string getIdentity() override;
};

class Balrog : public Monster {
    unsigned int combatPower = 15;
    unsigned int loot = 100;
    unsigned int damage = 9001;
    unsigned int sizeOfPack = 1;
public:
    unsigned int getCombatPower() override;
    unsigned int getLoot() override;
    unsigned int getDamage() override;
    unsigned int getSizeOfPack() override;
    void postFightEffect() override;
    string getIdentity() override;
};

class Pack : public Monster {
    std::vector<std::shared_ptr<Monster>> monsters;
    unsigned int combatPower = 0;
    unsigned int loot = 0;
    unsigned int damage = 0;
    unsigned int sizeOfPack = 0;
public:
    // Pack() will use calculations to construct the data.
    Pack() = delete;
    Pack(const std::vector<std::shared_ptr<Monster>> monsters);
    ~Pack() = default;
    string getIdentity() override;
    void updateStats();
    void postFightEffect() override;
    unsigned int getCombatPower() override;
    unsigned int getLoot() override;
    unsigned int getDamage() override;
    unsigned int getSizeOfPack() override;
};



