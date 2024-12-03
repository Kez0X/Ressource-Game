#ifndef CARD_H
#define CARD_H

#include <string>
#include <Cell.hpp>

enum TypeCard{
    bonus,
    ressource
};

enum status{
    NotUse,
    Using,
    alreadyUse
};

class Card {
    private:
        std::string _id;
        std::string _titre;
        std::string _desc;
        std::string _rarete;
        TypeCard _type;
        bool _active;
        status _status;

    public:
        // Constructeurs
        Card(std::string& const, std::string& const, std::string& const, std::string& const, std::string& const);

        // Getters
        const std::string getId();
        const std::string getTitre();
        const std::string getDesc();
        const std::string getRarete();
        const std::string getType();

        //Setters
        void setActiveCard();
        void setDesactiveCard();
        void setNotUseStatus();
        void setUsingStatus();
        void setAlreadyUseStatus();
};

#endif