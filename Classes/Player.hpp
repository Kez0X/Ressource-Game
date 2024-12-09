#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "Card.hpp"

class Player
{
private:
    std::string _name;
    std::vector<Card> _deck;
    std::vector<std::string> _bonus; // Une liste d'id des bonus associés aux joueurs qui sont actuellement actifs
    int _score;

public:
    // Constructeurs
    Player(std::string);
    Player(std::string, std::vector<Card>);
    Player(std::string, std::vector<Card>, std::vector<std::string>, int);

    // Getters
    std::string getName();
    std::vector<Card> getDeck();
    std::vector<std::string> getBonus();
    int getScore();

    // Setters
    void setName(std::string);
    void setBonus(std::vector<std::string>);
    void setScore(int);

    // Méthodes
    void addCard(Card);
};

#endif