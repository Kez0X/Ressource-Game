#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>
#include <vector>
#include "../Utils/json.hpp"
#include "Decks.hpp"
#include "Card.hpp"
#include "Cell.hpp"

using json = nlohmann::json;

int randomInt3()
{
    return std::rand();
}

Decks::Decks()
{
    // Création des decks de ressources et de bonus
    fillRessourcesDecksFromJson();
    fillBonusDecksFromJson();
};

int Decks::fillRessourcesDecksFromJson()
{
    // Ouverture du fichier
    std::ifstream file("../Utils/ressources.json");

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

    // On accede au json et parcourt les ressources
    for (const auto &_ressource : j["ressources"]["commun"])
    {
        if (_ressource["id"] == "Acier")
        {
            AcierRessourceDeck.setId(_ressource["id"]);
            AcierRessourceDeck.setTitre(_ressource["titre"]);
            AcierRessourceDeck.setDesc(_ressource["desc"]);
            AcierRessourceDeck.setRarete("commun");
            AcierRessourceDeck.setType(ressource);
        }

        else if (_ressource["id"] == "Bois")
        {
            BoisRessourceDeck.setId(_ressource["id"]);
            BoisRessourceDeck.setTitre(_ressource["titre"]);
            BoisRessourceDeck.setDesc(_ressource["desc"]);
            BoisRessourceDeck.setRarete("commun");
            BoisRessourceDeck.setType(ressource);
        }

        else if (_ressource["id"] == "Sable")
        {
            SableRessourceDeck.setId(_ressource["id"]);
            SableRessourceDeck.setTitre(_ressource["titre"]);
            SableRessourceDeck.setDesc(_ressource["desc"]);
            SableRessourceDeck.setRarete("commun");
            SableRessourceDeck.setType(ressource);
        }

        else if (_ressource["id"] == "Blé")
        {
            BleRessourceDeck.setId(_ressource["id"]);
            BleRessourceDeck.setTitre(_ressource["titre"]);
            BleRessourceDeck.setDesc(_ressource["desc"]);
            BleRessourceDeck.setRarete("commun");
            BleRessourceDeck.setType(ressource);
        }

        else if (_ressource["id"] == "Nourriture")
        {
            NourritureRessourceDeck.setId(_ressource["id"]);
            NourritureRessourceDeck.setTitre(_ressource["titre"]);
            NourritureRessourceDeck.setDesc(_ressource["desc"]);
            NourritureRessourceDeck.setRarete("commun");
            NourritureRessourceDeck.setType(ressource);
        }
    }
    for (const auto &_ressource : j["ressources"]["rare"])
    {
        if (_ressource["id"] == "Pierre")
        {
            PierreRessourceDeck.setId(_ressource["id"]);
            PierreRessourceDeck.setTitre(_ressource["titre"]);
            PierreRessourceDeck.setDesc(_ressource["desc"]);
            PierreRessourceDeck.setRarete("commun");
            PierreRessourceDeck.setType(ressource);
        }
    }
    for (const auto &_ressource : j["ressources"]["épique"])
    {
        if (_ressource["id"] == "Or")
        {
            OrRessourceDeck.setId(_ressource["id"]);
            OrRessourceDeck.setTitre(_ressource["titre"]);
            OrRessourceDeck.setDesc(_ressource["desc"]);
            OrRessourceDeck.setRarete("commun");
            OrRessourceDeck.setType(ressource);
        }
        else if (_ressource["id"] == "Argent")
        {
            ArgentRessourceDeck.setId(_ressource["id"]);
            ArgentRessourceDeck.setTitre(_ressource["titre"]);
            ArgentRessourceDeck.setDesc(_ressource["desc"]);
            ArgentRessourceDeck.setRarete("commun");
            ArgentRessourceDeck.setType(ressource);
        }
    }

    return 0;
}

int Decks::fillBonusDecksFromJson()
{
    // Ouverture du fichier
    std::ifstream file("../Utils/bonus.json");

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
    for (const auto &_bonus : j["bonus"]["epique"])
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

Card Decks::drawCardFromBonusDeck(std::string rarity)
{
    // On pioche une carte
    Card _card;
    do
    {
        _card = BonusDeck[rand() % BonusDeck.size()];
    } while (_card.getRarete() != rarity);

    // On retire la carte du deck
    bool erased = false;
    for (int i = 0; i < BonusDeck.size(); i++)
    {
        if (BonusDeck[i].getTitre() == _card.getTitre())
        {
            if (!erased)
            {
                erased = true;
            }
        }
    }

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
        std::vector<Card> _ressourceDecksAvailable = {AcierRessourceDeck, BoisRessourceDeck, SableRessourceDeck, BleRessourceDeck, NourritureRessourceDeck, PierreRessourceDeck, OrRessourceDeck, ArgentRessourceDeck};
        std::string _selected = "Default";
        int random = 0;
        while (_selected == "Default")
        {
            random = randomInt3() % _ressourceDecksAvailable.size();
            _selected = _ressourceDecksAvailable[random].getTitre();
        }
        return _ressourceDecksAvailable[random];
    }
}

void Decks::addCardToBonusDeck(Card _card)
{
    BonusDeck.push_back(_card);
}