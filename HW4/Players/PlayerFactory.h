#pragma once

#include "Player.h"
#include "Job.h"
#include "Character.h"
#include "PlayerStats.h"
#include <memory>


class PlayerFactory {
private:
    static std::unique_ptr<Job> makeJob(std::string job);
    static std::unique_ptr<Character> makeCharacter(std::string character);
    static std::unique_ptr<PlayerStats> makePlayerStats(std::string name);
public:
    static std::unique_ptr<Player> makePlayer(string nameOfPlayer,
                                              std::istream& playersStream);
};


