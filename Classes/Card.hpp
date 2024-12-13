#ifndef CARD_H
#define CARD_H

#include <string>
#include "Cell.hpp"

enum TypeCard
{
    bonus,
    ressource
};

enum status
{
    NotUse,
    Using,
    alreadyUse
};

class Card
{
private:
    std::string _id;
    std::string _titre;
    std::string _desc;
    std::string _rarete;
    TypeCard _type;
    bool _active;
    status _status;

public:
    //ructeurs
    Card();
    Card(std::string, std::string, std::string, std::string, TypeCard);
    Card(std::string, std::string, std::string, std::string, TypeCard, bool);
    Card(std::string, std::string, std::string, std::string, TypeCard, bool, status);

    // Getters
    std::string getId();
    std::string getTitre();
    std::string getDesc();
    std::string getRarete();
    TypeCard getType();
    status getStatus();

    // Setters
    void setActiveCard();
    void setDesactiveCard();
    void setNotUseStatus();
    void setUsingStatus();
    void setAlreadyUseStatus();
};

#endif