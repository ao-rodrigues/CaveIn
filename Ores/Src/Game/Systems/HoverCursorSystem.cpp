#include "HoverCursorSystem.h"

#include "../Components/HoverCursor.h"

#include "../Events/HoverCursorAttachEvent.h"
#include "../Events/HoverCursorReleaseEvent.h"


void HoverCursorSystem::update()
{
	auto entities = _entityManager->getEntitiesWithComponent<HoverCursor>();
	if (entities.size() == 0) return;

	HoverCursor& hoverCursor = entities[0]->getComponent<HoverCursor>();

	auto hoverAttachEvents = _entityManager->getEntitiesWithComponent<HoverCursorAttachEvent>();
	if (hoverAttachEvents.size() > 0 && !_cursorInUse)
	{
		hoverCursor.setPosition(hoverAttachEvents[0]->getComponent<HoverCursorAttachEvent>().position);
		hoverCursor.setVisible(true);
		_cursorInUse = true;
	}

	for (auto& event : hoverAttachEvents)
	{
		event->destroy();
	}

	auto hoverReleaseEvents = _entityManager->getEntitiesWithComponent<HoverCursorReleaseEvent>();
	if (hoverReleaseEvents.size() > 0)
	{
		_cursorInUse = false;
		hoverCursor.setVisible(false);
	}

	// Now that we got the event, we can destroy it
	for (auto& event : hoverReleaseEvents)
	{
		event->destroy();
	}
}