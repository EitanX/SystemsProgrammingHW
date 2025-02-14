#pragma once

#include "Event.h"
#include <iostream>
#include <vector>
#include <memory>

class EventFactory {
private:
    static std::shared_ptr<Monster> makePack(std::istream& eventsStream, int amount);
public:
    static std::shared_ptr<Event> makeEvent(string word, std::istream& eventsStream);
};