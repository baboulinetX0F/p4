#pragma once



// Etat d'une case de la grille de jeu
enum CASE_STATE
{
	EMPTY,
	RED,
	YELLOW
};


// Variable par defaut de la grille de jeu
static const unsigned short int NUM_COL = 7;
static const unsigned short int NUM_LINES = 6;

// Couleur a definir en fonction du choix du joueur
static const CASE_STATE COUL_JOUEUR = YELLOW;
static const CASE_STATE COUL_IA = RED;

/* Valeurs des séries */
static const short int PTS_VICTOIRE = 100;
static const short int PTS_SERIE_TROIS = 10;
static const short int PTS_SERIE_DEUX = 1;

static const short int DIFFICULTE_FACILE = 2;
static const short int DIFFICULTE_MOYEN = 3;
static const short int DIFFICULTE_DIFFICILE = 4;

/* GameManager : Gère la logique du jeu */
class GameManager
{
public:
	GameManager();
	~GameManager();
	
	bool m_playerTurn = true;

	void Update();	

	void Jouer(CASE_STATE color, unsigned short int column);
	

	/* m_grid : Grille de jeu */
	CASE_STATE m_grid[NUM_COL][NUM_LINES];
	CASE_STATE cpy_grid[NUM_COL][NUM_LINES];
	
	/* Initialise la grille de jeu */
	void InitGrid();

	/* Retourne le nombre de pièce que contient la colonne passé en paramètre */
	unsigned short int GetColHeight(unsigned short int column);

	CASE_STATE GetGridValAt(int x, int y);

	// Gére le tour de l'IA 
	void IA(unsigned short int difficulty);

private:
	short int m_gameState = 0;

	int m_difficulte = DIFFICULTE_FACILE;
	
	unsigned short int CompareGrid();

	short int test();

	/* traite l'etat de la grille en cas de fin de partie victoire / defaite / egalite */
	short int FinPartie(unsigned short int etat);

	/* Verifie si la partie est terminé ou pas en fonction du dernier pion posé
	Renvoie 0 si la partie continue, 1 si IA gagne, 2 si Joueur gagne, 3 si partie s'arrete */
	unsigned short int CheckEtat(short int serieDeQuatre, unsigned short int column);

	// remplie le tableau de résultat de la fonction Eval
	void FillTabEval(short int *tab, unsigned short int typeSerie);

	// Insert une piece de couleur (color) a la colonne (column)
	void PushPiece(CASE_STATE color, unsigned short int column);

	// Retire une piece de la colonne (column)
	void PullPiece(unsigned short int column);

	unsigned short int Horizontale(short int x, short int y, CASE_STATE c);
	unsigned short int Verticale(short int x, short int y, CASE_STATE c);
	unsigned short int DiagonaleD(short int x, short int y, CASE_STATE c);
	unsigned short int DiagonaleM(short int x, short int y, CASE_STATE c);

	/* Evalue un pion, calcul sont poids et s'il permet un alignement de 4(victoire)
	Renvoie un tableau d'entier de taille 2 dans la premiére case le poids des
	séries de 2 et 3 et dans la 2éme si ya une série de 4 de formé */
	short int* Eval(short int column);

	// Parcour de l'arbre, recherche du Min
	short int Min(unsigned short int difficulty, unsigned short int lastPion);

	// Parcour de l'arbre, recherche du Max
	short int Max(unsigned short int difficulty, unsigned short int lastPion);
};

