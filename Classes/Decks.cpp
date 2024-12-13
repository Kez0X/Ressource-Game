#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include "../Utils/json.hpp"
#include "Decks.hpp"
#include "Card.hpp"
#include "Cell.hpp"

using json = nlohmann::json;

Decks::Decks()
{
    // Création des decks de ressources et de bonus
    fillRessourcesDecksFromJson();
    fillBonusDecksFromJson();
};

int Decks::fillRessourcesDecksFromJson()
{
    // Ouverture du fichier
    std::ifstream file("ressources.json");

    // On verif si le fichier a été ouvert correctement
    if (!file.is_open())
    {
        std::cerr << "Erreur lors de l'ouverture du fichier !" << std::endl;
        // On retourne -1 en cas d'erreur
        return -1;
    }

    // Pour parser le fichier JSON
    nlohmann::json j;
    file >> j;

    // Afficher le contenu complet du fichier JSON
    std::cout << "Contenu complet du fichier JSON :" << std::endl;
    std::cout << j.dump(4) << std::endl; // dump(4) permet d'afficher le JSON avec une indentation pour la lisibilité // doc officielle github

    // On accede au json et parcourt les ressources
    for (const auto &_ressource : j["ressource"]["commun"])
    {
        if (_ressource["id"] == "Acier")
        {
            AcierRessourceDeck = Card(_ressource["id"], _ressource["titre"], _ressource["desc"], "commun", ressource);
        }

        if (_ressource["id"] == "Bois")
        {
            AcierRessourceDeck = Card(_ressource["id"], _ressource["titre"], _ressource["desc"], "commun", ressource);
        }

        if (_ressource["id"] == "Sable")
        {
            AcierRessourceDeck = Card(_ressource["id"], _ressource["titre"], _ressource["desc"], "commun", ressource);
        }

        if (_ressource["id"] == "Blé")
        {
            AcierRessourceDeck = Card(_ressource["id"], _ressource["titre"], _ressource["desc"], "commun", ressource);
        }

        if (_ressource["id"] == "Nourriture")
        {
            AcierRessourceDeck = Card(_ressource["id"], _ressource["titre"], _ressource["desc"], "commun", ressource);
        }
    }
    for (const auto &_ressource : j["bonus"]["rare"])
    {
        if (_ressource["id"] == "Pierre")
        {
            PierreRessourceDeck = Card(_ressource["id"], _ressource["titre"], _ressource["desc"], "rare", ressource);
        }
    }
    for (const auto &_ressource : j["bonus"]["epique"])
    {
        if (_ressource["id"] == "Or")
        {
            OrRessourceDeck = Card(_ressource["id"], _ressource["titre"], _ressource["desc"], "epique", ressource);
        }
    }


    return 0;
}

int Decks::fillBonusDecksFromJson()
{
    // Ouverture du fichier
    std::ifstream file("bonus.json");

    // On verif si le fichier a été ouvert correctement
    if (!file.is_open())
    {
        std::cerr << "Erreur lors de l'ouverture du fichier !" << std::endl;
        // On retourne -1 en cas d'erreur
        return -1;
    }

    // Pour parser le fichier JSON
    nlohmann::json j;
    file >> j;

    // Afficher le contenu complet du fichier JSON
    std::cout << "Contenu complet du fichier JSON :" << std::endl;
    std::cout << j.dump(4) << std::endl; // dump(4) permet d'afficher le JSON avec une indentation pour la lisibilité // doc officielle github

    // On accede au json et parcourt les bonus
    for (const auto &_bonus : j["bonus"]["commun"])
    {
        // 15 cartes de chaques pour avoir 45 cartes
        for (int i = 0; i < 15; i++)
        {
            // Création des cartes communes
            Card _card = Card(_bonus["id"], _bonus["titre"], _bonus["desc"], "commun", bonus);
            BonusDeck.push_back(_card);
        }
    }
    for (const auto &_bonus : j["bonus"]["rare"])
    {
        // 5 cartes de chaques pour avoir 20 cartes
        for (int i = 0; i < 5; i++)
        {
            // Création des cartes rare
            Card _card = Card(_bonus["id"], _bonus["titre"], _bonus["desc"], "rare", bonus);
            BonusDeck.push_back(_card);
        }
    }
    for (const auto &_bonus : j["bonus"]["épique"])
    {
        // 3 cartes de chaques pour avoir 15 cartes
        for (int i = 0; i < 3; i++)
        {
            // Création des cartes rare
            Card _card = Card(_bonus["id"], _bonus["titre"], _bonus["desc"], "épique", bonus);
            BonusDeck.push_back(_card);
        }
    }

    return 0;
}

std::vector<Card> Decks::getBonusDeck() const
{
    return BonusDeck;
}

void Decks::shuffleDecks()
{
    // On mélange les decks
    std::random_shuffle(BonusDeck.begin(), BonusDeck.end());
}

Card Decks::drawCardFromBonusDeck()
{
    // On pioche une carte
    Card _card = BonusDeck.back();
    // On retire la carte du deck
    BonusDeck.pop_back();
    // On retourne la carte
    return _card;
}

Card Decks::drawCardFromRessourceDeck(Ressource _ressource)
{
    switch (_ressource)
    {
    case Acier:
        return AcierRessourceDeck;

    case Bois:
        return BoisRessourceDeck;

    case Sable:
        return SableRessourceDeck;

    case Ble:
        return BleRessourceDeck;

    case Nourriture:
        return NourritureRessourceDeck;

    case Pierre:
        return PierreRessourceDeck;

    case Or:
        return OrRessourceDeck;

    case Argent:
        return ArgentRessourceDeck;

    default:
        break;
    }
}

void Decks::addCardToBonusDeck(Card _card)
{
    BonusDeck.push_back(_card);
}