#pragma once
#include "Button.h"
#include "GameManager.h"

#include <vector>

static const int CASE_SIZE_DEFAULT = 100;

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

                void OnClick();
        };
public:
    PGrid(GameManager* gameManager);
    ~PGrid();

    // Fonctions hérités de UIElement
    void Draw(Renderer* renderer);
    void HandleEvents(SDL_Event e);

    // Remplace les fonctions UIButton de base
    void SetPos(int x, int y);
    void SetSize(int x, int y);

    // Mets a jour les elements de grille
    void UpdateGrid();

    void OnGridElemClicked(Element* e);

private:
    std::vector<Element> m_gridElements;
    GameManager* m_gameManager = nullptr;

	void InitGrid();

    // Test un element de la colonne donnée est traversé par le curseur
    bool IsColumnHovered(int column);
};

