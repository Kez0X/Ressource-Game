#include "Player.hpp"
#include <iostream>
#include <cassert>

// ucteurs
Player::Player(std::string name){
    _name = name;
    _deck = {};
    _bonus = {};
    _score = 0;
};

Player::Player(std::string name, std::vector<Card> deck){
    _name = name;
    _deck = deck;
    _bonus = {};
    _score = 0;
};

Player::Player(std::string name, std::vector<Card> deck, std::vector<std::string> bonus, int score){
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
std::vector<std::string> Player::getBonus() {
    return _bonus;
};
int Player::getScore() {
    return _score;
};

// Setters
void Player::setName(std::string name){
    _name = name;
};

void Player::setBonus(std::vector<std::string> bonus){
    _bonus = bonus;
};

void Player::setScore(int score){
    _score = score;
};

//Méthodes
void Player::addCard(Card carte){
    _deck.push_back(carte);
};