#include "ParticipantHUD.h"
#include "ofMain.h"

ParticipantHUD::ParticipantHUD()
{
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
