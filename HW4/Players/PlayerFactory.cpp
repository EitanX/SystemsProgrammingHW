#include "PlayerFactory.h"
#include "Job.h"
#include "Character.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>

using std::unique_ptr;
using std::make_unique;
using std::string;

//functions to check input legality.
static bool isNameLegit(string name) {
    if(name.length() < 3 || name.length() > 15)
    {
        return false;
    }
    for(char c : name)
    {
        if(!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))){
            return false;
        }
    }
    return true;
}
static bool isJobLegit(string job) {
    return (job == "Warrior" || job == "Magician" || job == "Archer");
}
static bool isCharacterLegit(string character) {
    return (character == "Responsible" || character == "RiskTaking");
}
static bool allStringsLegit(string name, string job, string character) {
    return (isNameLegit(name) && isJobLegit(job) && isCharacterLegit(character));
}
//factory functions to build the whole Player
unique_ptr<Job> PlayerFactory::makeJob(string job) {
    if (job == "Warrior") {
        return make_unique<Warrior>();
    }
    if (job == "Magician") {
        return make_unique<Magician>();
    }
    return make_unique<Archer>();
}
unique_ptr<Character> PlayerFactory::makeCharacter(string character) {
    if (character == "Responsible") {
        return make_unique<Responsible>();
    }
    return make_unique<RiskTaking>();
}
unique_ptr<PlayerStats> PlayerFactory::makePlayerStats(string name) {
    return make_unique<PlayerStats>(name);
}
unique_ptr<Player> PlayerFactory::makePlayer(string nameOfPlayer, std::istream& playersStream) {
    string jobString, characterString;
    playersStream >> jobString >> characterString;

    if (!allStringsLegit(nameOfPlayer, jobString, characterString)) {
        throw std::runtime_error("Invalid Players File");
    }

    unique_ptr<Job> job = makeJob(jobString);
    unique_ptr<Character> character = makeCharacter(characterString);
    unique_ptr<PlayerStats> playerStats = makePlayerStats(nameOfPlayer);
    unique_ptr<Player> player = make_unique<Player>(std::move(playerStats),
                                                    std::move(job),
                                                    std::move(character));
    return player;
}
