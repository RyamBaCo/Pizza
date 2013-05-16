#include "Ingredient.h"


Ingredient::Ingredient(const GlobalValues::IngredientType& type)
	:	type(type),
		image(new PizzaImage(GlobalValues::getInstance().getValuesForIngredient(type).graphicDestination)),
		active(false)
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

void Ingredient::update()
{
	ofPoint diff = image->getDrawPosition() - GlobalValues::PIZZA_CENTER_POINT;
	float anglePt = ofRadToDeg(atan2(diff.y, diff.x)) + GlobalValues::SLICE_ANGLE;
	if (anglePt < 0) anglePt += 360;

	float diffAngle = anglePt - (GlobalValues::getInstance().getCurrentPizzaRotation());
	if (diffAngle > 180) anglePt -= 360;
	if (diffAngle < -180) anglePt += 360;

	active = (anglePt >= GlobalValues::getInstance().getCurrentPizzaRotation() && anglePt <= GlobalValues::getInstance().getCurrentPizzaRotation() + GlobalValues::SLICE_ANGLE);

	if(active && !ingredientSound.getIsPlaying())
		ingredientSound.play();
}

void Ingredient::draw(const ofPoint& position)
{
	image->draw(position);
}