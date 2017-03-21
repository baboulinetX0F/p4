#include "GameManager.h"
#include <ctime>
#include <cstdlib>
#include <iostream>



GameManager::GameManager() {
	InitGrid();
}

GameManager::~GameManager()
{
}

void GameManager::Update()
{
	if (m_gameState == 0) {
		if (!m_playerTurn)
			IA(m_difficulte);
	}
}

unsigned short int GameManager::CompareGrid() {
	for (int x = 0; x < NUM_COL; x++) {
		for (int y = 0; y < NUM_LINES; y++) {
			if (m_grid[x][y] != cpy_grid[x][y]) {
				cpy_grid[x][y] = m_grid[x][y];
				return x;
			}
		}
	}
	return 0;
}

short int GameManager::test()
{
	short int colDiff = CompareGrid(), etat;
	short int *tabEval = Eval(colDiff);
	short int serieDeQuatre = tabEval[1];
	delete[] tabEval;
	etat = CheckEtat(serieDeQuatre, colDiff);
	return etat;
}

void GameManager::PushPiece(CASE_STATE color, unsigned short int column)
{
	int line = GetColHeight(column);

	if (line < NUM_LINES)
	{
		m_grid[column][line] = color;
	}
}

void GameManager::Jouer(CASE_STATE color, unsigned short int column)
{
	if (m_gameState == 0) {
		PushPiece(color, column);
		m_playerTurn = !m_playerTurn;
		m_gameState = test();
	}
}

void GameManager::PullPiece(unsigned short int column)
{
	int line = GetColHeight(column) - 1;
	m_grid[column][line] = CASE_STATE::EMPTY;
}

void GameManager::InitGrid()
{
	for (unsigned short int x = 0; x < NUM_COL; x++)
	{
		for (unsigned short int y = 0; y < NUM_LINES; y++)
		{
			m_grid[x][y] = CASE_STATE::EMPTY;
			cpy_grid[x][y] = CASE_STATE::EMPTY;
		}
	}
}

CASE_STATE GameManager::GetGridValAt(int x, int y)
{
	return m_grid[x][y];
}

unsigned short int GameManager::GetColHeight(unsigned short int column)
{
	int count = 0;
	for (int y = 0; y < NUM_LINES; y++)
	{
		if (m_grid[column][y] != CASE_STATE::EMPTY)
			count++;
	}
	return count;
}

short int GameManager::FinPartie(unsigned short int etat) {
	int nbPion(0);
	for (int i = 0; i < NUM_COL; i++) {
		nbPion += GetColHeight(i);
	}
	switch (etat) {
	case 1: return PTS_VICTOIRE - nbPion; break; // Victoire IA
	case 2: return (-1 * PTS_VICTOIRE) + nbPion; break; // Victoire joueur
	default: return 0; break; // Grille pleine sans gagnant
	}
}

unsigned short int GameManager::CheckEtat(short int serieDeQuatre, unsigned short int column) {
	CASE_STATE couleur = m_grid[column][GetColHeight(column) - 1];
	if (serieDeQuatre && (couleur == COUL_IA))
		return 1; // IA gagne 
	else if (serieDeQuatre && (couleur == COUL_JOUEUR))
		return 2; // Joueur gagne 
	else {
		for (int i = 0; i < NUM_COL; i++) {
			if (GetColHeight(i) < NUM_LINES)
				return 0; // Reste de la place | Jeu continue
		}
		return 3; // Grille pleine | Jeu s'arrete
	}
}

void GameManager::FillTabEval(short int* tab, unsigned short int typeSerie) {
	switch (typeSerie) {
	case 1: /* Rien */ break;
	case 2: tab[0] += PTS_SERIE_DEUX; break;
	case 3: tab[0] += PTS_SERIE_TROIS; break;
	default:tab[1] += 1; break;
	}
}

unsigned short int GameManager::Horizontale(short int x, short int y, CASE_STATE c) {
	short int  i(1), j(1);
	unsigned short int size(1);

	while ((x - i >= 0) && (m_grid[x - i][y] == c)) { size++; i++; } //vers la gauche 
	while ((x + j < 7) && (m_grid[x + j][y] == c)) { size++; j++; } //vers la droite

	if (size == 2 || size == 3) { // chaines mortes
		if (!(x - i >= 0) && (m_grid[x + j][y] != CASE_STATE::EMPTY)) return 1; // Bord Gauche et 1er pion droit rouge
		else if (!(x + j < 7) && (m_grid[x - i][y] != CASE_STATE::EMPTY)) return 1;   // Bord Droit et 1er pion gauche rouge 
		else if ((x - i >= 0) && (x + j < 7) && (m_grid[x + j][y] != CASE_STATE::EMPTY) && (m_grid[x - i][y] != CASE_STATE::EMPTY)) return 1; // 1er pion gauche et droit rouge
	}
	if (size == 2 || size == 1) { // Fausses series de 3
		if ((x - i >= 0) && (x - (i + 1) >= 0) && (m_grid[x - i][y] == CASE_STATE::EMPTY) && (m_grid[x - (i + 1)][y] == c)) size++;
		else if ((x + j < 7) && (x + (j + 1) < 7) && (m_grid[x + j][y] == CASE_STATE::EMPTY) && (m_grid[x + (j + 1)][y] == c)) size++;
	}

	return size;
}

