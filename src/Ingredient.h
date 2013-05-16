#pragma once
#include "GlobalValues.h"
#include "PizzaImage.h"

class Ingredient
{
public:
	Ingredient(const GlobalValues::IngredientType& type);
	~Ingredient();

	void draw(const ofPoint& position);
	void update();

private:
	PizzaImage* image;
	GlobalValues::IngredientType type;
	bool active;

	ofSoundPlayer ingredientSound;
};

