# Ressource-Game
Ce jeu est un jeu de stratégie en C++ 

# Synopsis :
Un jeu ressemblant à Catane, vous avez la possibilité de construire des villages et des villes grâce à des ressources, l’emplacement de vos villages et villes déterminera les ressources que vous pourrez récupérer. Il s’agira des ressources environnant votre village ou ville. Les villes permettront de doubler les ressources récupérer. Pour savoir quelles ressources seront distribuées, il y aura un lancement de dés aléatoires et une disposition aléatoire des ressources. Voici la liste des différentes ressources qui permettront la construction des villages et villes :

-	Acier
-	Bois
-	Sable
-	Pierre
-	Or
-	Blé
-	Argent
-	Nourriture
  
La disposition des ressources dépendra de leurs raretés et de leurs nombres. En effet le jeu comportera 44 cases :

-	Acier (5 cases – classe : commun)
-	Bois (10 cases – classe : commun)
-	Sable (7 cases – classe : commun)
-	Pierre (4 cases – classe : rare)
-	Or (1 case – classe : épique)
-	Blé (7 cases – classe : commun)
-	Argent (2 cases – classe : épique)
-	Nourriture (8 cases – classe : commun)
  
Chaque ressource permettra d’avancer d’une manière ou d’une autre dans le jeu, les ressources communes permettront d’avancer plus vite dans la construction des villages et villes tandis que les ressources rares et épique permettront d’obtenir des bonus qui pourront vous être utile. Le but du jeu étant d’arriver à 20 points. Chaque ville construite rapporte 2 points et donne l’accès au double des ressources et chaque village construit rapporte 1 point et donne l’accès aux ressources adjacentes et à la case. Il y a aussi la possibilité de tirer des cartes bonus (classer en 3 catégories : commun – rare – épique). Voici la liste des matériaux nécessaire à la construction de chacun de ces cartes ou villages ou villes :

-	Village : 4 bois (pour les fondations) – 2 Sable (Pour les vitres) – 2 Blé (Pour la toiture) – 1 Nourriture (Pour les habitants)
-	Ville : 3 Acier (pour les fondations) – 3 Sable (Pour les vitres) – 2 Pierre (Pour les routes) – 5 Nourriture (pour les habitants) – 6 bois (Pour les poutres et fondations)
-	Carte bonus commune : 2 Acier – 5 Bois – 2 Sable – 1 Pierre – 3 Nourriture
-	Carte bonus rare : 4 Acier – 5 Bois – 3 Pierre – 4 Nourriture – 4 Blé – 5 Sable
-	Carte bonus épique : 1 Or – 2 Argent – 5 Bois – 5 Acier – 5 Nourriture – 4 Blé
  
Les joueurs auront la possibilité de faire des échanges entre eux et avec le commerce mondial : 4 même ressources contre 1.

## Liste des cartes par catégories : 

### Carte bonus commune ( 45 cartes ) 
-	Voler 1 carte à 1 joueur
-	Doubler les ressources obtenu pendant 1 tour ( à dire avant le lancement du tour )
-	Bloquer 1 case ressource pendant 2 tours (personne ne pourra obtenir la ressource même vous)
### Carte bonus rare ( 20 cartes )
-	Voler 1 carte à chaque joueur
-	Doubler les ressources obtenu pendant 3 tours ( à dire avant le lancement du tour )
-	Bloquer 1 case ressource pendant 5 tours
-	Gagner 1 point (carte à conserver jusqu’à la fin)
### Carte bonus épique (15 cartes )
-	Demander à tous les joueurs de vous donner toutes leurs carte d’une ressource de votre choix
-	Détruisez un village adverse
-	Assiégez une ville adverse (votre adversaire ne pourra pas utiliser sa ville pendant 4 tours)
-	Gagner 3 points
-	Annihiler une ressource pour le reste de la partie (la case ne sera plus utilisable de la partie que ce soit pour récupérer la ressource ou construire une ville, ne peut pas être utiliser sur une case comportant un village ou une ville)

Nombres de joueurs : 2 – 4 joueurs

## Début de la partie :
-	Chaque joueur reçoit 2 villages à placer sur le plateau l’ordre de jeu est déterminé aléatoirement. Une fois les villages placer, chaque joueur reçoit une ressource de chaque case adjacente au premier village placer.
  
## Déroulé d’un tour :
-	L’ordre de jeu suit l’ordre de jeu déterminé au début de la partie, au moment de jouer, le joueur peut en 1er utiliser une carte bonus de son deck s’il en a, puis lancer les dés : chaque joueur ayant une ressource adjacente à un village ou une ville comportant le numéro tiré par les dés reçoit les ressources indiquées sur les cases (1 pour les villages et 2 pour les villes). Puis une fois les ressources obtenues ou non par le joueur, il a la possibilité de construire au choix : un ou plusieurs villages, une ou plusieurs villes, une ou plusieurs carte bonus de son choix. Au préalable et uniquement pendant son tour, le joueur a la possibilité de proposer des échanges aux autres joueurs et/ou de faire des échanges avec le commerce mondial.

## Nos classes

Voici les différentes classes que nous allons utiliser :
-	Classe Game :
Gestion de la partie – Initialiseur du plateau
-	Classe Plateau
Initialiser le plateau et contenir les cases
-	Classe Case
Contient toutes les infos d’une case
-	Classe Joueur
Toutes les infos du joueur : main, bonus, id …