unsigned short int GameManager::Verticale(short int x, short int y, CASE_STATE c) {
	short int i(1);
	unsigned short int size(1);

	while ((y - i >= 0) && (m_grid[x][y - i] == c)) { size++; i++; } //vers le bas  
																	 // chaines mortes
	if ((size == 2 || size == 3) && (y + 1 >= 6)) return 1; // Bord Haut
	return size;
}

unsigned short int GameManager::DiagonaleD(short int x, short int y, CASE_STATE c) {
	short int  i(1), j(1);
	unsigned short int size(1);


	while ((x - i >= 0) && (y + i < 6) && (m_grid[x - i][y + i] == c)) { size++; i++; } //vers le Haut Gauche 
	while ((x + j < 7) && (y - j >= 0) && (m_grid[x + j][y - j] == c)) { size++; j++; } //vers le Bas Droit 

	if (size == 2 || size == 3) { // chaines mortes
		if (!(x - i >= 0) && !(y + i < 6) && (m_grid[x + j][y - j] != CASE_STATE::EMPTY)) return 1;		 //Coin Haut Gauche et et 1er pion Bas Droit rouge
		else if (!(x + j < 7) && !(y - j >= 0) && (m_grid[x - i][y + i] != CASE_STATE::EMPTY)) return 1;		 //Coin Bas Droit et 1er pion Haut gauche rouge
		else if ((x - i >= 0) && !(y + i < 6) && (m_grid[x + j][y - j] != CASE_STATE::EMPTY)) return 1;		 //Bord Haut 1er pion Bas Droit rouge
		else if (!(x - i >= 0) && (y + i < 6) && (m_grid[x + j][y - j] != CASE_STATE::EMPTY)) return 1;		 //Bord Gauche 1er pion Bas Droit rouge
		else if ((x + j < 7) && !(y - j >= 0) && (m_grid[x - i][y + i] != CASE_STATE::EMPTY)) return 1;		 //Bord Bas 1er pion Haut Gauche rouge
		else if (!(x + j < 7) && (y - j >= 0) && (m_grid[x - i][y + i] != CASE_STATE::EMPTY)) return 1;		 //Bord Droit 1er pion Haut Gauche rouge
		else if (!(x - i >= 0) && !(y - j >= 0)) return 1;													 //Bord Gauche Bord Bas
		else if (!(x + j < 7) && !(y + i < 6))  return 1;													 //Bord Droit Bord Haut
		else if ((x - i >= 0) && (y + i < 6) && (x + j < 7) && (y - j >= 0) && (m_grid[x - i][y + i] != CASE_STATE::EMPTY) && (m_grid[x + j][y - j] != CASE_STATE::EMPTY)) return 1; //1er pion Haut Gauche et Bas Droit rouge
	}
	if (size == 2 || size == 1) { // Fausses series de 3
		if ((x - i >= 0) && (y + i < 6) && (x - (i + 1) >= 0) && (y + (i + 1) < 6) && (m_grid[x - i][y + i] == CASE_STATE::EMPTY) && (m_grid[x - (i + 1)][y + (i + 1)] == c)) size++;
		else if ((x + j < 7) && (y - j >= 0) && (x + (j + 1) < 7) && (y - (j + 1) >= 0) && (m_grid[x + j][y - j] == CASE_STATE::EMPTY) && (m_grid[x + (j + 1)][y - (j + 1)] == c)) size++;
	}
	return size;
}

