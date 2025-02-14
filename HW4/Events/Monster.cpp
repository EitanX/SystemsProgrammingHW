#include "Monster.h"
#include <vector>
#include <string>


//Monster is a pure abstract class
//Each monster has its ouw methods. most are the same.
//Decided for each monster to have its own methods for flex-ability!
//For example: in the future, a monster that can shape-shift into another monster.
//Each Monster has its own postFightEffect - Balrog: +2 force points.
//                                           Pack: updateStats() method.
//--------------------------------------------------------------------------------------------------
//Snail
string Snail::getIdentity() {
    return "Snail";
}
unsigned int Snail::getCombatPower() {
    return this->combatPower;
}
unsigned int Snail::getLoot() {
    return this->loot;
}
unsigned int Snail::getDamage() {
    return this->damage;
}
unsigned int Snail::getSizeOfPack() {
    return this->sizeOfPack;
}
void Snail::postFightEffect() {}

//Slime
string Slime::getIdentity() {
    return "Slime";
}
unsigned int Slime::getCombatPower() {
    return this->combatPower;
}
unsigned int Slime::getLoot() {
    return this->loot;
}
unsigned int Slime::getDamage() {
    return this->damage;
}
unsigned int Slime::getSizeOfPack() {
    return this->sizeOfPack;
}
void Slime::postFightEffect() {}

//Balrog
string Balrog::getIdentity() {
    return "Balrog";
}
unsigned int Balrog::getCombatPower() {
    return this->combatPower;
}
unsigned int Balrog::getLoot() {
    return this->loot;
}
unsigned int Balrog::getDamage() {
    return this->damage;
}
unsigned int Balrog::getSizeOfPack() {
    return this->sizeOfPack;
}
void Balrog::postFightEffect() {
    this->combatPower = this->combatPower + 2;
}

//Pack
Pack::Pack(const std::vector<std::shared_ptr<Monster>> monsters) {
    this->monsters = monsters;
    this->updateStats();
}
string Pack::getIdentity() {
    return "Pack";
}
unsigned int Pack::getCombatPower() {
    return this->combatPower;
}
unsigned int Pack::getLoot() {
    return this->loot;
}
unsigned int Pack::getDamage() {
    return this->damage;
}
unsigned int Pack::getSizeOfPack() {
    return this->sizeOfPack;
}
void Pack::updateStats() {
    unsigned int totalCombatPower = 0;
    unsigned int totalLoot = 0;
    unsigned int totalDamage = 0;
    unsigned int totalSizeOfPack = 0;
    for (std::shared_ptr<Monster> m: monsters) {
        totalCombatPower += m->getCombatPower();
        totalLoot += m->getLoot();
        totalDamage += m->getDamage();
        //totalSizeOfPack += m->getSizeOfPack();
        totalSizeOfPack++;
    }
    this->combatPower = totalCombatPower;
    this->loot = totalLoot;
    this->damage = totalDamage;
    this->sizeOfPack = totalSizeOfPack;
}
void Pack::postFightEffect() {
    for (std::shared_ptr<Monster> m: monsters) {
        m->postFightEffect();
    }
    this->updateStats();
}


