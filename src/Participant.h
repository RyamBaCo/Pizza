#pragma once
#include "ofMain.h"
#include <list>

#include "Ingredient.h"

class Participant
{
public:
	Participant();
	~Participant();

	void setPosition(const ofPoint& position);
	ofPoint getPosition() const;
	bool hasIngredient() const;

	void update();
	bool draw();

private:
	void resetIngredients();
	void removeIngredients();
	void dropIngredient();

private:
	ofPoint position;
	// the ingredient which is rendered on player's feet
	Ingredient* baseIngredient;
	// track of ingredients
	std::list<Ingredient*> ingredients;
	ofPoint lastIngredientPosition;

	bool punished;

	ofSoundPlayer burntSound;
};

