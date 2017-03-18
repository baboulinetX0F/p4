#include "GameManager.h"

#include "Button.h"


class PGridElem : public Button
{
public:
	PGridElem();
	~PGridElem();

	void Draw(Renderer* renderer);
	
private:	
	CASE_STATE m_state;

	SDL_Texture* m_emptyTexture = nullptr;
	SDL_Texture* m_redTexture = nullptr;
	SDL_Texture* m_yellowTexture = nullptr;
};
