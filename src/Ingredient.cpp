#include "Ingredient.h"
#include "HelperFunctions.h"

Ingredient::Ingredient(const GlobalValues::IngredientType& type)
	:	type(type),
		image(new PizzaImage(GlobalValues::getInstance().getValuesForIngredient(type).graphicDestination)),
		active(false)
{
	ingredientSound.loadSound(GlobalValues::getInstance().getValuesForIngredient(type).soundDestination);
}

Ingredient::Ingredient(const GlobalValues::IngredientType& type, const ofPoint& position)
	:	type(type),
		image(new PizzaImage(GlobalValues::getInstance().getValuesForIngredient(type).graphicDestination)),
		active(false),
		position(position)
{
	ingredientSound.loadSound(GlobalValues::getInstance().getValuesForIngredient(type).soundDestination);
}

Ingredient::~Ingredient()
{
	if(image != 0)
	{
		delete image;
		image = 0;
	}
}

GlobalValues::IngredientType Ingredient::getType() const
{
	return type;
}

void Ingredient::setPosition(const ofPoint& position)
{
	this->position = position;
}

void Ingredient::update()
{
	if(!ingredientSound.getIsPlaying() && HelperFunctions::isPositionInSlice(position))
		ingredientSound.play();
}

void Ingredient::draw()
{
	image->draw(position);
}
