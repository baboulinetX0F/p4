#pragma once
#include <string>

// Etat d'une case de la grille de jeu
enum CASE_STATE {
	EMPTY,
	RED,
	YELLOW
};

// Variable par defaut de la grille de jeu
static const short int NUM_COL = 7;
static const short int NUM_LINES = 6;

// Couleur a definir en fonction du choix du joueur
static const CASE_STATE COUL_JOUEUR = YELLOW;
static const CASE_STATE COUL_IA = RED;

/* Valeurs des séries, pondération */
static const short int PTS_VICTOIRE = 1000;
static const short int PTS_SERIE_TROIS = 10;
static const short int PTS_SERIE_DEUX = 1;

// Niveaux de difficultés
static const short int DIFFICULTE_FACILE = 6;
static const short int DIFFICULTE_MOYEN = 8;
static const short int DIFFICULTE_DIFFICILE = 10; //utilisation de paternes + auto apprendage
static const short int DIFFICULTE_HARDCORE = 12; //utilisation de paternes + auto apprendage

/* GameManager : Gère la logique du jeu */
class GameManager {

public:

	std::string MakeString();

	void PutInFile(short int col);

	short int IsInFile();

	// Retourne l'instance unique de GameManager
	static GameManager& Instance();
	
	// Booléen pour savoir si c'est le tour du joueur (et gérer le tour IA par conséquent)
	bool m_playerTurn = true;

	// Tab qui sauvegarde chaque coup joué (les num de col) dans la partie
	short int suiteDeCoup[44];

	// remplie le tab suiteDeCoup
	void FillSuiteDeCoup(short int col);

	// Sauvegarde une partie
	void Sauvegarder();

	//Charge une parite sauvegardé
	void Load();

	// En fonction de l'état du jeu fait jouer l'IA (si la partie continue)
	void Update();

	// Place le pion du joueur Si c'est son tour
	void Jouer(CASE_STATE color, short int column);

	// Retourne l'état actuel de la partie
	short int GetGameState() const;
	
	// Redemarre une nouvelle partie
	void Restart();

	// Renvoie l'etat dune case
	CASE_STATE GetGridValAt(short int x, short int y);

	/* Retourne le nombre de pièce que contient la colonne passé en paramètre */
	short int GetColHeight(short int column);

	// Gére le tour de l'IA 
	//void IA(short int difficulty);

	// Gère le tour de l'IA version Coupe Alpha/Beta
	void IaAB(short int profondeur);
	void IaABPattern(short int profondeur);


	// Change la difficulté
	void DifficulteUn();
	void DifficulteDeux();
	void DifficulteTrois();
	void DifficulteQuatre();

private:
	// Differents operations sur reference
	GameManager& operator= (const GameManager&) {}
	GameManager(const GameManager&) {}

	// Instance du singleton
	static GameManager m_instance;

	// Constructeur et Destructeur
	GameManager();
	~GameManager();

	/* m_grid : Grille de jeu */
	CASE_STATE m_grid[NUM_COL][NUM_LINES];
	/* cpy_grid : copie de la Grille de jeu qui permet de savoir quel pion vient d'être joué */
	CASE_STATE cpy_grid[NUM_COL][NUM_LINES];

	

	// Variable d'état du jeu : s'arrete ou continue
	short int m_gameState = 0;

	// Variable de difficulté de l'IA (à def par les choix joueur)
	int m_difficulte = 2;

	/* Initialise la grille de jeu */
	void InitGrid();

	// Compare la grille de jeu et la copie et renvoie la premiére colonne différente trouvé
	short int CompareGrid();

	// Vérifie à chaque fois que le joueur ou l'IA joue (en dehors de l'ARBRE)
	// si l'un des 2 à gagné, pour arréter la partie
	short int CheckWin();

	// En cas de fin de partie dans l'ARBRE renvoie les pts appropriés
	short int FinPartie(short int etat);

	/* Verifie si la partie est terminé ou pas en fonction du dernier pion posé
	Renvoie 0 si la partie continue, 1 si IA gagne, 2 si Joueur gagne, 3 si partie s'arrete */
	short int CheckEtat(short int serieDeQuatre, short int column);

	// Remplie le tableau de résultat de la fonction Eval
	void FillTabEval(short int *tab, short int typeSerie);

	// Insert une piece de couleur (color) à la colonne (column)
	bool PushPiece(CASE_STATE color, short int column);

	// Retire une piece de la colonne (column)
	void PullPiece(short int column);

	// Pour les 4 fonctions suivante les cas particulier de chaines mortes et de fausses chaines sont gérés
	// Compte le nombre de pion de couleur c aligné horizontalement
	short int Horizontale(short int x, short int y, CASE_STATE c);
	// Compte le nombre de pion de couleur c aligné verticalement
	short int Verticale(short int x, short int y, CASE_STATE c);
	// Compte le nombre de pion de couleur c aligné  en diagonale déscendante (haut gauche vers bas droit)
	short int DiagonaleD(short int x, short int y, CASE_STATE c);
	// Compte le nombre de pion de couleur c aligné  en diagonale montante (bas gauche vers haut droit)
	short int DiagonaleM(short int x, short int y, CASE_STATE c);

	/* Evalue un pion, calcul sont poids et s'il permet un alignement de 4(victoire)
	Renvoie un tableau d'entier de taille 2 dans la premiére case le poids des
	séries de 2 et 3 et dans la 2éme si ya une série de 4 de formé */
	short int* Eval(short int column);

	short int MinAB(short int profondeur, short int lastPion, short int alpha, short int beta);

	short int MaxAB(short int profondeur, short int lastPion, short int alpha, short int beta);

	// Parcours de l'arbre, recherche du Min
	//short int Min(short int difficulty, short int lastPion);

	// Parcours de l'arbre, recherche du Max
	//short int Max(short int difficulty, short int lastPion);

};

