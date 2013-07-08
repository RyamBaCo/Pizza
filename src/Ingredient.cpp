#include "Ingredient.h"
#include "HelperFunctions.h"

Ingredient::Ingredient(const GlobalValues::IngredientType& type)
	:	type(type),
		image(new PizzaImage(GlobalValues::getInstance().getValuesForIngredient(type).graphicDestination, PizzaImage::CENTER)),
		active(false),
		readyForDelete(false)
{
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

ofPoint Ingredient::getPosition() const
{
	return position;
}

bool Ingredient::isReadyForDelete() const
{
	return readyForDelete;
}

float Ingredient::getRotation() const
{
	return image->getDrawRotation();
}

PizzaImage* Ingredient::getPizzaImage() const
{
	return image;
}

void Ingredient::setReadyForDelete(bool readyForDelete)
{
	this->readyForDelete = readyForDelete;
}

void Ingredient::setPosition(const ofPoint& position)
{
	this->position = position;
}

void Ingredient::setRotation(float rotation)
{
	image->setDrawRotation(rotation);
}

void Ingredient::update()
{
	if(HelperFunctions::isPositionInSlice(position))
	{
		GlobalValues::getInstance().getValuesForIngredient(type).playSound();
		GlobalValues::getInstance().increaseCurrentScore();
		readyForDelete = true;
	}
}

void Ingredient::draw()
{
	image->draw(position, image->getDrawRotation());
}