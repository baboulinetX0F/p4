#include "UIElement.h"
#include "PGridElem.h"

class PGrid : public UIElement
{
public:
	PGrid();
	~PGrid();

	void Draw(Renderer* renderer);
	void HandleEvents(SDL_Event e);

private:
	//std::vector<PGridElem> m_gridElem;
};
