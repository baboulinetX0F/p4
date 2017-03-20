#pragma once
#include "Button.h"
#include "GameManager.h"

#include <vector>

static const int CASE_DEFAULT_SIZE = 50;

// Classe speciale pour le jeu permettant d'afficher la grille de jeu
// en passant le GameManager en paramètre pour le constructeur.
class PGrid : public UIElement
{
private:
        // Classe discrete uniquement utilisé par la grille represent un élement de celle-ci
        class Element : public Button
        {
        public:
                Element(PGrid* grid);
                ~Element();

                void SetGridPos(int x, int y);
                void SetState(CASE_STATE state);

                // Fonctions hérités de Button
                void Draw(Renderer* renderer);
                void HandleEvents(SDL_Event e);

                int GetGridX() const;
                int GetGridY() const;
        private:
                PGrid* m_parentGrid;
                int m_gridX, m_gridY;

                CASE_STATE m_state = CASE_STATE::EMPTY;
        };
public:
        PGrid(GameManager* gameManager);
	~PGrid();

	void Draw(Renderer* renderer);
	void HandleEvents(SDL_Event e);

	void SetPos(int x, int y);        
    void UpdateGrid();

    void OnGridElemClicked(Element* e);

private:
	std::vector<Element> m_gridElements;
        GameManager* m_gameManager = nullptr;

	void InitGrid();
};

