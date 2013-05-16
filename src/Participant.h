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
	bool hasIngredients() const;
	void createIngredients();
	void removeIngredients();

private:
	ofPoint position;
	std::list<Ingredient*> ingredients;
};

