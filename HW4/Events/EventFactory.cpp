#include "EventFactory.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>

//EventFactory is a  pure abstract class.
//given the string of the event - needed to create - creates it.
//if supplied with PACK - calls makePack wich works recursively in cases of Pack inside Pack.
std::shared_ptr<Event> EventFactory::makeEvent(string word, std::istream& eventsStream) {
    int amount;

    if (word == "Pack") {
        try {
            eventsStream >> amount;
        } catch (...) {
            throw std::runtime_error("Invalid Events File");
        }
        return std::make_shared<Encounter>(makePack(eventsStream, amount));
    } else if (word == "Snail") {
        return std::make_shared<Encounter>(std::make_shared<Snail>());
    } else if (word == "Slime") {
        return std::make_shared<Encounter>(std::make_shared<Slime>());
    } else if (word == "Balrog") {
        return std::make_shared<Encounter>(std::make_shared<Balrog>());
    } else if (word == "SolarEclipse") {
        return std::make_shared<SolarEclipse>();
    } else if (word == "PotionsMerchant") {
        return std::make_shared<PotionsMerchant>();
    } else {
        throw std::runtime_error("Invalid Events File");
    }
}
std::shared_ptr<Monster> EventFactory::makePack(std::istream& eventsStream, int amount) {
    if (amount < 1) {
        throw std::runtime_error("Invalid Events File");
    }
    std::string word;
    int amountRecursive;
    std::vector<std::shared_ptr<Monster>> packVector;
    for (int i = 0; i < amount; ++i) {
        word = "";
        eventsStream >> word;
        if (word == "Pack") {
            try {
                eventsStream >> amountRecursive;
            } catch (...) {
                throw std::runtime_error("Invalid Events File");
            }
            packVector.push_back(makePack(eventsStream, amountRecursive));
        } else if (word == "Snail") {
            packVector.push_back(std::make_shared<Snail>());
        } else if (word == "Slime") {
            packVector.push_back(std::make_shared<Slime>());
        } else if (word == "Balrog") {
            packVector.push_back(std::make_shared<Balrog>());
        } else {
            throw std::runtime_error("Invalid Events File");
        }
    }
    std::shared_ptr<Monster> pack = std::make_shared<Pack>(packVector);
    return pack;
}
