#include "Player.hpp"
#include <iostream>
#include <cassert>
#include <map>


// Constructeurs
Player::Player(std::string name){
    _name = name;
    _deck = {};
    _bonus = 0;
    _score = 0;
};

Player::Player(std::string name, int score){
    _name = name;
    _deck = {};
    _bonus = 0;
    _score = score;
};

Player::Player(std::string name, std::vector<Card> deck){
    _name = name;
    _deck = deck;
    _bonus = 0;
    _score = 0;
};

Player::Player(std::string name, std::vector<Card> deck, int bonus, int score){
    _name = name;
    _deck = deck;
    _bonus = bonus;
    _score = score;
}

// Getters
std::string Player::getName() {
    return _name;
};
std::vector<Card> Player::getDeck() {
    return _deck;
};

std::vector<Card> Player::getDeckFilter(TypeCard _cardType)
{
    std::vector<Card> filteredDeck;

    for (int i = 0; i < _deck.size(); i++)
    {
        Card _card = _deck[i];
        if (_card.getType() == _cardType)
        {
            filteredDeck.push_back(_card);
        }
    }

    return filteredDeck;
}

int Player::getBonus() {
    return _bonus;
};
int Player::getScore() {
    return _score;
};

// Setters
void Player::setName(std::string name){
    _name = name;
};

void Player::setBonus(int bonus){
    _bonus = bonus;
};

void Player::setScore(int score){
    _score = score;
};

void Player::setDeck(std::vector<Card> _newdeck) {
    _deck = _newdeck;
}

//Méthodes
void Player::addCard(Card carte){
    _deck.push_back(carte);
};

void Player::printDeck() {
    std::map<std::string, int> mapCount;
    std::map<std::string, Card> mapCard;

    std::cout << "\n\n" <<  _name << "\n" << std::endl;

    // On comptabilise les cartes dans mapCount et stocker les informations dans mapCard
    for (int i = 0; i < _deck.size(); i++) {
        if (mapCount.find(_deck[i].getTitre()) != mapCount.end()) {
            mapCount[_deck[i].getTitre()]++;
        } else {
            mapCount[_deck[i].getTitre()] = 1;
            mapCard[_deck[i].getTitre()] = _deck[i];
        }
    }

     std::cout << "=== Cartes Ressources ===\n";
    for (const auto& pair : mapCount) {
        if (mapCard[pair.first].getType() != bonus) {
            std::cout << pair.first << " ( " << std::to_string(pair.second) << " ) \n"
                      << "Description : " << mapCard[pair.first].getDesc() << "\n"
                      << "Rareté : " << mapCard[pair.first].getRarete() << "\n\n";
        }
    }

    // On sépare par types de cartes
    std::cout << "=== Cartes Bonus ===\n";
    for (const auto& pair : mapCount) {
        if (mapCard[pair.first].getType() == bonus) {
            std::string statut;
            if (mapCard[pair.first].getStatus() == NotUse) {
                statut = "Pas encore utilisé";
            } else if (mapCard[pair.first].getStatus() == Using) {
                statut = "En cours d'utilisation";
            } else {
                statut = "Déjà utilisé";
            }
            std::cout << pair.first << " ( " << std::to_string(pair.second) << " ) \n"
                      << "Description : " << mapCard[pair.first].getDesc() << "\n"
                      << "Rareté : " << mapCard[pair.first].getRarete() << "\n"
                      << "Statut : " << statut << "\n\n";
        }
    }
   
}

void Player::printDeckBonus(){
    std::map<std::string, int> mapCount;
    std::map<std::string, Card> mapCard;

    std::cout << "\n\n" <<  _name << "\n" << std::endl;

    // On comptabilise les cartes dans mapCount et stocker les informations dans mapCard
    for (int i = 0; i < _deck.size(); i++) {
        if (mapCount.find(_deck[i].getTitre()) != mapCount.end()) {
            mapCount[_deck[i].getTitre()]++;
        } else {
            mapCount[_deck[i].getTitre()] = 1;
            mapCard[_deck[i].getTitre()] = _deck[i];
        }
    }

    // On sépare par types de cartes
    std::cout << "=== Cartes Bonus ===\n";
    for (const auto& pair : mapCount) {
        if (mapCard[pair.first].getType() == bonus) {
            std::string statut;
            if (mapCard[pair.first].getStatus() == NotUse) {
                statut = "Pas encore utilisé";
            } else if (mapCard[pair.first].getStatus() == Using) {
                statut = "En cours d'utilisation";
            } else {
                statut = "Déjà utilisé";
            }
            std::cout << pair.first << " ( " << std::to_string(pair.second) << " ) \n"
                      << "Description : " << mapCard[pair.first].getDesc() << "\n"
                      << "Rareté : " << mapCard[pair.first].getRarete() << "\n"
                      << "Statut : " << statut << "\n\n";
        }
    }
}