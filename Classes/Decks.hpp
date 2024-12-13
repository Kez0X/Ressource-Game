#include <vector>
#include "Card.hpp"
#include "Cell.hpp"

class Decks {

    private:
        Card AcierRessourceDeck;
        Card BoisRessourceDeck;
        Card SableRessourceDeck;
        Card PierreRessourceDeck;
        Card OrRessourceDeck;
        Card NourritureRessourceDeck;
        Card ArgentRessourceDeck;
        Card BleRessourceDeck;

        std::vector<Card> BonusDeck;

        int fillRessourcesDecksFromJson();
        int fillBonusDecksFromJson();

    public:
        Decks();

        std::vector<Card> getBonusDeck() const;

        void shuffleDecks();

        Card drawCardFromRessourceDeck(Ressource ressource);
        Card drawCardFromBonusDeck();

        void addCardToBonusDeck(Card card);
};