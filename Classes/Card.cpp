#include "Card.hpp"
#include <iostream>
#include <cassert>


Card::Card(std::string id, std::string titre, std::string desc, std::string rarete, TypeCard type){
    _id = id;
    _titre = titre;
    _desc = desc;
    _rarete = rarete;
    _type = type;
    _active = false;
    _status = NotUse;
};

Card::Card(std::string id, std::string titre, std::string desc, std::string rarete, TypeCard type, bool active){
    _id = id;
    _titre = titre;
    _desc = desc;
    _rarete = rarete;
    _type = type;
    _active = active;
    _status = NotUse;
};

Card::Card(std::string id, std::string titre, std::string desc, std::string rarete, TypeCard type, bool active, status status){
    _id = id;
    _titre = titre;
    _desc = desc;
    _rarete = rarete;
    _type = type;
    _active = active;
    _status = status;
};

// Getters
std::string Card::getId(){
    return _id;
};
std::string Card::getTitre(){
    return _titre;
};
std::string Card::getDesc(){
    return _desc;
};
std::string Card::getRarete(){
    return _rarete;
};
TypeCard Card::getType(){
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