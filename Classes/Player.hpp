#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <Card.hpp>

class Player
{
private:
    std::string _name;
    std::vector<Card> _deck;
    std::vector<std::string> _bonus; // Une liste d'id des bonus associés aux joueurs qui sont actuellement actifs
    int _score;

public:
    // Constructeurs
    Player(const std::string&, std::vector<Card>&);
    Player(const std::string&, std::vector<Card>&, std::vector<std::string>&, int&);

    // Getters
    std::string getName() const;
    std::vector<Card> getDeck() const;
    std::vector<std::string> getBonus() const;
    int getScore() const;

    // Setters
    void setName();
    void setBonus();
    void setScore();

    //Méthodes
    void addCard();
};

#endif