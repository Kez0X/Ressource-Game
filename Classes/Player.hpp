#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>

class Player
{
private:
    std::string _name;
    std::vector<Card> _deck;
    std::vector<Bonus> _bonus;
    int _score;

public:
    // Constructeurs
    Player(const std::string&, std::vector<Card>&);
    Player(const std::string&, std::vector<Card>&, std::vector<Bonus>&, int&);

    // Getters
    std::string getName() const;
    std::vector<Card> getDeck() const;
    std::vector<Bonus> getBonus() const;
    int getScore() const;
};

#endif