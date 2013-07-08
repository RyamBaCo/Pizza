#pragma once
#include "GlobalValues.h"
#include "PizzaImage.h"

class Ingredient
{
public:
	Ingredient(const GlobalValues::IngredientType& type);
	~Ingredient();

	GlobalValues::IngredientType getType() const;
	ofPoint getPosition() const;
	bool isReadyForDelete() const;

	void setPosition(const ofPoint& position);
	void setReadyForDelete(bool readyForDelete);
	void setRotation(float rotation);
	float getRotation() const;
	PizzaImage* getPizzaImage() const;

	void update();
	void draw();

private:
	PizzaImage* image;
	GlobalValues::IngredientType type;
	bool active;
	bool readyForDelete;
	ofPoint position;
};

