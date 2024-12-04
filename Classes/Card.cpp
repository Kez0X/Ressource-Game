#include "Card.hpp"
#include <iostream>
#include <cassert>


Card::Card(std::string& const id, std::string& const titre, std::string& const desc, std::string& const rarete, TypeCard type){
    _id = id;
    _titre = titre;
    _desc = desc;
    _rarete = rarete;
    _type = type;
    _active = false;
    _status = NotUse;
};

Card::Card(std::string& const id, std::string& const titre, std::string& const desc, std::string& const rarete, TypeCard type, bool active){
    _id = id;
    _titre = titre;
    _desc = desc;
    _rarete = rarete;
    _type = type;
    _active = active;
    _status = NotUse;
};

Card::Card(std::string& const id, std::string& const titre, std::string& const desc, std::string& const rarete, TypeCard type, bool active, status status){
    _id = id;
    _titre = titre;
    _desc = desc;
    _rarete = rarete;
    _type = type;
    _active = active;
    _status = status;
};

// Getters
const std::string Card::getId(){
    return _id;
};
const std::string Card::getTitre(){
    return _titre;
};
const std::string Card::getDesc(){
    return _desc;
};
const std::string Card::getRarete(){
    return _rarete;
};
const TypeCard Card::getType(){
    return _type;
};

//Setters
void Card::setActiveCard(){
    _active = true;
};
void Card::setDesactiveCard(){
    _active = false;
};
void Card::setNotUseStatus(){
    _status = NotUse;
};
void Card::setUsingStatus(){
    _status = Using;
};
void Card::setAlreadyUseStatus(){
    _status = alreadyUse;
};