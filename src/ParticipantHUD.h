#pragma once
#include "PizzaImage.h"
#include "GlobalValues.h"

class ParticipantHUD
{
public:
	enum HUDImageType
	{
		FREE = 0,
		USED,
		INACTIVE,
		LAST
	};

	ParticipantHUD();
	~ParticipantHUD();

	void draw(const ofPoint& position, int rotation, int freeSlots, int availableSlots);

private:
	PizzaImage* hudImages[GlobalValues::MAX_FREE_SLOTS][HUDImageType::LAST];
};

