#pragma once

#include <string>
#include <memory>
#include "Job.h"
#include "Character.h"
#include "PlayerStats.h"

using std::string;

class Player {
private:
    std::unique_ptr<PlayerStats> playerStats;
    std::unique_ptr<Job> job;
    std::unique_ptr<Character> character;

    void initPerks();
public:
    /**
     * Gets the description of the player
     *
     * @return - description of the player
    */
    string getDescription() const;
    /**
     * Gets the name of the player
     *
     * @return - name of the player
    */
    string getName() const;
    /**
     * Gets the current level of the player
     *
     * @return - level of the player
    */
    int getLevel() const;
    /**
     * Gets the of force the player has
     *
     * @return - force points of the player
    */
    int getForce() const;
    /**
     * Gets the amount of health points the player currently has
     *
     * @return - health points of the player
    */
    int getHealthPoints() const;
    /**
     * Gets the amount of coins the player has
     *
     * @return - coins of the player
    */
    int getCoins() const;

    //-------------------------------------------Methods-------------------------------------------
    PlayerStats& getPlayerStats() const;
    Job& getJob() const;
    Character& getCharacter() const;
    unsigned int getMaxHP() const;
    bool isFainted() const;
    void setForcePointsBy(int amount);
    void setMaxHP(int value);
    void setCurrentHPBy(int amount);
    void setCoinsBy(int amount);
    void levelUp();
    void setIsFainted();
    //-----------------------------------------C'tor D'tor-----------------------------------------
    Player() = delete;
    Player(std::unique_ptr<PlayerStats> playerStats,
           std::unique_ptr<Job> job,
           std::unique_ptr<Character> character);
    ~Player() = default;
};
