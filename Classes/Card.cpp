#include "Card.hpp"
#include <iostream>
#include <cassert>

Card::Card(){
    _id = "0";
    _titre = "Default";
    _desc = "Default";
    _rarete = "Default";
    _type = ressource;
    _active = false;
    _status = NotUse;
};

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

status Card::getStatus(){
    return _status;
}

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

void Card::setId(std::string id){
    _id = id;
};

void Card::setTitre(std::string titre){
    _titre = titre;
};
void Card::setDesc(std::string desc){
    _desc = desc;
};
void Card::setRarete(std::string rarete){
    _rarete = rarete;
};
void Card::setType(TypeCard type){
    _type = type;
};
void Card::setStatus(status statut){
    _status = statut;
};