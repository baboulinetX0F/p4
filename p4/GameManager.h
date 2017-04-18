#pragma once


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

/* Valeurs des s�ries, pond�ration */
static const short int PTS_VICTOIRE = 1000;
static const short int PTS_SERIE_TROIS = 10;
static const short int PTS_SERIE_DEUX = 1;

// Niveaux de difficult�s
static const short int DIFFICULTE_FACILE = 2;
static const short int DIFFICULTE_MOYEN = 4;
static const short int DIFFICULTE_DIFFICILE = 8;
static const short int DIFFICULTE_HARDCORE = 10; //utilisation de paternes + auto apprendage

/* GameManager : G�re la logique du jeu */
class GameManager {

public:

	// Retourne l'instance unique de GameManager
	static GameManager& Instance();
	
	// Bool�en pour savoir si c'est le tour du joueur (et g�rer le tour IA par cons�quent)
	bool m_playerTurn = true;

	short int suiteDeCoup[44];

	void FillSuiteDeCoup(short int col);

	void Sauvegarder();

	void Load();

	// En fonction de l'�tat du jeu fait jouer l'IA (si la partie continue)
	void Update();

	// Place le pion du joueur Si c'est son tour
	void Jouer(CASE_STATE color, short int column);

	// Retourne l'�tat actuel de la partie
	short int GetGameState() const;
	
	// Redemarre une nouvelle partie
	void Restart();

	// Renvoie l'etat dune case
	CASE_STATE GetGridValAt(short int x, short int y);

	/* Retourne le nombre de pi�ce que contient la colonne pass� en param�tre */
	short int GetColHeight(short int column);

	// G�re le tour de l'IA 
	//void IA(short int difficulty);

	// G�re le tour de l'IA version Coupe Alpha/Beta
	void IaAB(short int profondeur);

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
	/* cpy_grid : copie de la Grille de jeu qui permet de savoir quel pion vient d'�tre jou� */
	CASE_STATE cpy_grid[NUM_COL][NUM_LINES];

	// Variable d'�tat du jeu : s'arrete ou continue
	short int m_gameState = 0;

	// Variable de difficult� de l'IA (� def par les choix joueur)
	int m_difficulte = 2;

	/* Initialise la grille de jeu */
	void InitGrid();

	// Vide les grilles (temporaire et principale)
	void ClearGrid();

	// Compare la grille de jeu et la copie et renvoie la premi�re colonne diff�rente trouv�
	short int CompareGrid();

	// V�rifie � chaque fois que le joueur ou l'IA joue (en dehors de l'ARBRE)
	// si l'un des 2 � gagn�, pour arr�ter la partie
	short int CheckWin();

	// En cas de fin de partie dans l'ARBRE renvoie les pts appropri�s
	short int FinPartie(short int etat);

	/* Verifie si la partie est termin� ou pas en fonction du dernier pion pos�
	Renvoie 0 si la partie continue, 1 si IA gagne, 2 si Joueur gagne, 3 si partie s'arrete */
	short int CheckEtat(short int serieDeQuatre, short int column);

	// Remplie le tableau de r�sultat de la fonction Eval
	void FillTabEval(short int *tab, short int typeSerie);

	// Insert une piece de couleur (color) � la colonne (column)
	bool PushPiece(CASE_STATE color, short int column);

	// Retire une piece de la colonne (column)
	void PullPiece(short int column);

	// Pour les 4 fonctions suivante les cas particulier de chaines mortes et de fausses chaines sont g�r�s
	// Compte le nombre de pion de couleur c align� horizontalement
	short int Horizontale(short int x, short int y, CASE_STATE c);
	// Compte le nombre de pion de couleur c align� verticalement
	short int Verticale(short int x, short int y, CASE_STATE c);
	// Compte le nombre de pion de couleur c align�  en diagonale d�scendante (haut gauche vers bas droit)
	short int DiagonaleD(short int x, short int y, CASE_STATE c);
	// Compte le nombre de pion de couleur c align�  en diagonale montante (bas gauche vers haut droit)
	short int DiagonaleM(short int x, short int y, CASE_STATE c);

	/* Evalue un pion, calcul sont poids et s'il permet un alignement de 4(victoire)
	Renvoie un tableau d'entier de taille 2 dans la premi�re case le poids des
	s�ries de 2 et 3 et dans la 2�me si ya une s�rie de 4 de form� */
	short int* Eval(short int column);

	// Parcours de l'arbre, recherche du Min
	//short int Min(short int difficulty, short int lastPion);

	// Parcours de l'arbre, recherche du Max
	//short int Max(short int difficulty, short int lastPion);


	short int MinAB(short int profondeur, short int lastPion, short int alpha, short int beta);

	short int MaxAB(short int profondeur, short int lastPion, short int alpha, short int beta);
};

