#pragma once

// Etat d'une case de la grille de jeu
enum CASE_STATE
{
	EMPTY,
	RED,
	YELLOW
};

// Variable par defaut de la grille de jeu
static const int NUM_COL = 7;
static const int NUM_LINES = 6;


/* GameManager : Gère la logique du jeu */
class GameManager
{
public:
	GameManager();
	~GameManager();

	void Update();

	// Insert une piece de couleur (color) a la colonne (column)
	void PushPiece(CASE_STATE color, int column);

    CASE_STATE GetGridValAt(int x, int y);

    bool m_playerTurn = true;

private:
	/* m_grid : Grille de jeu */
    CASE_STATE m_grid[NUM_COL][NUM_LINES];


	/* Initialise la grille de jeu */
	void InitGrid();

	/* Retourne le nombre de pièce que contient la colonne passé en paramètre */
	unsigned int GetColHeight(int column);

	/* Verifie si la partie est terminé */
	void CheckWin();
};

