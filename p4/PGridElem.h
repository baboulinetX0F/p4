#include "Button.h"

class PGridElem : public Button
{
public:
	PGridElem();
	~PGridElem();
	
private:
	SDL_Texture* m_texture;
};
