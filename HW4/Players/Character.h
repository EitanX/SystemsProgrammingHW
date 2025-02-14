#pragma once

#include <string>

using std::string;

class Character {
public:
    virtual string getDescription() const = 0;
    virtual int howManyPotions(unsigned int hp, unsigned int coins, unsigned int maxHP) const = 0;
    virtual ~Character() = default;
};

class Responsible : public Character {
    string description = "Responsible";
public:
    string getDescription() const override;
    int howManyPotions(unsigned int hp, unsigned int coins, unsigned int maxHP) const override;
};

class RiskTaking : public Character {
    string description = "RiskTaking";
public:
    string getDescription() const override;
    int howManyPotions(unsigned int hp, unsigned int coins, unsigned int maxHP) const override;
};