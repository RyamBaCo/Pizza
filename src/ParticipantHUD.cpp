#include "ParticipantHUD.h"
#include "ofMain.h"

ParticipantHUD::ParticipantHUD()
{
	hudPositions[5] = ofPoint(-80, -60);
	hudPositions[4] = ofPoint(-60, -25);
	hudPositions[3] = ofPoint(-22, -5);
	hudPositions[2] = ofPoint(22, -5);
	hudPositions[1] = ofPoint(60, -25);
	hudPositions[0] = ofPoint(80, -60);

	std::map<int, std::string> typeMap;
	typeMap[HUDImageType::FREE] = "f";
	typeMap[HUDImageType::USED] = "u";
	typeMap[HUDImageType::INACTIVE] = "i";

	for(int i = 0; i < GlobalValues::MAX_FREE_SLOTS; ++i)
		for(int j = 0; j < HUDImageType::LAST; ++j)
			hudImages[i][j] = new PizzaImage("images/bar/" + ofToString(i + 1) + typeMap[j] + ".png", PizzaImage::CENTER);
}

ParticipantHUD::~ParticipantHUD()
{
	for(int i = 0; i < GlobalValues::MAX_FREE_SLOTS; ++i)
		for(int j = 0; j < HUDImageType::LAST; ++j)
			if(hudImages[i][j] != 0)
			{
				delete hudImages[i][j];
				hudImages[i][j] = 0;
			}
}

void ParticipantHUD::draw(const ofPoint& position, int rotation, int freeSlots, int availableSlots)
{
	for(int i = 0; i < GlobalValues::MAX_FREE_SLOTS; ++i)
		hudImages[i][i < availableSlots ? (i < freeSlots ? HUDImageType::FREE : HUDImageType::USED) : HUDImageType::INACTIVE]->draw(position, rotation);
}

ofPoint ParticipantHUD::getHUDPosition(int index)
{
	return hudPositions[index];
}
