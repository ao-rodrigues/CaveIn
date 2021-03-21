#include "HoverCursorSystem.h"

#include "../Components/HoverCursor.h"

#include "../Events/HoverCursorAttachEvent.h"
#include "../Events/HoverCursorReleaseEvent.h"


void HoverCursorSystem::update()
{
	auto entities = _entityManager->getEntitiesWithComponentAll<HoverCursor>();

	HoverCursor& hoverCursor = entities[0]->getComponent<HoverCursor>();

	auto hoverAttachEvents = _entityManager->getEntitiesWithComponentAll<HoverCursorAttachEvent>();
	if (hoverAttachEvents.size() > 0 && !_cursorInUse)
	{
		hoverCursor.setPosition(hoverAttachEvents[0]->getComponent<HoverCursorAttachEvent>().position);
		hoverCursor.setVisible(true);
		_cursorInUse = true;
	}

	auto hoverReleaseEvents = _entityManager->getEntitiesWithComponentAll<HoverCursorReleaseEvent>();
	if (hoverReleaseEvents.size() > 0)
	{
		_cursorInUse = false;
		hoverCursor.setVisible(false);
	}
}