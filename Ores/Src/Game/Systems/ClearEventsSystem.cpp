#include "ClearEventsSystem.h"

#include "../Events/HoverCursorAttachEvent.h"
#include "../Events/HoverCursorReleaseEvent.h"
#include "../Events/LevelUpEvent.h"
#include "../Events/OreDestroyedEvent.h"
#include "../Events/OreDestroyedInLevelUpEvent.h"
#include "../Events/OreSelectedEvent.h"
#include "../Events/PushEvent.h"


void ClearEventsSystem::update()
{

	for (auto& event : _entityManager->getEntitiesWithComponentAny<
		HoverCursorAttachEvent, 
		HoverCursorReleaseEvent, 
		LevelUpEvent,
		OreDestroyedEvent,
		OreDestroyedInLevelUpEvent,
		OreSelectedEvent,
		PushEvent
	>())
	{
		event->destroy();
	}
}