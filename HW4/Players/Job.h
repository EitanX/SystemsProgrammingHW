#pragma once

#include <string>
#include <memory>
#include "PlayerStats.h"

using std::string;

class Job {
private:
public:
    virtual void initPerks(PlayerStats& playerStats) = 0;
    virtual string getDescription() const = 0;
    virtual int calcCombatPower(int force, int level) = 0;
    virtual void applyPostFightConsequences(PlayerStats& playerStats, bool flagWin) = 0;

    virtual ~Job() = default;
};


class Warrior : public Job {
private:
    string description = "Warrior";
    string range = "Close Range";
    void initPerks(PlayerStats& playerStats) override;
public:
    string getDescription() const override;
    int calcCombatPower(int force, int level) override;
    void applyPostFightConsequences(PlayerStats& playerStats, bool flagWin) override;
};

class Archer : public Job {
private:
    string description = "Archer";
    string range = "Long Range";
    void initPerks(PlayerStats& playerStats) override;
public:
    string getDescription() const override;
    int calcCombatPower(int force, int level) override;
    void applyPostFightConsequences(PlayerStats& playerStats, bool flagWin) override;
};

class Magician : public Job {
private:
    string description = "Magician";
    string range = "Long Range";
    void initPerks(PlayerStats& playerStats) override;
public:
    string getDescription() const override;
    int calcCombatPower(int force, int level) override;
    void applyPostFightConsequences(PlayerStats& playerStats, bool flagWin) override;
};