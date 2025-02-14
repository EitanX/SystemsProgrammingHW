
#include "MatamStory.h"
#include "Utilities.h"
#include "Events/EventFactory.h"
#include "Players/PlayerFactory.h"
#include "Players/Player.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

using std::string;
using std::shared_ptr;
using std::vector;

MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream) {
    /*======= Open and read events file ========*/
    string word;
    while (eventsStream >> word) {
        try {
            this->events.push_back(EventFactory::makeEvent(word, eventsStream));
        } catch (...) {
            throw;
        }
    }
    if (events.size() < 2) {
        throw std::runtime_error("Invalid Events File");
    }
    /*==========================================*/
    /*======= Open and Read players file =======*/
    string name;
    while (playersStream >> name) {
        try {
            this->players.push_back(PlayerFactory::makePlayer(name, playersStream));
        } catch (...) {
            throw;
        }
    }
    if (players.size() < 2 || players.size() > 6) {
        throw std::runtime_error("Invalid Players File");
    }
    /*==========================================*/
    this->m_turnIndex = 1;
    this->iterEvents = events.begin();
}
void MatamStory::playTurn(Player& player) {
    //get the event that needs to be played this turn
    Event& event = *(*this->iterEvents);
    printTurnDetails(m_turnIndex, player, *(*iterEvents));

    // play Event and save the outcome string
    string turnOutcome = event.playEvent(player);
    printTurnOutcome(turnOutcome);

    // logic of event turns: forward turn number + event iterator.
    m_turnIndex++;
    this->iterEvents++;
    if (this->iterEvents == events.end()) {
        this->iterEvents = events.begin();
    }
}
void MatamStory::playRound() {
    printRoundStart();

    // playTurn on each not fainted player.
    for (shared_ptr<Player> singlePlayer: this->players) {
        if (singlePlayer->isFainted()) {
            continue;
        }
        playTurn(*singlePlayer);
    }

    printRoundEnd();

    // print leaderboard at the end of the round.
    // preforming a sort using ALGORITHM, saving it in a new vector.
    printLeaderBoardMessage();
    vector<shared_ptr<Player>> sortedPlayers = getSortedPlayersList();
    int playerNum = 1;
    for (const shared_ptr<Player>& singlePlayer: sortedPlayers) {
        printLeaderBoardEntry(playerNum, *singlePlayer);
        playerNum++;
    }
    printBarrier();
}
bool MatamStory::isGameOver() const {
    if (checkWinner() || checkAllFainted()) {
        return true;
    }
    return false;
}
void MatamStory::play() {
    printStartMessage();
    int i = 1;
    for (shared_ptr<Player>& singlePlayer: this->players) {
        printStartPlayerEntry(i, *singlePlayer);
        i++;
    }
    printBarrier();

    //play a round while the game is not over.
    while (!isGameOver()) {
        playRound();
    }

    //game here is over - handle prints.
    printGameOver();
    if (checkWinner()) {
        Player& winner = findWinner();
        printWinner(winner);
    } else {
        printNoWinners();
    }
}

vector<shared_ptr<Player>> MatamStory::getSortedPlayersList() const {
    // preforming a sort using ALGORITHM, saving it in a new vector.
    vector<shared_ptr<Player>> sortedPlayers = this->players;
    std::sort(sortedPlayers.begin(), sortedPlayers.end(),
              [](shared_ptr<Player> a, shared_ptr<Player> b) {
                  if (a->getLevel() == b->getLevel()) {
                      if (a->getCoins() == b->getCoins()) {
                          return a->getName() < b->getName();
                      }
                      return a->getCoins() > b->getCoins();
                  }
                  return a->getLevel() > b->getLevel();
              });
    return sortedPlayers;
}
bool MatamStory::checkWinner() const {
    for (const shared_ptr<Player>& player: this->players) {
        if (player->getLevel() == 10) {
            return true;
        }
    }
    return false;
}
bool MatamStory::checkAllFainted() const {
    for (const shared_ptr<Player>& player: this->players) {
        if (player->getHealthPoints() != 0) {
            return false;
        }
    }
    return true;
}
Player& MatamStory::findWinner() const {
    vector<shared_ptr<Player>> sortedPlayers = getSortedPlayersList();
    return *(*(sortedPlayers.begin()));
}
