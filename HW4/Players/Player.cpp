#include "Player.h"
#include "Job.h"
#include "Character.h"
#include <memory>
#include <vector>
#include <string>

//Player is devided into 3 in our implementation.
//PlayerStats
//Job
//Character

//simple getters
//some forward the get by using the corresponding get of PlayerStats getters.
string Player::getName() const {
    return this->playerStats->getName();
}
string Player::getDescription() const {
    //Player: Daniel, Warrior with Responsible character (level 1, force 5)
    string nameString, jobString, characterString, levelString, forceString;
    nameString = this->playerStats->getName();
    jobString = this->job->getDescription();
    characterString = this->character->getDescription();
    levelString = std::to_string(this->getLevel());
    forceString = std::to_string((this->getForce()));
    return nameString + ", " + jobString + " with " + characterString + " character (level "
           + levelString + ", force " + forceString + ")";
}
PlayerStats& Player::getPlayerStats() const {
    return *this->playerStats;
}
Job& Player::getJob() const {
    return *(this->job);
}
Character& Player::getCharacter() const {
    return *(this->character);
}
int Player::getLevel() const {
    return this->playerStats->getLevel();
}
int Player::getForce() const {
    return this->playerStats->getForce();
}
unsigned int Player::getMaxHP() const {
    return this->playerStats->getMaxHP();
}
int Player::getHealthPoints() const {
    return this->playerStats->getCurrentHP();
}
int Player::getCoins() const {
    return this->playerStats->getCoins();
}
bool Player::isFainted() const {
    return this->playerStats->isFainted();
}

//simple setters
//forwarding the set by using the corresponding set of PlayerStats setters.
void Player::levelUp() {
    this->playerStats->levelUp();
}
void Player::setForcePointsBy(int amount) {
    this->playerStats->setForcePointsBy(amount);
}
void Player::setMaxHP(int value) {
    this->playerStats->setMaxHP(value);
}
void Player::setCurrentHPBy(int amount) {
    this->playerStats->setCurrentHPBy(amount);
}
void Player::setCoinsBy(int amount) {
    this->playerStats->setCoinsBy(amount);
}
void Player::setIsFainted() {
    this->playerStats->setIsFainted();
}

//PRIVATE METHOD: called inside the constructor only!!!
void Player::initPerks() {
    this->job->initPerks(*this->playerStats);
}

//C'tor
Player::Player(std::unique_ptr<PlayerStats> playerStats,
               std::unique_ptr<Job> job,
               std::unique_ptr<Character> character)
        : playerStats(std::move(playerStats)),
          job(std::move(job)),
          character(std::move(character)) {
    initPerks();
}