unsigned short int GameManager::DiagonaleM(short int x, short int y, CASE_STATE c) {
	short int  i(1), j(1);
	unsigned short int size(1);

	while ((x + i < 7) && (y + i < 6) && (m_grid[x + i][y + i] == c)) { size++; i++; } //vers le Haut Droit 
	while ((x - j >= 0) && (y - j >= 0) && (m_grid[x - j][y - j] == c)) { size++; j++; } //vers le Bas Gauche 

	if (size == 2 || size == 3) { // chaines mortes
		if (!(x + i < 7) && !(y + i < 6) && (m_grid[x - j][y - j] != CASE_STATE::EMPTY)) return 1;		 //Coin Haut Droit et et 1er pion Bas Gauche rouge			
		else if (!(x - j >= 0) && !(y - j >= 0) && (m_grid[x + i][y + i] != CASE_STATE::EMPTY)) return 1;		 //Coin Bas Gauche et 1er pion Haut Droit rouge		 
		else if ((x + i < 7) && !(y + i < 6) && (m_grid[x - j][y - j] != CASE_STATE::EMPTY)) return 1;		 //Bord Haut 1er pion Bas Gauche rouge					 
		else if (!(x + i < 7) && (y + i < 6) && (m_grid[x - j][y - j] != CASE_STATE::EMPTY)) return 1;		 //Bord Droit 1er pion Bas Gauche rouge					  
		else if ((x - j >= 0) && !(y - j >= 0) && (m_grid[x + i][y + i] != CASE_STATE::EMPTY)) return 1;		 //Bord Bas 1er pion Haut Droit rouge					 
		else if (!(x - j >= 0) && (y - j >= 0) && (m_grid[x + i][y + i] != CASE_STATE::EMPTY)) return 1;		 //Bord Gauche 1er pion Haut Droit rouge					
		else if (!(x - j >= 0) && !(y + i < 6)) return 1;														 //Bord Gauche Bord Haut
		else if (!(x + i < 7) && !(y - j >= 0)) return 1;														 //Bord Droit Bord Bas
		else if ((x + i < 7) && (y + i < 6) && (x - j >= 0) && (y - j >= 0) && (m_grid[x + i][y + i] != CASE_STATE::EMPTY) && (m_grid[x - j][y - j] != CASE_STATE::EMPTY)) return 1; //1er pion Haut Droit et Bas Gauche rouge

	}
	if (size == 2 || size == 1) { // Fausses series de 3
		if ((x + i < 7) && (y + i < 6) && (x + (i + 1) < 7) && (y + (i + 1) < 6) && (m_grid[x + i][y + i] == CASE_STATE::EMPTY) && (m_grid[x + (i + 1)][y + (i + 1)] == c)) size++;
		else if ((x - j >= 0) && (y - j >= 0) && (x - (j + 1) >= 0) && (y - (j + 1) >= 0) && (m_grid[x - j][y - j] == CASE_STATE::EMPTY) && (m_grid[x - (j + 1)][y - (j + 1)] == c)) size++;
	}
	return size;
}

short int* GameManager::Eval(short int column) {
	short int positifNegatif;
	short int *tabEval = new short int[2];
	tabEval[0] = 0; tabEval[1] = 0;
	short int line = GetColHeight(column) - 1;
	CASE_STATE couleur = m_grid[column][line];

	if (couleur == COUL_IA) positifNegatif = 1;
	else positifNegatif = -1;

	FillTabEval(&tabEval[0], Horizontale(column, line, couleur));
	FillTabEval(&tabEval[0], Verticale(column, line, couleur));
	FillTabEval(&tabEval[0], DiagonaleD(column, line, couleur));
	FillTabEval(&tabEval[0], DiagonaleM(column, line, couleur));

	tabEval[0] *= positifNegatif;

	return tabEval;
}

void GameManager::IA(unsigned short int profondeur)
{
	short int max(-1000), tmp, maxi;
	srand(time(NULL));
	for (unsigned short int i = 0; i < NUM_COL; i++)
	{
		if (GetColHeight(i) < NUM_LINES)
		{
			PushPiece(COUL_IA, i);
			tmp = Min(profondeur - 1, i);

			if ((tmp > max) || ((tmp == max) && (rand() % 2 == 0))) {
				max = tmp;
				maxi = i;
			}
			PullPiece(i);
		}
	}
	Jouer(COUL_IA, maxi);
}

short int GameManager::Min(unsigned short int profondeur, unsigned short int lastPion)
{
	short int *tabEval = Eval(lastPion);
	short int serieDeQuatre = tabEval[1];
	short int poids = tabEval[0];
	delete[] tabEval;
	unsigned short int etat = CheckEtat(serieDeQuatre, lastPion);
	if (etat != 0) {
		return FinPartie(etat);
	}
	else if (profondeur == 0) {
		return poids;
	}
	else {
		int min(1000), tmp;
		for (int i = 0; i < NUM_COL; i++) {
			if (GetColHeight(i) < NUM_LINES) {
				PushPiece(COUL_JOUEUR, i);
				tmp = Max(profondeur - 1, i);
				if ((tmp < min) || ((tmp == min) && (rand() % 2 == 0)))
					min = tmp;
				PullPiece(i);
			}
		}
		return min + poids;
	}
}

short int GameManager::Max(unsigned short int profondeur, unsigned short int lastPion)
{
	short int *tabEval = Eval(lastPion);
	short int serieDeQuatre = tabEval[1];
	short int poids = tabEval[0];
	delete[] tabEval;
	unsigned short int etat = CheckEtat(serieDeQuatre, lastPion);
	if (etat != 0) {
		return FinPartie(etat);
	}
	else if (profondeur == 0) {
		return poids;
	}
	else {
		int max(-1000), tmp;
		for (int i = 0; i < NUM_COL; i++) {
			if (GetColHeight(i) < NUM_LINES) {
				PushPiece(COUL_IA, i);
				tmp = Min(profondeur - 1, i);
				if ((tmp > max) || ((tmp == max) && (rand() % 2 == 0)))
					max = tmp;
				PullPiece(i);
			}
		}
		return max + poids;
	}

}