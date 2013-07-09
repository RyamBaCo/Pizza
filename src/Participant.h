#pragma once
#include "ofMain.h"
#include <list>

#include "Ingredient.h"
#include "ParticipantHUD.h"

class Participant
{
public:
	Participant();
	~Participant();

	void setPosition(const ofPoint& position);
	ofPoint getPosition() const;

	void update();
	bool draw();

	// TODO refactor using observer pattern
	// called by GlobalValues once round has been finished
	void roundComplete();

private:
	bool hasIngredient() const;
	void resetIngredients();
	void removeIngredients();
	void dropIngredient();
	void playGainSlotAnimation(const int numberOfSlots);

private:
	ofPoint position;
	// the ingredient which is rendered on player's feet
	Ingredient* baseIngredient;
	// hud for displaying available "resources"
	ParticipantHUD* hud;
	// track of ingredients
	std::list<Ingredient*> ingredients;
	// lastpoints and frontdirection are used to get the player's orientation
	std::list<ofPoint> lastPoints;
	ofPoint frontDirection;
	ofPoint lastIngredientPosition;

	int freeSlots;
	int availableSlots;
	bool punished;
	bool punishedInRound;
};

