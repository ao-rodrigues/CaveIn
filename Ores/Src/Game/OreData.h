#pragma once

#include <string>

struct OreData
{
	OreData(int typeIndex, int destructionPoints, const std::string& textureID)
		: typeIndex(typeIndex)
		, destructionPoints(destructionPoints)
		, textureID(textureID)
	{ }

	int typeIndex;
	int destructionPoints;
	std::string textureID;
};
