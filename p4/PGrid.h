#include <vector>

#include "PGridElem.h"
#include "UIElement.h"

class PGrid : public UIElement
{
public:
	PGrid();
	~PGrid();

	void Draw(Renderer* renderer);
	void HandleEvents(SDL_Event e);

private:
	std::vector<PGridElem> m_gridElem;

	void InitGrid();
};