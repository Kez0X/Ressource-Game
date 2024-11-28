#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>

class Hexagone {
public:
    float x, y;  // Position du centre de l'hexagone
    float rayon; // Rayon des hexagones (distance du centre à un coin)

    Hexagone(float x, float y, float rayon) : x(x), y(y), rayon(rayon) {}

    // Fonction pour obtenir un polygone hexagonal
    sf::ConvexShape getHexagonShape() {
        sf::ConvexShape hexagon(6);  // Hexagone a 6 côtés
        for (int i = 0; i < 6; i++) {
            float angle = i * 2 * M_PI / 6;
            hexagon.setPoint(i, sf::Vector2f(
                x + rayon * cos(angle),
                y + rayon * sin(angle)
            ));
        }
        return hexagon;
    }
};

class PlateauHexagonal {
private:
    std::vector<Hexagone> hexagones; // Liste des hexagones
    float rayon; // Rayon des hexagones
    int largeur; // Largeur du plateau (en termes de nombre de hexagones)
    int hauteur; // Hauteur du plateau (en termes de nombre de hexagones)

public:
    PlateauHexagonal(int largeur, int hauteur, float rayon) : largeur(largeur), hauteur(hauteur), rayon(rayon) {
        // Générer le plateau hexagonal
        for (int i = 0; i < hauteur; ++i) {
            for (int j = 0; j < largeur; ++j) {
                // Décalage horizontal pour chaque hexagone
                float offsetX = j * rayon * 1.5f;
                // Décalage vertical pour chaque hexagone
                float offsetY = i * rayon * sqrt(3);
                
                // Décalage supplémentaire sur les lignes impaires (déplacement de la colonne)
                if (j % 2 != 0) {
                    offsetY += rayon * sqrt(3) / 2;
                }

                // Ajouter un hexagone à la liste
                hexagones.push_back(Hexagone(offsetX, offsetY, rayon));
            }
        }
    }

    // Fonction pour dessiner le plateau
    void afficher(sf::RenderWindow& window) {
        for (auto& hex : hexagones) {
            sf::ConvexShape hexagonShape = hex.getHexagonShape();
            hexagonShape.setFillColor(sf::Color::Green);  // Par défaut, colorier en vert
            hexagonShape.setOutlineThickness(2);
            hexagonShape.setOutlineColor(sf::Color::Black);
            window.draw(hexagonShape);
        }
    }
};

int main() {
    // Création de la fenêtre
    sf::RenderWindow window(sf::VideoMode(800, 600), "Plateau Hexagonal");

    // Création du plateau hexagonal de 44 cases
    PlateauHexagonal plateau(8, 6, 30); // 8 colonnes et 6 lignes de hexagones

    // Boucle principale
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Effacer l'écran et redessiner
        window.clear(sf::Color::White);

        // Affichage du plateau
        plateau.afficher(window);

        // Afficher le contenu de la fenêtre
        window.display();
    }

    return 0;
}
