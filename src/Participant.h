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

	void update();
	bool draw();

private:
	bool hasIngredient() const;
	void resetIngredients();
	void removeIngredients();

private:
	ofPoint position;
	// the ingredient which is rendered on player's feet
	Ingredient* baseIngredient;
	std::list<Ingredient*> ingredients;
};

