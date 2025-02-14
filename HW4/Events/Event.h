#pragma once

#include "../Players/Player.h"
#include "Monster.h"
#include <vector>
#include <memory>

class Event {
public:
    /**
     * Gets the description of the event
     *
     * @return - the description of the event
    */
    virtual string getDescription() const = 0;
    virtual string playEvent(Player& player) = 0;

    virtual ~Event() = default;
};

//--------------------------------------------Encounter--------------------------------------------
class Encounter : public Event {
    string description;
    std::shared_ptr<Monster> monster;
public:
    Encounter() = delete;
    Encounter(std::shared_ptr<Monster> monster);
    ~Encounter() = default;
    unsigned int getCombatPower();
    unsigned int getLoot();
    unsigned int getDamage();
    string getDescription() const override;
    void updateDescriptiopn();
    string playEvent(Player& player) override;
    string eventWon(Player& player);
    string eventLost(Player& player);
};

//------------------------------------------Special Event------------------------------------------
class SpecialEvent : public Event {
protected:
    virtual string apply(Player& player) = 0;
};

class SolarEclipse : public SpecialEvent {
    string description = "SolarEclipse";
    string apply(Player& player) override;
public:
    string getDescription() const override;
    string playEvent(Player& player) override;
};

class PotionsMerchant : public SpecialEvent {
    string description = "PotionsMerchant";
    string apply(Player& player) override;
public:
    string getDescription() const override;
    string playEvent(Player& player) override;
};

