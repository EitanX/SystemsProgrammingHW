#include "Event.h"
#include "Monster.h"
#include "../Utilities.h"
#include <memory>
#include <string>

//Event - hold all the necessary logic about each event.
//In our implementation we have a pure virtual class Event
//Encounter/SpecialEvent are children of Event
//Each child has its own additional functions - corresponding to its use.
//All Events have a description string generated at construction.
//--------------------------------------------------------------------------------------------------
//Encounter
Encounter::Encounter(std::shared_ptr<Monster> monster) : monster(monster) {
    updateDescriptiopn();
}
unsigned int Encounter::getCombatPower() {
    return this->monster->getCombatPower();
}
unsigned int Encounter::getLoot() {
    return this->monster->getLoot();
}
unsigned int Encounter::getDamage() {
    return this->monster->getDamage();
}
string Encounter::getDescription() const {
    return this->description;
}
void Encounter::updateDescriptiopn() {
    // set the description of the encounter
    string typeOfMonster = monster->getIdentity();
    string pack;
    if (typeOfMonster == "Pack") {
        pack = "of " + std::to_string(monster->getSizeOfPack()) + " members";
    }
    string stats = "(power " + std::to_string(monster->getCombatPower()) +
                   ", loot " + std::to_string(monster->getLoot()) +
                   ", damage " + std::to_string(monster->getDamage()) +
                   ")";
    if (typeOfMonster == "Pack") {
        this->description = typeOfMonster + " " + pack + " " + stats;
    } else {
        this->description = typeOfMonster + " " + stats;
    }
}
string Encounter::playEvent(Player& player) {
    unsigned int playerCombatPower =
            player.getJob().calcCombatPower(player.getForce(), player.getLevel());
    unsigned int monsterCombatPower = this->getCombatPower();

    string returnString;
    bool flagWinTurn = false;
    if (playerCombatPower > monsterCombatPower) {
        returnString = eventWon(player);
        flagWinTurn = true;
    } else {
        returnString = eventLost(player);
    }

    player.getJob().applyPostFightConsequences(player.getPlayerStats(), flagWinTurn);
    this->monster->postFightEffect();
    this->updateDescriptiopn();

    return returnString;
}
string Encounter::eventWon(Player& player) {
    unsigned int loot = this->getLoot();
    player.setCoinsBy(loot);
    player.levelUp();
    return getEncounterWonMessage(player, loot);
}
string Encounter::eventLost(Player& player) {
    int damage = this->getDamage();
    player.setCurrentHPBy(-damage);
    return getEncounterLostMessage(player, damage);
}

//SpecialEvent
//SolarEclipse
string SolarEclipse::playEvent(Player& player) {
    return apply(player);
}
string SolarEclipse::apply(Player& player) {
    int magicValue = 0;
    string jobDescription = player.getJob().getDescription();
    if (jobDescription == "Magician") {
        magicValue = 1;
    } else {
        player.getForce() > 0 ? magicValue = -1 : magicValue = 0;
    }
    player.setForcePointsBy(magicValue);
    return getSolarEclipseMessage(player, magicValue);
}
string SolarEclipse::getDescription() const {
    return this->description;
}

//PotionsMerchant
string PotionsMerchant::playEvent(Player& player) {
    return apply(player);
}
string PotionsMerchant::apply(Player& player) {
    unsigned int amount = player.getCharacter().howManyPotions(
            player.getHealthPoints(), player.getCoins(), player.getMaxHP());
    for (unsigned int i = 0; i < amount; ++i) {
        player.setCurrentHPBy(10);
        player.setCoinsBy(-5);
    }
    return getPotionsPurchaseMessage(player, amount);
}
string PotionsMerchant::getDescription() const {
    return this->description;
}
