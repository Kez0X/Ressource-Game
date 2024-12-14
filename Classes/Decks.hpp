#ifndef DECKS_H
#define DECKS_H

#include <vector>
#include "Card.hpp"
#include "Cell.hpp"

class Decks {

    private:
        // TODO: Définition infinie de Card
        Card AcierRessourceDeck;
        Card BoisRessourceDeck;
        Card SableRessourceDeck;
        Card PierreRessourceDeck;
        Card OrRessourceDeck;
        Card NourritureRessourceDeck;
        Card ArgentRessourceDeck;
        Card BleRessourceDeck;

        std::vector<Card> BonusDeck;

    public:
        Decks();

        int fillRessourcesDecksFromJson();
        int fillBonusDecksFromJson();

        std::vector<Card> getBonusDeck() const;

        void shuffleDecks();

        Card drawCardFromRessourceDeck(Ressource);
        Card drawCardFromBonusDeck(std::string);

        void addCardToBonusDeck(Card card);
};

#endif