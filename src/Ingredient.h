#pragma once
#include "GlobalValues.h"
#include "PizzaImage.h"

class Ingredient
{
public:
	Ingredient(const GlobalValues::IngredientType& type);
	Ingredient(const GlobalValues::IngredientType& type, const ofPoint& position);
	~Ingredient();

	GlobalValues::IngredientType getType() const;
	void setPosition(const ofPoint& position);

	void draw();
	
	void update();

private:
	PizzaImage* image;
	GlobalValues::IngredientType type;
	bool active;
	ofPoint position;

	ofSoundPlayer ingredientSound;
};

